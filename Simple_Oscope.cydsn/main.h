#define RX_BUFFER_SIZE  32

// Command Defines
#define PC_CONNECT      "#PC_REQ_CONNECT#"
#define PC_DISCONNECT   "#PC_REQ_DISCONNECT#"
#define PSOC_ACK        "PSOC_READY"
#define ADC_PARAMS      "AFRSZ#"
#define DAC_PARAMS      "ADFOVWZ#"

// Default settings
#define DEFAULT_ADC_RESOLUTION  12
#define DEFAULT_ADC_SPS         100000
#define ADC_FRAME_SIZE          400

#define DEFAULT_DAC_FREQUENCY   100
#define DEFAULT_DAC_VPP         2.0
#define DEFAULT_DAC_OFFSET      1.0
#define DEFAULT_DAC_WAVE        SQUARE
#define DEFAULT_DAC_DUTY        50

/* DMA Configuration for DMA_ADC_MEM */
#define DMA_ADC_MEM_BYTES_PER_BURST 2
#define DMA_ADC_MEM_REQUEST_PER_BURST 1
#define DMA_ADC_MEM_SRC_BASE (CYDEV_PERIPH_BASE)
#define DMA_ADC_MEM_DST_BASE (CYDEV_SRAM_BASE)

// Uncomment to enable debug output
//#define DEBUG_OUTPUT

#ifdef DEBUG_OUTPUT
    #define DEBUG_PRINT(x) {\
            UART_PutString(x);\
            }
#else
    #define DEBUG_PRINT(x)
#endif

typedef enum {SINE, SQUARE, SAW, TRIANGLE, ARB} waveform;
void parseCommand(char *cmd);
void DMA_ADC_MEM_Config();
void initVariables();