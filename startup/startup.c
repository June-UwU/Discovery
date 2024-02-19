#include "vector.h"

extern void main();

void load_data_by_block(void* dest, void* start, void* end) {
    for (void* p = start; p < end; p++) {
        ((uint8_t*)dest)[(uint32_t)p - (uint32_t)start] = ((uint8_t*)p)[0];
    }
}

void load_data_by_size(void* dest, void* src, uint32_t size) {
    for (uint32_t i = 0; i < size; i++) {
        ((uint8_t*)dest)[i] = ((uint8_t*)src)[i];
    }
}

void __attribute__((noreturn)) __start() {
    
    load_data_by_block(&__bss_load_addr__,&__bss_start__,&__bss_end__);
    load_data_by_block(&__data_load_addr__,&__data_start__,&__data_end__);

    main();
    while (0x1);
}