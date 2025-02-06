#include "rcc.h"
#include "stdint.h"

typedef struct
{
    volatile uint32_t CR;         // RCC clock control register,                Offset: 0x00
    volatile uint32_t PLLCFGR;    // RCC PLL configuration register,            Offset: 0x04
    volatile uint32_t CFGR;       // RCC clock configuration register,          Offset: 0x08
    volatile uint32_t CIR;        // RCC clock interrupt register,              Offset: 0x0C
    volatile uint32_t AHB1RSTR;   // RCC AHB1 peripheral reset register,        Offset: 0x10
    volatile uint32_t AHB2RSTR;   // RCC AHB2 peripheral reset register,        Offset: 0x14
    volatile uint32_t AHB3RSTR;   // RCC AHB3 peripheral reset register,        Offset: 0x18
    uint32_t RESERVED0;           // Reserved,                                  Offset: 0x1C
    volatile uint32_t APB1RSTR;   // RCC APB1 peripheral reset register,        Offset: 0x20
    volatile uint32_t APB2RSTR;   // RCC APB2 peripheral reset register,        Offset: 0x24
    uint32_t RESERVED1[2];        // Reserved,                             Offset: 0x28-0x2C
    volatile uint32_t AHB1ENR;    // RCC AHB1 peripheral clock enable register, Offset: 0x30
    volatile uint32_t AHB2ENR;    // RCC AHB2 peripheral clock enable register, Offset: 0x34
    volatile uint32_t AHB3ENR;    // RCC AHB3 peripheral clock enable register, Offset: 0x38
    uint32_t RESERVED2;           // Reserved,                                  Offset: 0x3C
    volatile uint32_t APB1ENR;    // RCC APB1 peripheral clock enable register, Offset: 0x40
    volatile uint32_t APB2ENR;    // RCC APB2 peripheral clock enable register, Offset: 0x44
    uint32_t RESERVED3[2];        // Reserved,                             Offset: 0x48-0x4C
    volatile uint32_t AHB1LPENR;  // RCC AHB1 peripheral clock enable in low power mode register, Offset: 0x50
    volatile uint32_t AHB2LPENR;  // RCC AHB2 peripheral clock enable in low power mode register, Offset: 0x54
    volatile uint32_t AHB3LPENR;  // RCC AHB3 peripheral clock enable in low power mode register, Offset: 0x58
    uint32_t RESERVED4;           // Reserved,                               Offset: 0x5C
    volatile uint32_t APB1LPENR;  // RCC APB1 peripheral clock enable in low power mode register, Offset: 0x60
    volatile uint32_t APB2LPENR;  // RCC APB2 peripheral clock enable in low power mode register, Offset: 0x64
    uint32_t RESERVED5[2];        // Reserved,                                 Offset: 0x68-0x6C
    volatile uint32_t BDCR;       // RCC Backup domain control register,            Offset: 0x70
    volatile uint32_t CSR;        // RCC clock control & status register,           Offset: 0x74
    uint32_t RESERVED6[2];        // Reserved,                                 Offset: 0x78-0x7C
    volatile uint32_t SSCGR;      // RCC spread spectrum clock generation register, Offset: 0x80
    volatile uint32_t PLLI2SCFGR; // RCC PLLI2S configuration register,             Offset: 0x84
    volatile uint32_t PLLSAICFGR; // RCC PLLSAI configuration register,             Offset: 0x88
    volatile uint32_t DCKCFGR;    // RCC dedicated clocks configuration register,   Offset: 0x8C
} RCC_REGISTERS;

RCC_err_status_t RCC_ClkEnable(uint32_t RCC_CLK)
{
    RCC_err_status_t Loc_Status = RCC_OK;
    switch (RCC_CLK)
    {
    case HSI_CLK:
        RCC->CR |= RCC_CLK_HSI;
        break;
    case HSE_CLK:
        RCC->CR |= RCC_CLK_HSE;
        break;
    case PLL_CLK:
        RCC->CR |= RCC_CLK_PLL;
        break;

    default:
        Loc_Status = RCC_NOK;
        break;
    }
    return RCC_OK;
}

RCC_err_status_t RCC_ClkSel(uint32_t RCC_CLK)
{
    RCC_err_status_t Loc_Status = RCC_OK;
    uint32_t isReady;
    RCC_ClkIsReady(RCC_CLK, &isReady);

    if (!isReady)
    {
        return RCC_NOK;
    }
    else
    {
        switch (RCC_CLK)
        {
        case HSI_CLK:

            RCC->CFGR = (RCC->CFGR & SW_CLR);
            break;
        case HSE_CLK:
            RCC->CFGR = (RCC->CFGR & SW_CLR) | SW_HSE;
            break;
        case PLL_CLK:
            RCC->CFGR = (RCC->CFGR & SW_CLR) | SW_PLL;
            break;

        default:
            Loc_Status = RCC_NOK;
            break;
        }
    }
    return RCC_OK;
}

RCC_err_status_t RCC_ClkIsReady(uint32_t RCC_CLK, uint32_t *CLK_RDY)
{
    switch (RCC_CLK)
    {
    case HSI_CLK:
        *CLK_RDY = (RCC->CR >> HSI_RDY_BIT) & 0x1;
        break;
    case HSE_CLK:
        *CLK_RDY = (RCC->CR >> HSE_RDY_BIT) & 0x1;
        break;
    case PLL_CLK:
        *CLK_RDY = (RCC->CR >> PLL_RDY_BIT) & 0x1;
        break;
    default:
        break;
    }

    return RCC_OK;
}

RCC_err_status_t RCC_PLL_Config(const PLL_CONFIG_t *pll_config_ptr)
{
    // Check for NULL pointer
    if (pll_config_ptr == NULL)
    {
        return RCC_NOK;
    }

    // Validate PLLM
    if (pll_config_ptr->PLLM < PLLM_MIN || pll_config_ptr->PLLM > PLLM_MAX)
    {
        return RCC_NOK;
    }

    // Validate PLLN
    if (pll_config_ptr->PLLN < PLLN_MIN || pll_config_ptr->PLLN > PLLN_MAX)
    {
        return RCC_NOK;
    }

    // Validate PLLP
    switch (pll_config_ptr->PLLP)
    {
    case 2:
    case 4:
    case 6:
    case 8:
        // Valid PLLP value
        break;
    default:
        return RCC_NOK; // Invalid PLLP value
    }

    // Validate PLLQ
    if (pll_config_ptr->PLLQ < PLLQ_MIN || pll_config_ptr->PLLQ > PLLQ_MAX)
    {
        return RCC_NOK;
    }

    // Validate PLLSRC
    if (pll_config_ptr->PLLSRC != PLLSRC_HSI && pll_config_ptr->PLLSRC != PLLSRC_HSE)
    {
        return RCC_NOK;
    }

    // Configure PLL if all inputs are valid
    RCC->PLLCFGR = (pll_config_ptr->PLLM << 0) |    // Bits 0-5
                   (pll_config_ptr->PLLN << 6) |    // Bits 6-14
                   (pll_config_ptr->PLLP << 16) |   // Bits 16-17
                   (pll_config_ptr->PLLSRC << 22) | // Bit 22
                   (pll_config_ptr->PLLQ << 24);    // Bits 24-27

    return RCC_OK;
}

RCC_err_status_t RCC_EnablePeripheralClock(uint32_t peripheral)
{
    if (peripheral >= AHB1_START && peripheral <= AHB1_END)
    {
        RCC->AHB1ENR |= (1 << peripheral);
    }
    else if (peripheral >= AHB2_START && peripheral <= AHB2_END)
    {
        RCC->AHB2ENR |= (1 << peripheral);
    }
    else if (peripheral >= APB1_START && peripheral <= APB1_END)
    {
        RCC->APB1ENR |= (1 << peripheral);
    }
    else if (peripheral >= APB2_START && peripheral <= APB2_END)
    {
        RCC->APB2ENR |= (1 << peripheral);
    }
    else
    {
        return RCC_INVALID_PERIPHERAL; // Invalid peripheral
    }
    return RCC_OK;
}

RCC_err_status_t RCC_DisablePeripheralClock(uint32_t peripheral)
{
    if (peripheral >= AHB1_START && peripheral <= AHB1_END)
    {
        RCC->AHB1ENR &= ~(1 << peripheral);
    }
    else if (peripheral >= AHB2_START && peripheral <= AHB2_END)
    {
        RCC->AHB2ENR &= ~(1 << peripheral);
    }
    else if (peripheral >= APB1_START && peripheral <= APB1_END)
    {
        RCC->APB1ENR &= ~(1 << peripheral);
    }
    else if (peripheral >= APB2_START && peripheral <= APB2_END)
    {
        RCC->APB2ENR &= ~(1 << peripheral);
    }
    else
    {
        return RCC_INVALID_PERIPHERAL; // Invalid peripheral
    }
    return RCC_OK;
}

RCC_err_status_t RCC_ResetPeripheral(uint32_t peripheral)
{
    if (peripheral >= AHB1_START && peripheral <= AHB1_END)
    {
        RCC->AHB1RSTR |= (1 << peripheral);
    }
    else if (peripheral >= AHB2_START && peripheral <= AHB2_END)
    {
        RCC->AHB2RSTR |= (1 << peripheral);
    }
    else if (peripheral >= APB1_START && peripheral <= APB1_END)
    {
        RCC->APB1RSTR |= (1 << peripheral);
    }
    else if (peripheral >= APB2_START && peripheral <= APB2_END)
    {
        RCC->APB2RSTR |= (1 << peripheral);
    }
    else
    {
        return RCC_INVALID_PERIPHERAL; // Invalid peripheral
    }
    return RCC_OK;
}