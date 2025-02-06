#ifndef _GPIO_H_
#define _GPIO_H_

#include "STD_TYPES.h"
// GPIO Registers base address
#define GPIOA_BASE_ADDR      0x40020000U
#define GPIOB_BASE_ADDR      0x40020400U
#define GPIOC_BASE_ADDR      0x40020800U
#define GPIOD_BASE_ADDR      0x40020C00U
#define GPIOE_BASE_ADDR      0x40021000U
#define GPIOH_BASE_ADDR      0x40021C00U

// GPIO Registers Pointer Definitions
#define GPIOA               ((GPIO_TypeDef *)GPIOA_BASE_ADDR)
#define GPIOB               ((GPIO_TypeDef *)GPIOB_BASE_ADDR)
#define GPIOC               ((GPIO_TypeDef *)GPIOC_BASE_ADDR)
#define GPIOD               ((GPIO_TypeDef *)GPIOD_BASE_ADDR)
#define GPIOE               ((GPIO_TypeDef *)GPIOE_BASE_ADDR)
#define GPIOH               ((GPIO_TypeDef *)GPIOH_BASE_ADDR)

// GPIO Registers Structure
typedef struct {
    volatile u32 MODER;          // GPIO port mode register,               Offset: 0x00
    volatile u32 OTYPER;         // GPIO port output type register,        Offset: 0x04
    volatile u32 OSPEEDR;        // GPIO port output speed register,       Offset: 0x08
    volatile u32 PUPDR;          // GPIO port pull-up/pull-down register,  Offset: 0x0C
    volatile u32 IDR;            // GPIO port input data register,         Offset: 0x10
    volatile u32 ODR;            // GPIO port output data register,        Offset: 0x14
    volatile u32 BSRR;           // GPIO port bit set/reset register,      Offset: 0x18
    volatile u32 LCKR;           // GPIO port configuration lock register, Offset: 0x1C
    volatile u32 AFR[2];         // GPIO alternate function registers,     Offset: 0x20-0x24
} GPIO_TypeDef;

// GPIO Configuration Structure
typedef struct {
    GPIO_Port_t port;                // GPIO port (e.g., GPIO_PORT_A)
    GPIO_Pin_t pin;                  // GPIO pin (e.g., GPIO_PIN_5)
    GPIO_PinMode_t mode;             // GPIO pin mode (input, output, alternate, analog)
    GPIO_OutputType_t outputType;    // GPIO output type (push-pull, open-drain)
    GPIO_InputType_t inputType;      // GPIO input type (no pull, pull-up, pull-down)
    GPIO_OutputSpeed_t speed;        // GPIO output speed (low, medium, high, very high)
} GPIO_InitCFG_t;

// GPIO Pin Mode Enumeration
typedef enum {
    GPIO_PIN_MODE_INPUT = 0,         // Input mode
    GPIO_PIN_MODE_OUTPUT,            // Output mode
    GPIO_PIN_MODE_ALTERNATE,         // Alternate function mode
    GPIO_PIN_MODE_ANALOG             // Analog mode
} GPIO_PinMode_t;

// GPIO Output Type Enumeration
typedef enum {
    GPIO_OUTPUT_TYPE_PP = 0,  // Push-pull output
    GPIO_OUTPUT_TYPE_OD       // Open-drain output
} GPIO_OutputType_t;

// GPIO Input Type Enumeration
typedef enum {
    GPIO_INPUT_TYPE_NO_PULL = 0,     // No pull-up/pull-down
    GPIO_INPUT_TYPE_PULL_UP,         // Pull-up resistor
    GPIO_INPUT_TYPE_PULL_DOWN        // Pull-down resistor
} GPIO_InputType_t;

// GPIO Output Speed Enumeration
typedef enum {
    GPIO_OUTPUT_SPEED_LOW = 0,       // Low speed
    GPIO_OUTPUT_SPEED_MEDIUM,        // Medium speed
    GPIO_OUTPUT_SPEED_HIGH,          // High speed
    GPIO_OUTPUT_SPEED_VERY_HIGH      // Very high speed
} GPIO_OutputSpeed_t;

// GPIO Pin Enumeration
typedef enum {
    GPIO_PIN_0 = 0,                  // Pin 0
    GPIO_PIN_1,                      // Pin 1
    GPIO_PIN_2,                      // Pin 2
    GPIO_PIN_3,                      // Pin 3
    GPIO_PIN_4,                      // Pin 4
    GPIO_PIN_5,                      // Pin 5
    GPIO_PIN_6,                      // Pin 6
    GPIO_PIN_7,                      // Pin 7
    GPIO_PIN_8,                      // Pin 8
    GPIO_PIN_9,                      // Pin 9
    GPIO_PIN_10,                     // Pin 10
    GPIO_PIN_11,                     // Pin 11
    GPIO_PIN_12,                     // Pin 12
    GPIO_PIN_13,                     // Pin 13
    GPIO_PIN_14,                     // Pin 14
    GPIO_PIN_15                      // Pin 15
} GPIO_Pin_t;

// GPIO Port Enumeration
typedef enum {
    GPIO_PORT_A = 0,                 // Port A
    GPIO_PORT_B,                     // Port B
    GPIO_PORT_C,                     // Port C
    GPIO_PORT_D,                     // Port D
    GPIO_PORT_E,                     // Port E
    GPIO_PORT_H                      // Port H
} GPIO_Port_t;

// GPIO Error Status Enumeration
typedef enum {
    GPIO_OK = 0,                     // Operation successful
    GPIO_NOK                         // Operation failed
} GPIO_ErrorStatus_t;

typedef enum {
    GPIO_PIN_RESET = 0,
    GPIO_PIN_SET
} GPIO_PinState;

typedef enum {
    GPIO_AF0 = 0,
    GPIO_AF1,
    GPIO_AF2,
    GPIO_AF3,
    GPIO_AF4,
    GPIO_AF5,
    GPIO_AF6,
    GPIO_AF7,
    GPIO_AF8,
    GPIO_AF9,
    GPIO_AF10,
    GPIO_AF11,
    GPIO_AF12,
    GPIO_AF13,
    GPIO_AF14,
    GPIO_AF15
} GPIO_AlternateFunction_t;

#endif // _GPIO_H