#include <main.h>
#include <device.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

CY_ISR_PROTO(UART_RX_INTER);
CY_ISR_PROTO(TIMER_DMA_INTER);
CY_ISR_PROTO(DMA_FRAME_INTER);

// Value describes sync state with PC GUI
uint8 initialized = 0;

// UART variables
char  rxBuffer[RX_BUFFER_SIZE];
uint8 rxBufLen     = 0;
uint8 commandReady = 0;
char  command[RX_BUFFER_SIZE];

// ADC Variables
uint8  adcOn           = 0;
uint   adcRez          = DEFAULT_ADC_RESOLUTION;
uint32 adcSPS          = DEFAULT_ADC_SPS;
uint8  adcFPS          = DEFAULT_ADC_FPS;
uint   adcFrameSize    = DEFAULT_ADC_FRAME_SIZE;
uint16 *adcFrame;
uint8  adcFrameReady   = 0;
uint32 adcSPSValues[6] = {  50, 250, 1000, 50000, 250000, 1000000};
uint8  adcDiv8Bit[6]   = {  40,  40,   40,    40,     16,       4};
uint16 adcCount8Bit[6] = {2000, 400,  100,     2,      1,       1};

// DAC Variables
uint8       dacOn       = 0;
uint32      dacFreq     = DEFAULT_DAC_FREQUENCY;
float       dacVPP      = DEFAULT_DAC_VPP;
float       dacOffset   = DEFAULT_DAC_OFFSET;
waveform    dacWave     = DEFAULT_DAC_WAVE;
uint        dacDuty     = DEFAULT_DAC_DUTY;
uint16      sample_size = 100;
uint8       ws          = 1;
uint8       ms          = 0;
uint32      sample_rate = DEFAULT_DAC_SAMPLE_RATE;
char        wavetype    = 'Q';                      //Default waveform is Square


/* Variable declarations for DMA_ADC_MEM */
uint8 DMA_ADC_MEM_Chan;
uint8 DMA_ADC_MEM_TD[1];
uint8 DMA_ADC_MEM_BYTES_PER_BURST = 1;

int main() {
    uint16 i;
    char framePrefix[10];
    
    // Init modules
    adcFrame = malloc(DMA_ADC_MEM_BYTES_PER_BURST * adcFrameSize);
    UART_Start();
    ADC_Start();
    
    DMA_ADC_MEM_Config();
    TIMER_DMA_Init();
    SPS_Divider_Counter_Start();
    UART_RX_StartEx(UART_RX_INTER);
    DMA_ENABLE_StartEx(TIMER_DMA_INTER);
    DMA_FRAME_READY_StartEx(DMA_FRAME_INTER);
    CYGlobalIntEnable;
    
    for/*ever*/(;;) {
        // Sync with the GUI
        while(!initialized) {
            if (commandReady) {
                commandReady = 0;
                if (strcmp(command, PC_CONNECT) == 0) {
                    initialized = 1;
                    UART_PutString(PSOC_ACK);
                }
            }
        }
        
        // Parse a command if available
        if (commandReady) {
            parseCommand(command);
            commandReady = 0;
        }
        
        // Send ADC frame to PC if available
        if (adcFrameReady) {
            adcFrameReady = 0;
            #ifndef DEBUG_OUTPUT
            sprintf(framePrefix, "#F%dK%luD", adcFrameSize, adcSPS);
            UART_PutString(framePrefix);
            for (i = 0; i < adcFrameSize; i++) {
                // Send both bits only if adcRez != 8
                if (DMA_ADC_MEM_BYTES_PER_BURST == 2)
                    UART_PutChar((adcFrame[i] >> 8) & 0XFF);
                UART_PutChar(adcFrame[i] & 0XFF);
            }
            #endif
        }
    }
    return 0;
}

void parseCommand(char *cmd) {
    char *param = cmd + 1;
    uint32 temp;
    
    if (*param == 'A') {
        DEBUG_PRINT("ADC");
        ++param;
        while (*param != '#') {
            switch (*param++) {
                case 'A': // Start
                    DEBUG_PRINT(" Start");
                    startADC();
                    break;
                case 'F': // Samples per frame
                    DEBUG_PRINT(" SPF");
                    sscanf(param, "%ld", &temp);
                    adcFrameResize(temp);
                    break;
                case 'P': // Frames per second
                    DEBUG_PRINT(" FPS");
                    sscanf(param, "%ld", &temp);
                    if(temp && temp <= 255) // Crappy attempt at an upper limit
                        TIMER_DMA_WritePeriod(TIMER_DMA_CLOCK_FREQ / temp);
                     else
                        DEBUG_PRINT(" FPS too large");
                    break;
                case 'R': // Resolution
                    DEBUG_PRINT(" Res");
                    sscanf(param, "%ld", &temp);
                    changeRes(temp);
                    break;
                case 'S': // Samples per second
                    DEBUG_PRINT(" SPS");
                    sscanf(param, "%ld", &temp);
                    changeSPS(temp);
                    break;
                case 'Z': // Stop
                    DEBUG_PRINT(" Stop");
                    stopADC();
                    break;
                default:  // Unexpected parameter
                    DEBUG_PRINT(" Unknown");
                    break;
            }
            param = strpbrk(param, ADC_PARAMS);
        }
        DEBUG_PRINT("\n\r");
    }
    else if (*param == 'D') {
        DEBUG_PRINT("DAC");
        ++param;
        while (*param != '#') {
            switch (*param++) {
                case 'A': // Start
                    DEBUG_PRINT(" Start");
                    startDAC();
                    break;
                case 'D': // Duty cycle
                    DEBUG_PRINT(" Duty");
                    sscanf(param, "%d", &dacDuty);
                    // Make sure it is a valid value
                    if (dacDuty > 100) {
                        DEBUG_PRINT(" Invalid duty");
                    }
                    else {
                        // Do stuff to change the duty (only for square wave)
                        changeDuty();
                    }
                    break;
                case 'F': // Frequency
                    DEBUG_PRINT(" Freq");
                    
                    sscanf(param, "%ld", &dacFreq);
                    // Make sure it is a valid value
                    if (dacFreq > 240000 || dacFreq < 62) {
                        DEBUG_PRINT(" Invalid frequency");
                    }
                    else {
                        // Do stuff to change the frequency
                        sample_size = DEFAULT_DAC_SAMPLE_RATE / dacFreq;
                        
                    }
                    break;
                case 'O': // Offset
                    DEBUG_PRINT(" Offset");
                    
                    sscanf(param, "%f", &dacOffset);
                    // Make sure it is a valid value
                    if (dacOffset < 0 || dacOffset > 4.0) {
                        DEBUG_PRINT(" Invalid offset");
                    }
                    else {
                        // Changes offset to a value between 0 to 250u
                        dacVPP = floor( dacVPP / 4.0 * 250 );
                        regenerateWave();
                    }
                    break;
                case 'V': // Peak to Peak Voltage
                    DEBUG_PRINT(" VPP");
                    
                    sscanf(param, "%f", &dacVPP);
                    // Make sure it is a valid value
                    if (dacVPP < 0 || dacVPP > 4.0) {
                        DEBUG_PRINT(" Invalid VPP");
                    }
                    else {
                        // Do stuff to change the VPP
                        // ranges from 0u to 255u but for uncertainty use 3u to 253u
                        // changes the Vpp to a value between 0 to 250u
                        dacVPP = floor( dacVPP / 4.0 * 250 );
                        regenerateWave();
                    }
                    break;
                    
                case 'W': // Waveform
                    DEBUG_PRINT(" Wave");
                    wavetype = *(param++);
                    
                    regenerateWave();
                    break;
                case 'Z': // Stop
                    DEBUG_PRINT(" Stop");
                    stopDAC();
                    break;
                default:  // Unexpected parameter
                    DEBUG_PRINT(" Unknown");
                    break;
            }
            param = strpbrk(param, DAC_PARAMS);
        }
        DEBUG_PRINT("\n\r");
    }
    else if (strcmp(command, PC_DISCONNECT) == 0) {
        // Perform Software reset, good as new
        CySoftwareReset();
    }
    else { // Unspecified command
        DEBUG_PRINT("Unspecified command\n\r");
    }
}

void regenerateWave()
{
    uint8 wave[sample_size];
    
    stopDAC();
    // Settings for current DAC setup
    //       MUX 0   MUX 1
    // REG0  Sine    Triangle
    // REG1  Square  Arbitrary
    //
    // S(I)ne, S(Q)uare, Sa(W)tooth, (T)riangle, (A)rbitrary
                    
    switch (wavetype) {
        case 'A':
            
            break;
        case 'I':
            
            break;
        case 'Q':
            
            break;
        case 'T':
            
            break;
        case 'W':
            // Not yet implemented
        
            break;
        default:
            // Bad parameter
            DEBUG_PRINT(" Invalid waveform");
            break;
    }
    startDAC();
}

void changeDuty()
{
    if (!ms && ws)
    {
        // Its a square wave
        stopDAC();
        // write new square wave
        uint8 square[sample_size];
        uint8 up_time = (dacDuty * sample_size) / 100 ;
        int i;
        // ON phase
        for ( i = 0; i < up_time; i++)
        {
            square[i] = 252u;
        }
        // OFF phase
        for (; i < sample_size; i++)
        {
            square[i] = 3u;
        }
        
        DAC_1_Wave1Setup(square, sample_size);
        startDAC();
        
    }
}


void startADC() {
    if (!adcOn) {
        ADC_StartConvert();
        TIMER_DMA_Start();
        adcOn = 1;
        CyDmaChEnable(DMA_ADC_MEM_Chan, 1);
    }
}

/* 
   Steps to make it safe.
   1. Stop the timer
   2. Wait for the DMA to finish
   3. Stop the ADC
*/
void stopADC() {
    uint8 state;
    
    if (adcOn) {
        TIMER_DMA_Stop();
        do {
            CyDmaChStatus(DMA_ADC_MEM_Chan, NULL, &state);
        }while (state);
        CyDmaChDisable(DMA_ADC_MEM_Chan); // May not need this. No idea.
        ADC_Stop();
        adcOn = 0;
    }
}

void startDAC() {
    if (!dacOn) 
    {
        MUX_DAC_FastSelect(ms);
        Control_DAC_Write(ws);
        DAC_1_Start();
        //DAC_2_Start();
        dacOn = 1;
    }
}

void stopDAC() {
    if (dacOn) {
        MUX_DAC_DisconnectAll();
        DAC_1_Stop();
        //DAC_2_Stop();
        dacOn = 0;
    }
}

void changeSPS(int sps) {
    int restoreAdc = adcOn;
    int i;
    
    // Don't have 10- or 12-bit implemented yet *****************************
    if (adcRez != 8) {
        DEBUG_PRINT("Not implemented for 10- or 12-bit yet. Rejecting request.\n\r");
        return;
    }
    
    // Make sure it is a valid value
    for (i = 0; i < 6; i++) {
        if (adcSPSValues[1] == (uint32)sps)
           break;
    }
    
    if (i == 6) {
        DEBUG_PRINT("Invalid SPS. Rejecting request.\n\r");
        return;
    }
        
    // Stop the ADC. Safety first, kids.
    stopADC();
    
    // <i> should now point to the table entry for the SPS
    // Set the clock divider
    if (adcRez == 8)
        ADC_Clock_SetDividerValue(adcDiv8Bit[i]);
    else if (adcRez == 10) {
    }
    else {
    }
    
    // Set the counter period
    if (adcRez == 8)
        SPS_Divider_Counter_WritePeriod(adcCount8Bit[i]);
    else if (adcRez == 10) {
    }
    else {
    }
    
    // Set the mux control register
    if (adcRez == 8)
        SPS_Divider_Control_Reg_Write(adcCount8Bit[i] != 1);
    else if (adcRez == 10) {
    }
    else {
    }
    
    adcSPS = sps;
    
    // Restart if necessary
    if (restoreAdc)
        startADC();
}

void changeRes(int res) {
    int restoreADC = adcOn;
    
    // Make sure it is a valid value
    if ((res != 12 && res != 10 && res != 8) || (unsigned)res == adcRez) {
        DEBUG_PRINT(" Invalid resolution");
        return;
    }
    
    // Play safely
    stopADC();
    
    // Check to see if changing between incompatible res'
    if (res == 8 || adcRez == 8) {
        DMA_ADC_MEM_Destruct();
        
        // Resize the frame and DMA settings
        DMA_ADC_MEM_BYTES_PER_BURST = res == 8 ? 1 : 2;
        adcFrameResize(adcFrameSize);
        
        // Reconfigure the DMA with new settings
        DMA_ADC_MEM_Config();
    }
    
    // Finally change the resolution
    ADC_SetResolution(res);
    
    // Turn the lights back on
    if (restoreADC)
        startADC();
}

void adcFrameResize(int newSize) {
    free(adcFrame);
        
    // Make sure new size doesn't request more bytes than the DMA can handle
    if (DMA_ADC_MEM_BYTES_PER_BURST * newSize > MAX_DMA_TRANSFER_SIZE) {
        adcFrameSize = MAX_DMA_TRANSFER_SIZE / DMA_ADC_MEM_BYTES_PER_BURST;
        DEBUG_PRINT("Sloppy programming. Data size * frame size must be ");
        DEBUG_PRINT("less than 4095 bytes.\r\nResized to max frame size.\r\n");
    }
    else
        adcFrameSize = newSize;
    
    adcFrame = malloc(DMA_ADC_MEM_BYTES_PER_BURST * adcFrameSize);
}

CY_ISR(UART_RX_INTER) {
    char c;
    
    // Build the command if no other command is pending
    // Need error checking for command greater than 32 chars**************************
    while (UART_GetRxBufferSize() && !commandReady) {
        c = UART_GetChar();
        if (rxBufLen || c == '#') { // Filters out random bytes
            rxBuffer[rxBufLen] = c;
            if (rxBufLen++ && c == '#') { // End packet
                commandReady = 1;
                strncpy(command, rxBuffer, rxBufLen);
                command[rxBufLen] = 0;
                rxBufLen = 0;
            }
        }
        else {
            DEBUG_PRINT("Random bytes\n\r");
        }
    }
    
    // Check for error with UART module
    if (UART_ReadRxStatus() & (UART_RX_STS_OVERRUN | UART_RX_STS_PAR_ERROR |
     UART_RX_STS_STOP_ERROR | UART_RX_STS_BREAK)) {
        // Maybe do something about it
        // Clear buffer and request resend
    }
}

// Used to reenable the ADC to MEM DMA so that another frame can be captured
CY_ISR(TIMER_DMA_INTER) {
    uint8 state;
    
    CyDmaChStatus(DMA_ADC_MEM_Chan, NULL, &state);
    
    // Want to make sure DMA is complete before trying to reactivate it
    if (!state) {
        CyDmaChEnable(DMA_ADC_MEM_Chan, 1);
        DEBUG_PRINT("DMA Reenabled\r\n");
    }
    else {
        DEBUG_PRINT("TIMER_DMA period too small\r\n");
    }
}

// Used to notify Main that a frame is ready for transmission
CY_ISR(DMA_FRAME_INTER) {
    DEBUG_PRINT("Frame Captured\r\n");
    adcFrameReady = 1;
}

/*  Code created by the DMA Wizard. Initializes the DMA to transfer ADC_FRAME_SIZE samples
 *  to the array adcFrame. After one frame capture it disables the channel and waits to be
 *  reenabled.
 */
void DMA_ADC_MEM_Config() {
    DMA_ADC_MEM_Chan = DMA_ADC_MEM_DmaInitialize(DMA_ADC_MEM_BYTES_PER_BURST,
        DMA_ADC_MEM_REQUEST_PER_BURST, HI16(DMA_ADC_MEM_SRC_BASE), HI16(DMA_ADC_MEM_DST_BASE));
    
    DMA_ADC_MEM_TD[0] = CyDmaTdAllocate();
    
    CyDmaTdSetConfiguration(DMA_ADC_MEM_TD[0], DMA_ADC_MEM_BYTES_PER_BURST * adcFrameSize,
     CY_DMA_DISABLE_TD, DMA_ADC_MEM__TD_TERMOUT_EN | TD_INC_DST_ADR);
    
    CyDmaTdSetAddress(DMA_ADC_MEM_TD[0], LO16((uint32)ADC_SAR_WRK0_PTR), LO16((uint32)adcFrame));
    
    CyDmaChSetInitialTd(DMA_ADC_MEM_Chan, DMA_ADC_MEM_TD[0]);
}

/*
   Gets rid of the DMA channel and TD, most-likely to update it for some change.
   User needs to make sure DMA is stopped before attempting to call this function.
*/
void DMA_ADC_MEM_Destruct() {
    DMA_ADC_MEM_DmaRelease();
    CyDmaTdFree(DMA_ADC_MEM_TD[0]);
}

