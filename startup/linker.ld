MEMORY {
    SRAM    (rwx)   : ORIGIN = 0x20000000 , LENGTH = 128k
    FLASH   (rx)    : ORIGIN = 0x08000000 , LENGTH = 1024k
    CCM     (rwx)   : ORIGIN = 0x10000000 , LENGTH = 64k
}

__STACK_START__     = ORIGIN(SRAM) + LENGTH(SRAM);
__SRAM_START__      = ORIGIN(SRAM);
__SRAM_END__        = ORIGIN(SRAM) + LENGTH(SRAM);
__CCM_START__       = ORIGIN(CCM);
__CCM_END__         = ORIGIN(CCM) + LENGTH(CCM);

OUTPUT_FORMAT ("elf32-littlearm", "elf32-bigarm", "elf32-littlearm")

EXTERN(Reset_Handler)

ENTRY(__start)

SECTIONS {
    .vector : ALIGN(4)
    {
        __vector_start__    = ABSOLUTE(.);
        *(.vectors)
        __vector__end__     = .;
    } > FLASH

    .text :
    {
        __text_start__  = .;
        *(.text)
        __text_end__    = .;
    } > FLASH
    
    .rodata : 
    {
        __rodata_start__    = .;
        *(.rodata)
        __rodata_end__      = .; 
    } > FLASH

    .data :
    {
        __data_load_addr__  = LOADADDR(.data);
        __data_start__      = .;
        *(.data)
        __data_end__        = .;
    } > SRAM AT > FLASH

    .bss :
    {
        __bss_load_addr__   = LOADADDR(.bss);
        __bss_start__       = .;
        *(.bss)
        __bss_end__         = .;
    } > SRAM AT > FLASH
}