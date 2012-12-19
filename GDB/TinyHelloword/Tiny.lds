ENTRY(nomain)

SECTIONS
{
	. = 0x00010000 + SIZEOF_HEADERS;
	tinytext : {*(.text) *(.data) *(.rodata)}
	/DISCARD/ : {*(.comment)}
}

