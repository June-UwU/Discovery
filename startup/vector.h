#pragma once
#include <stdint.h>
#include "boards/stm32f407.h"

extern uint32_t __STACK_START__;
extern uint32_t __STACK_END__;
extern uint32_t __SRAM_START__;
extern uint32_t __SRAM_END__;
extern uint32_t __CCM_START__;
extern uint32_t __CCM_END__;
extern uint32_t __vector_start__;
extern uint32_t __vector_end__;
extern uint32_t __text_start__;
extern uint32_t __text_end__;
extern uint32_t __rodata_start__;
extern uint32_t __rodata_end__;
extern uint32_t __data_load_addr__;
extern uint32_t __data_start__;
extern uint32_t __data_end__;
extern uint32_t __bss_load_addr__;
extern uint32_t __bss_start__;
extern uint32_t __bss_end__;

extern __attribute__((noreturn,weak)) void __start();

void Reset_Handler(void);

// Define the number of vectors
#define NUM_VECTORS (16 + 82) // 16 Cortex-M system + 82 STM32F407

#define X(name) extern void name() __attribute__ ((weak, alias("Default_Handler")));
// Forward declaration of the default fault handlers
extern void Reset_Handler();
extern void NMI_Handler()          __attribute__ ((weak, alias("Default_Handler")));
extern void HardFault_Handler()    __attribute__ ((weak, alias("Default_Handler")));
extern void MemManage_Handler()    __attribute__ ((weak, alias("Default_Handler")));
extern void BusFault_Handler()     __attribute__ ((weak, alias("Default_Handler")));
extern void UsageFault_Handler()   __attribute__ ((weak, alias("Default_Handler")));
extern void SVC_Handler()          __attribute__ ((weak, alias("Default_Handler")));
extern void DebugMon_Handler()     __attribute__ ((weak, alias("Default_Handler")));
extern void PendSV_Handler()       __attribute__ ((weak, alias("Default_Handler")));
extern void SysTick_Handler()      __attribute__ ((weak, alias("Default_Handler")));
    // ... Define other IRQ handlers here ...
__BOARD_VECTOR_HANDLERS__

#undef X

#define X(name) name,
// The vector table. This can be copied to the RAM.
__attribute__ ((section(".vectors")))
void (* const g_pfnVectors[NUM_VECTORS])(void) = {
    (void(*)(void))((uint32_t)&__STACK_START__), // The initial stack pointer
    Reset_Handler,                        // The reset handler
    NMI_Handler,                          // The NMI handler
    HardFault_Handler,                    // The hard fault handler
    MemManage_Handler,                    // The MPU fault handler
    BusFault_Handler,                     // The bus fault handler
    UsageFault_Handler,                   // The usage fault handler
    0,                                    // Reserved
    0,                                    // Reserved
    0,                                    // Reserved
    0,                                    // Reserved
    SVC_Handler,                          // SVCall handler
    DebugMon_Handler,                     // Debug monitor handler
    0,                                    // Reserved
    PendSV_Handler,                       // The PendSV handler
    SysTick_Handler,                      // The SysTick handler
    // ... Initialize other vectors (IRQ handlers) here ...
    __BOARD_VECTOR_HANDLERS__
};


#undef X

void Reset_Handler() {
    __start();
    while (1);
}

// Default handler that is called if there is no application handler
void Default_Handler(void ) {
    while (1); 
}
