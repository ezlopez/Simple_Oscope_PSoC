#define RX_BUFFER_SIZE  32

// Command Defines
#define PC_CONNECT    "#PC_REQ_CONNECT#"
#define PC_DISCONNECT "#PC_REQ_DISCONNECT#"
#define PSOC_ACK      "PSOC_READY"
#define ADC_PARAMS    "AFRSZ#"
#define DAC_PARAMS    "ADFOVWZ#"

// Default settings
#define DEFAULT_ADC_RESOLUTION 8
#define DEFAULT_ADC_SPS        50000
#define DEFAULT_ADC_FRAME_SIZE 400
#define DEFAULT_ADC_FPS        6

#define DEFAULT_DAC_FREQUENCY   2500
#define DEFAULT_DAC_VPP         2.0
#define DEFAULT_DAC_OFFSET      1.0
#define DEFAULT_DAC_WAVE        SQUARE
#define DEFAULT_DAC_DUTY        50
#define DEFAULT_DAC_SAMPLE_RATE 250000
#define DEFAULT_DAC_SAMPLE_SIZE 100

// Misc defines
#define TIMER_DMA_CLOCK_FREQ   24000000
#define MASTER_CLOCK_FREQ      24000000
#define MINIMUM_ADC_CLOCK_FREQ 1000000
#define MAXIMUM_ADC_CLOCK_FREQ 16000000
#define MAXIMUM_ADC_CLOCK_DIV  24
#define MINIMUM_ADC_CLOCK_DIV  1

/* DMA Configuration for DMA_ADC_MEM */
#define DMA_ADC_MEM_REQUEST_PER_BURST 1
#define DMA_ADC_MEM_SRC_BASE          (CYDEV_PERIPH_BASE)
#define DMA_ADC_MEM_DST_BASE          (CYDEV_SRAM_BASE)
#define MAX_DMA_TRANSFER_SIZE         4095

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
void DMA_ADC_MEM_Destruct();
void startADC();
void stopADC();
void changeSPS(int sps);
void changeRes(int res);
void adcFrameResize(int newSize);
void startDAC();
void stopDAC();
void changeDuty();
void regenerateWave();