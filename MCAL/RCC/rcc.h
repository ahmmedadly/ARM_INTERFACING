#ifndef RCC_H_
#define RCC_H_

#define NULL    ((void *)0)   // Define NULL pointer
#define RCC_BASE_ADDR        0x40023800U    // RCC Base address 
#define RCC                 ((RCC_REGISTERS *)RCC_BASE_ADDR) //RCC Registers structure pointer 
/*************************************************************************/
/* Clock source selection masks */
#define SW_CLR               0xFFFFFFFC
#define SW_HSI               0x0
#define SW_HSE               0x1
#define SW_PLL               0x2

/* Clock enable bits */
#define RCC_CLK_HSI          0x00000001
#define RCC_CLK_HSE          0x00010000
#define RCC_CLK_PLL          0x01000000

// PLL configuration limits
#define PLLM_MIN             2
#define PLLM_MAX             63
#define PLLN_MIN             50
#define PLLN_MAX             432
#define PLLP_VALID_VALUES    {2, 4, 6, 8}
#define PLLQ_MIN             2
#define PLLQ_MAX             15
#define PLLSRC_HSI           0
#define PLLSRC_HSE           1

/*************************************************************************/
/* Clock ready bit positions */
#define HSI_RDY_BIT          1
#define HSE_RDY_BIT          17
#define PLL_RDY_BIT          25
/*************************************************************************/
// Peripheral clock enable bits 
// AHB1 peripherals
#define GPIOA_EN_BIT         0
#define GPIOB_EN_BIT         1
#define GPIOC_EN_BIT         2
#define GPIOD_EN_BIT         3
#define GPIOE_EN_BIT         4
#define GPIOF_EN_BIT         5
#define GPIOG_EN_BIT         6
#define GPIOH_EN_BIT         7
#define CRC_EN_BIT           12
#define DMA1_EN_BIT          21
#define DMA2_EN_BIT          22
#define ETHMAC_EN_BIT        25
#define USB_OTG_HS_EN_BIT    27

// AHB2 peripherals
#define USB_OTG_FS_EN_BIT    7
#define RNG_EN_BIT           6
#define CAMERA_EN_BIT        8

// APB1 peripherals
#define TIM2_EN_BIT          0
#define TIM3_EN_BIT          1
#define TIM4_EN_BIT          2
#define TIM5_EN_BIT          3
#define TIM6_EN_BIT          4
#define TIM7_EN_BIT          5
#define TIM12_EN_BIT         6
#define TIM13_EN_BIT         7
#define TIM14_EN_BIT         8
#define WWDG_EN_BIT          11
#define SPI2_EN_BIT          14
#define SPI3_EN_BIT          15
#define USART2_EN_BIT        17
#define USART3_EN_BIT        18
#define UART4_EN_BIT         19
#define UART5_EN_BIT         20
#define I2C1_EN_BIT          21
#define I2C2_EN_BIT          22
#define I2C3_EN_BIT          23
#define CAN1_EN_BIT          25
#define CAN2_EN_BIT          26
#define PWR_EN_BIT           28
#define DAC_EN_BIT           29

// APB2 peripherals
#define TIM1_EN_BIT          0
#define TIM8_EN_BIT          1
#define USART1_EN_BIT        4
#define USART6_EN_BIT        5
#define ADC1_EN_BIT          8
#define ADC2_EN_BIT          9
#define ADC3_EN_BIT          10
#define SDIO_EN_BIT          11
#define SPI1_EN_BIT          12
#define SPI4_EN_BIT          13
#define SYSCFG_EN_BIT        14
#define TIM9_EN_BIT          16
#define TIM10_EN_BIT         17
#define TIM11_EN_BIT         18
/*************************************************************************/
// Bus ranges
#define AHB1_START    0   // GPIOA is the first peripheral in AHB1
#define AHB1_END      27  // USB OTG HS is the last peripheral in AHB1

#define AHB2_START    6   // RNG is the first peripheral in AHB2
#define AHB2_END      8   // Camera Interface is the last peripheral in AHB2

#define APB1_START    0   // TIM2 is the first peripheral in APB1
#define APB1_END      29  // DAC is the last peripheral in APB1

#define APB2_START    0   // TIM1 is the first peripheral in APB2
#define APB2_END      18  // TIM11 is the last peripheral in APB2

/*************************************************************************/

/* Error status enumeration */
typedef enum {
    RCC_OK,
    RCC_NOK,
    RCC_NULL_PTR,
    RCC_INVALID_PLLM,
    RCC_INVALID_PLLN,
    RCC_INVALID_PLLP,
    RCC_INVALID_PLLQ,
    RCC_INVALID_PLLSRC,
    RCC_INVALID_PERIPHERAL,
    RCC_INVALID_BUS
} RCC_err_status_t;
/*************************************************************************/
/* Clock source enumeration */
typedef enum {
    HSI_CLK,
    HSE_CLK,
    PLL_CLK
} RCC_CLK_t;
/*************************************************************************/
/* PLL CONFIGRATION STRUCTURE */
typedef struct {
    u32 PLLM;   // Division factor for the main PLL input clock (2-63)
    u32 PLLN;   // Main PLL multiplication factor (50-432)
    u32 PLLP;   // Main PLL division factor for system clock (2, 4, 6, or 8)
    u32 PLLQ;   // Main PLL division factor for USB OTG FS, SDIO, and RNG clocks (2-15)
    u32 PLLSRC; // PLL entry clock source (0 for HSI, 1 for HSE)
} PLL_CONFIG_t;

/*************************************************************************/
/* Function prototypes */
RCC_err_status_t RCC_ClkEnable(u32 RCC_CLK);
RCC_err_status_t RCC_ClkSel(u32 RCC_CLK);
RCC_err_status_t RCC_ClkIsReady(u32 RCC_CLK, u32 *CLK_RDY);
RCC_err_status_t RCC_EnablePeripheralClock(u32 peripheral);
RCC_err_status_t RCC_DisablePeripheralClock(u32 peripheral);

#endif /* RCC_H_ */