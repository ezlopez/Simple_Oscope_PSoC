#include <main.h>
#include <device.h>
#include <stdlib.h>
#include <stdio.h>

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
uint8  adcOn         = 0;
uint   adcRez        = DEFAULT_ADC_RESOLUTION;
uint32 adcSPS        = DEFAULT_ADC_SPS;
uint8  adcFPS        = DEFAULT_ADC_FPS;
uint   adcFrameSize  = DEFAULT_ADC_FRAME_SIZE;
uint16 adcFrame[DEFAULT_ADC_FRAME_SIZE];
uint8  adcFrameReady = 0;

// DAC Variables
uint8    dacOn     = 0;
uint32   dacFreq   = DEFAULT_DAC_FREQUENCY;
float    dacVPP    = DEFAULT_DAC_VPP;
float    dacOffset = DEFAULT_DAC_OFFSET;
waveform dacWave   = DEFAULT_DAC_WAVE;
uint     dacDuty   = DEFAULT_DAC_DUTY;
uint8    ws        = 0;
uint8    ms        = 0;

/* Variable declarations for DMA_ADC_MEM */
uint8 DMA_ADC_MEM_Chan;
uint8 DMA_ADC_MEM_TD[1];

int main() {
    uint16 i;
    char framePrefix[10];
    
    // Init modules
    UART_Start();
    ADC_Start();
    DMA_ADC_MEM_Config();
    TIMER_DMA_Init();
    UART_RX_StartEx(UART_RX_INTER);
    DMA_ENABLE_StartEx(TIMER_DMA_INTER);
    DMA_FRAME_READY_StartEx(DMA_FRAME_INTER);
    CYGlobalIntEnable;
    
    for(;;) {
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
            sprintf(framePrefix, "#F%dD", adcFrameSize);
            UART_PutString(framePrefix);
            for (i = 0; i < adcFrameSize; i++) {
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
                    break;
                case 'R': // Resolution
                    DEBUG_PRINT(" Res");
                    sscanf(param, "%d", &adcRez);
                    // Make sure it is a valid value
                    if (adcRez != 12 && adcRez != 10 && adcRez != 8) {
                        DEBUG_PRINT(" Invalid resolution");
                    }
                    else {
                        // Do stuff to change the resolution
                    }
                    break;
                case 'P': // Frames per second
                    DEBUG_PRINT(" FPS");
                    sscanf(param, "%ld", &temp);
                    
                    if(temp && temp <= 255)
                        TIMER_DMA_WritePeriod(TIMER_DMA_CLOCK_FREQ / temp);
                    
                case 'S': // Samples per second
                    DEBUG_PRINT(" SPS");
                    sscanf(param, "%ld", &adcSPS);
                    // Make sure it is a valid value
                    // Should make it resolution-specific *************************************
                    if (adcSPS < MINIMUM_ADC_SPS || adcSPS > MAXIMUM_ADC_SPS) {
                        DEBUG_PRINT(" Invalid SPS");
                    }
                    else {
                        // Do stuff to change the SPS
                    }
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
                    if (!dacOn) {
                        MUX_DAC_FastSelect(ms);
                        Control_DAC_Write(ws);
                        DAC_1_Start();
                        DAC_2_Start();
                        dacOn = 1;
                    }
                    break;
                case 'D': // Duty cycle
                    DEBUG_PRINT(" Duty");
                    
                    sscanf(param, "%d", &dacDuty);
                    // Make sure it is a valid value
                    if (dacDuty > 100) {
                        DEBUG_PRINT(" Invalid duty");
                    }
                    else {
                        // Do stuff to change the duty
                    }
                    break;
                case 'F': // Frequency
                    DEBUG_PRINT(" Freq");
                    
                    sscanf(param, "%ld", &dacFreq);
                    // Make sure it is a valid value
                    if (dacFreq > 240000) {
                        DEBUG_PRINT(" Invalid frequency");
                    }
                    else {
                        // Do stuff to change the frequency
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
                        // Do stuff to change the offset
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
                    }
                    break;
                case 'W': // Waveform
                    DEBUG_PRINT(" Wave");
                    
                    // Settings for current DAC setup
                    //       MUX 0   MUX 1
                    // REG0  Sine    Triangle
                    // REG1  Square  Arbitrary
                    //
                    // S(I)ne, S(Q)uare, Sa(W)tooth, (T)riangle, (A)rbitrary
                    switch (*(param++)) {
                        case 'A':
                            ms = 1;
                            ws = 1;
                            break;
                        case 'I':
                            ms = 0;
                            ws = 0;
                            break;
                        case 'Q':
                            ms = 0;
                            ws = 1;
                            break;
                        case 'T':
                            ms = 1;
                            ws = 0;
                            break;
                        case 'W':
                            // Not yet implemented
                            break;
                        default:
                            // Bad parameter
                            DEBUG_PRINT(" Invalid waveform");
                            break;
                    }
                    
                    Control_DAC_Write(ws);
                    MUX_DAC_FastSelect(ms);
                    
                    break;
                case 'Z': // Stop
                    DEBUG_PRINT(" Stop");
                    
                    if (dacOn) {
                        MUX_DAC_DisconnectAll();
                        DAC_1_Stop();
                        DAC_2_Stop();
                        dacOn = 0;
                    }
                    
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

void startADC() {
    if (!adcOn) {
        ADC_StartConvert();
        TIMER_DMA_Start();
        adcOn = 1;
        CyDmaChEnable(DMA_ADC_MEM_Chan, 1);
    }
}

/* Steps to make it safe.
   1. Stop the timer
   2. Wait for the DMA to finish
   3. Stop the ADC
   Don't forget to implement **********************************************************
*/
void stopADC() {
    if (adcOn) {
        TIMER_DMA_Stop();
        ADC_Stop();
        CyDmaChDisable(DMA_ADC_MEM_Chan);
        adcOn = 0;
    }
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
    DMA_ADC_MEM_Chan = DMA_ADC_MEM_DmaInitialize(DMA_ADC_MEM_BYTES_PER_BURST, DMA_ADC_MEM_REQUEST_PER_BURST, 
     HI16(DMA_ADC_MEM_SRC_BASE), HI16(DMA_ADC_MEM_DST_BASE));
    
    DMA_ADC_MEM_TD[0] = CyDmaTdAllocate();
    
    CyDmaTdSetConfiguration(DMA_ADC_MEM_TD[0], 2 * adcFrameSize, CY_DMA_DISABLE_TD,
     DMA_ADC_MEM__TD_TERMOUT_EN | TD_INC_DST_ADR);
    
    CyDmaTdSetAddress(DMA_ADC_MEM_TD[0], LO16((uint32)ADC_SAR_WRK0_PTR), LO16((uint32)adcFrame));
    
    CyDmaChSetInitialTd(DMA_ADC_MEM_Chan, DMA_ADC_MEM_TD[0]);
}