#include "rcc.h"
#include "gpio.h"

void Delay(u32 count) {
    for (volatile u32 i = 0; i < count; i++);
}

int main(void) {
    // Enable GPIOA clock
    RCC->AHB1ENR |= (1 << 0); // Enable GPIOA clock

    // Configure GPIOA Pin 5 as output
    GPIO_InitCFG_t GPIO_InitStruct = {
        .port = GPIO_PORT_A,
        .pin = GPIO_PIN_5,
        .mode = GPIO_PIN_MODE_OUTPUT,
        .outputType = GPIO_OUTPUT_TYPE_PP,
        .inputType = GPIO_INPUT_TYPE_NO_PULL,
        .speed = GPIO_OUTPUT_SPEED_HIGH
    };

    // Initialize GPIO
    if (GPIO_Init(GPIOA, &GPIO_InitStruct) != GPIO_OK) {
        // Handle initialization error
        while (1); // Stuck here if initialization fails
    }

    while (1) {
        // Toggle GPIOA Pin 5
        if (GPIO_TogglePin(GPIOA, GPIO_PIN_5) != GPIO_OK) {
            // Handle toggle error
            while (1); // Stuck here if toggle fails
        }

        // Delay for visibility
        Delay(1000000); // Adjust the delay as needed
    }
}