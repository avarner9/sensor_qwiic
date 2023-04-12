
_start = 0x08000188 ;

MEMORY
{
    FLASH (rx)      : ORIGIN = 0x08000000, LENGTH = 32K
    RAM (xrw)       : ORIGIN = 0x20000000, LENGTH = 6K
}

SECTIONS
{
    .intvectable    0x08000000 : { *(.intvectable) } > FLASH
    .text           : { *(.text); _text_sec_end = .;} > FLASH
	
	.data : {
		_data_sec_start = .;
		* (.data);
		_data_sec_end = .;
	} >RAM AT>FLASH
	
	.bss : {
		_bss_sec_start = .;
		* (.bss);
		_bss_sec_end = .;
	} >RAM
}
