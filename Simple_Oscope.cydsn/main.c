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
uint8 rxBufLen = 0;
uint8 commandReady = 0;
char  command[RX_BUFFER_SIZE] = {0};

// ADC Variables
uint8  adcOn         = 0;
uint8  adcRez        = DEFAULT_ADC_RESOLUTION;
uint32 adcSPS        = DEFAULT_ADC_SPS;
uint16 adcFrame[ADC_FRAME_SIZE];
uint8  adcFrameReady = 0;

// DAC Variables
uint8    dacOn     = 0;
uint32   dacFreq   = DEFAULT_DAC_FREQUENCY;
float    dacVPP    = DEFAULT_DAC_VPP;
float    dacOffset = DEFAULT_DAC_OFFSET;
waveform dacWave   = DEFAULT_DAC_WAVE;
uint8    dacDuty   = DEFAULT_DAC_DUTY;
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
            sprintf(framePrefix, "#F%dD", ADC_FRAME_SIZE);
            UART_PutString(framePrefix);
            for (i = 0; i < ADC_FRAME_SIZE; i++) {
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
    
    if (*param == 'A') {
        #ifdef DEBUG_OUTPUT
        UART_PutString("ADC");
        #endif
        ++param;
        while (*param != '#') {
            switch (*param++) {
                case 'A': // Start
                    #ifdef DEBUG_OUTPUT
                    UART_PutString(" Start");
                    #endif
                    
                    if (!adcOn) {
                        ADC_StartConvert();
                        TIMER_DMA_Start();
                        adcOn = 1;
                        CyDmaChEnable(DMA_ADC_MEM_Chan, 1);
                    }
                    
                    break;
                case 'F': // Samples per frame
                    #ifdef DEBUG_OUTPUT
                    UART_PutString(" SPF");
                    #endif
                    break;
                case 'R': // Resolution
                    #ifdef DEBUG_OUTPUT
                    UART_PutString(" Res");
                    #endif
                    break;
                case 'S': // Samples per second
                    #ifdef DEBUG_OUTPUT
                    UART_PutString(" SPS");
                    #endif
                    break;
                case 'Z': // Stop
                    #ifdef DEBUG_OUTPUT
                    UART_PutString(" Stop");
                    #endif
                    
                    if (adcOn) {
                        TIMER_DMA_Stop();
                        ADC_Stop();
                        CyDmaChDisable(DMA_ADC_MEM_Chan);
                        adcOn = 0;
                    }
                    
                    break;
                default:  // Unexpected parameter
                    #ifdef DEBUG_OUTPUT
                    UART_PutString(" Unknown");
                    #endif
                    break;
            }
            param = strpbrk(param, ADC_PARAMS);
        }
        #ifdef DEBUG_OUTPUT
        UART_PutString("\n\r");
        #endif
    }
    else if (*param == 'D') {
        #ifdef DEBUG_OUTPUT
        UART_PutString("DAC");
        #endif
        ++param;
        while (*param != '#') {
            switch (*param++) {
                case 'A': // Start
                    #ifdef DEBUG_OUTPUT
                    UART_PutString(" Start");
                    #endif
                    
                    if (!dacOn) {
                        MUX_DAC_FastSelect(ms);
                        Control_DAC_Write(ws);
                        DAC_1_Start();
                        DAC_2_Start();
                        dacOn = 1;
                    }
                    
                    break;
                case 'D': // Duty cycle
                    #ifdef DEBUG_OUTPUT
                    UART_PutString(" Duty");
                    #endif
                    break;
                case 'F': // Frequency
                    #ifdef DEBUG_OUTPUT
                    UART_PutString(" Freq");
                    #endif
                    break;
                case 'O': // Offset
                    #ifdef DEBUG_OUTPUT
                    UART_PutString(" Offset");
                    #endif
                    break;
                case 'V': // Peak to Peak Voltage
                    #ifdef DEBUG_OUTPUT
                    UART_PutString(" VPP");
                    #endif
                    break;
                case 'W': // Waveform
                    #ifdef DEBUG_OUTPUT
                    UART_PutString(" Wave");
                    #endif
                    
                    // Settings for current DAC setup
                    //       MUX 0   MUX 1
                    // REG0  Sine    Triangle
                    // REG1  Square  Arbitrary
                    //
                    // S(I)ne, S(Q)uare, Sa(W)tooth, (T)riangle, (A)rbitrary
                    switch (*++param) {
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
                            break;
                    }
                    
                    Control_DAC_Write(ws);
                    MUX_DAC_FastSelect(ms);
                    
                    break;
                case 'Z': // Stop
                    #ifdef DEBUG_OUTPUT
                    UART_PutString(" Stop");
                    #endif
                    
                    if (dacOn) {
                        MUX_DAC_DisconnectAll();
                        DAC_1_Stop();
                        DAC_2_Stop();
                        dacOn = 0;
                    }
                    
                    break;
                default:  // Unexpected parameter
                    #ifdef DEBUG_OUTPUT
                    UART_PutString(" Unknown");
                    #endif
                    break;
            }
            param = strpbrk(param, DAC_PARAMS);
        }
        #ifdef DEBUG_OUTPUT
        UART_PutString("\n\r");
        #endif
    }
    else if (strcmp(command, PC_DISCONNECT) == 0) {
        // Set everything to default and uninitialize
    }
    else { // Unspecified command
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
            #ifdef DEBUG_OUTPUT
            UART_PutString("Random bytes");
            #endif
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
    #ifdef DEBUG_OUTPUT
    UART_PutString("DMA Reenabled\r\n");
    #endif
    CyDmaChEnable(DMA_ADC_MEM_Chan, 1);
}

// Used to notify Main that a frame is ready for transmission
CY_ISR(DMA_FRAME_INTER) {
    #ifdef DEBUG_OUTPUT
    UART_PutString("Frame Captured\r\n");
    #endif
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
    CyDmaTdSetConfiguration(DMA_ADC_MEM_TD[0], 2 * ADC_FRAME_SIZE, CY_DMA_DISABLE_TD,
     DMA_ADC_MEM__TD_TERMOUT_EN | TD_INC_DST_ADR);
    CyDmaTdSetAddress(DMA_ADC_MEM_TD[0], LO16((uint32)ADC_SAR_WRK0_PTR), LO16((uint32)adcFrame));
    CyDmaChSetInitialTd(DMA_ADC_MEM_Chan, DMA_ADC_MEM_TD[0]);
}