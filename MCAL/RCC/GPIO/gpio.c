#include "gpio.h"

GPIO_ErrorStatus_t GPIO_Init(GPIO_TypeDef *GPIOx, GPIO_InitCFG_t *InitStruct)
{
    // Validate input parameters
    if (GPIOx == NULL || InitStruct == NULL)
    {
        return GPIO_NOK; // Invalid input
    }

    // Validate pin number
    if (InitStruct->pin > GPIO_PIN_15)
    {
        return GPIO_NOK; // Invalid pin number
    }
    //////////////////* REMEMBER TO Enable the GPIO port clock IN UR MAIN APPLICATION *////////////////////////

    // Configure the GPIO pin mode
    GPIOx->MODER &= ~(0x3U << (InitStruct->pin * 2));            // Clear existing mode
    GPIOx->MODER |= (InitStruct->mode << (InitStruct->pin * 2)); // Set new mode

    // Configure the output type (only for output or alternate mode)
    if (InitStruct->mode == GPIO_PIN_MODE_OUTPUT || InitStruct->mode == GPIO_PIN_MODE_ALTERNATE)
    {
        GPIOx->OTYPER &= ~(0x1U << InitStruct->pin);                  // Clear existing output type
        GPIOx->OTYPER |= (InitStruct->outputType << InitStruct->pin); // Set new output type
    }

    // Configure the output speed
    GPIOx->OSPEEDR &= ~(0x3U << (InitStruct->pin * 2));             // Clear existing speed
    GPIOx->OSPEEDR |= (InitStruct->speed << (InitStruct->pin * 2)); // Set new speed

    // Configure the input type (pull-up/pull-down)
    GPIOx->PUPDR &= ~(0x3U << (InitStruct->pin * 2));                 // Clear existing pull-up/pull-down
    GPIOx->PUPDR |= (InitStruct->inputType << (InitStruct->pin * 2)); // Set new pull-up/pull-down

    return GPIO_OK;
}
// Write a value to a GPIO pin (output mode)
GPIO_ErrorStatus_t GPIO_WritePin(GPIO_TypeDef *GPIOx, u16 Pin, GPIO_PinState PinState)
{
    // Validate input parameters
    if (GPIOx == NULL || Pin > GPIO_PIN_15)
    {
        return GPIO_NOK; // Invalid input
    }

    if (PinState == GPIO_PIN_SET)
    {
        GPIOx->BSRR = (1 << Pin); // Set the pin
    }
    else
    {
        GPIOx->BSRR = (1 << (Pin + 16)); // Reset the pin
    }

    return GPIO_OK;
}
// Read the state of a GPIO pin (input mode)
GPIO_ErrorStatus_t GPIO_ReadPin(GPIO_TypeDef *GPIOx, u16 Pin, GPIO_PinState *PinState)
{
    // Validate input parameters
    if (GPIOx == NULL || Pin > GPIO_PIN_15 || PinState == NULL)
    {
        return GPIO_NOK; // Invalid input
    }

    *PinState = (GPIOx->IDR & (1 << Pin)) ? GPIO_PIN_SET : GPIO_PIN_RESET;
    return GPIO_OK;
}
// Toggle the state of a GPIO pin (output mode)
GPIO_ErrorStatus_t GPIO_TogglePin(GPIO_TypeDef *GPIOx, u16 Pin)
{
    // Validate input parameters
    if (GPIOx == NULL || Pin > GPIO_PIN_15)
    {
        return GPIO_NOK; // Invalid input
    }

    GPIOx->ODR ^= (1 << Pin); // Toggle the pin
    return GPIO_OK;
}
// Set the alternate function for a GPIO pin (alternate function mode)
GPIO_ErrorStatus_t GPIO_SetAlternateFunction(GPIO_TypeDef *GPIOx, u16 Pin, u8 AlternateFunction)
{
    // Validate input parameters
    if (GPIOx == NULL || Pin > GPIO_PIN_15 || AlternateFunction > 15)
    {
        return GPIO_NOK; // Invalid input
    }

    u8 afr_index = Pin / 8;        // Determine which AFR register to use (AFRL or AFRH)
    u8 afr_offset = (Pin % 8) * 4; // Calculate the bit offset within the AFR register

    // Clear the existing alternate function bits
    GPIOx->AFR[afr_index] &= ~(0xF << afr_offset);

    // Set the new alternate function bits
    GPIOx->AFR[afr_index] |= (AlternateFunction << afr_offset);

    return GPIO_OK;
}

/*Lock and unlock the configuration of a GPIO pin (input, output, alternate, analog)
call the func one time to lock and twise to unlock*/

GPIO_ErrorStatus_t GPIO_LockPin(GPIO_TypeDef *GPIOx, u16 Pin)
{
    // Validate input parameters
    if (GPIOx == NULL || Pin > GPIO_PIN_15)
    {
        return GPIO_NOK; // Invalid input
    }

    // Write the lock sequence to the LCKR register
    u32 lock = (1 << Pin) | (1 << 16); // Set the lock bit and the pin bit
    GPIOx->LCKR = lock;
    GPIOx->LCKR = (1 << Pin); // Write again to confirm
    GPIOx->LCKR = lock;       // Write again to confirm
    u32 is_locked = GPIOx->LCKR; // Read the LCKR register to check if the lock was successful
    return GPIO_OK;
}
