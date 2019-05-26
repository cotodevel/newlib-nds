/*
			Copyright (C) 2017  Coto
This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301
USA
*/

/* Coto: ARM7 linker file for NDS ARM7 processor, could be adapted for DSi-3DS */
OUTPUT_FORMAT("elf32-littlearm")

/* attributes can actually help in debugging because if you try to move functions to DTCM, for example, compiler will rant since DTCM is DATA only path and not execution*/
MEMORY
{
	IWRAM	(rwx)	: ORIGIN = 0x03800000, LENGTH = 64K
}

_iwram_start = ORIGIN(IWRAM);
_iwram_end = ORIGIN(IWRAM)	+	LENGTH(IWRAM);

/* ARM7 Specific */
_arm7_irqcheckbits = 0x04000000 - 8;	/* __irq_flags */
_arm7_irqhandler = 0x04000000 - 4;	/* __irq_vector */

/* ARM ABI says stacks are full decreasing */
sp_SVC	= _iwram_end - 0x100;	/* reset, swi exception*/
sp_IRQ	= sp_SVC - 0x100;	/*irq exception*/
sp_FIQ	= sp_IRQ - 0x100;	/* fiq exception */
sp_ABT	= sp_FIQ - 0x100;	/* prefetch / data aborts exception */
sp_UND	= sp_ABT - 0x100;	/* undefined exception */
sp_USR	= sp_UND - 0x100;	/* usr / sys stacks */

ENTRY (_start)
SECTIONS
{
	.init : ALIGN(4) { 			/* Entrypoint */
		PROVIDE (__init_start__ = ABSOLUTE(.));
		KEEP(*(.init*))
		PROVIDE (__init_end__ = ABSOLUTE(.));
	} > IWRAM = 0xff
	
	. = ALIGN(4);
	
	.data : ALIGN(4) {				/* used by TGDS-Newlib C/C++ code */
		PROVIDE (__data_start__ = ABSOLUTE(.));
		*(.data)
		*(.data.*)
		*(.gnu.linkonce.d*)
		*(.gnu.linkonce.t*)
		PROVIDE (__data_end__ = ABSOLUTE(.));
	} > IWRAM = 0xff
	
	. = ALIGN(4);
	
	.rodata : ALIGN(4) {			/* used by TGDS-Newlib C/C++ code */
		PROVIDE (__rodata_start__ = ABSOLUTE(.));
		*(.rdata)
		*(.rodata)
		*(.rodata.*)
    	*(.gnu.linkonce.r.*)
		PROVIDE (__rodata_end__ = ABSOLUTE(.));
	} > IWRAM = 0xff
	
	. = ALIGN(4);
	
	.bss (NOLOAD): {				/* used by TGDS-Newlib C/C++ code */
		PROVIDE (__bss_vma_start = ABSOLUTE(.));
		*(.dynbss*)
		*(.bss*)
		*(.bss)
		*(.gnu.linkonce.b*.)
		PROVIDE (__bss_vma_end = ABSOLUTE(.));
	} > IWRAM = 0xff
	
	. = ALIGN(4);
	
	.text : ALIGN(4) {				/* used by TGDS-Newlib C/C++ code */
		PROVIDE (__text_start__ = ABSOLUTE(.));
		KEEP(*(.text*))
		KEEP(*(COMMON))					/* libc requires these for uninitialized objects, include any heap uninit vars*/
		PROVIDE (__text_end__ = ABSOLUTE(.));
	} > IWRAM = 0xff
	
	. = ALIGN(4);
	
	.ARM.exidx : ALIGN(4) {			/* not used at all, but some code rely on ARM debugging symbols */
		PROVIDE (__exidx_start = ABSOLUTE(.));
		*(.ARM.exidx)
		*(.ARM.exidx*)
		*(.gnu.linkonce.armexidx.)
		*(.gnu.linkonce.armexidx.*)
		PROVIDE (__exidx_end = ABSOLUTE(.));	
	} > IWRAM = 0xff
	
	. = ALIGN(4);
	
	/*
     * Stabs le debugging sections.
     *
     */

    .stab          0 : { *(.stab) }
    .stabstr       0 : { *(.stabstr) }
    .stab.excl     0 : { *(.stab.excl) }
    .stab.exclstr  0 : { *(.stab.exclstr) }
    .stab.index    0 : { *(.stab.index) }
    .stab.indexstr 0 : { *(.stab.indexstr) }
    .comment       0 : { *(.comment) }
    /* DWARF debug sections.
       Symbols in the DWARF debugging sections are relative to the beginning
       of the section so we begin them at 0.  */
    /* DWARF 1 */
    .debug          0 : { *(.debug) }
    .line           0 : { *(.line) }
    /* GNU DWARF 1 extensions */
    .debug_srcinfo  0 : { *(.debug_srcinfo) }
    .debug_sfnames  0 : { *(.debug_sfnames) }
    /* DWARF 1.1 and DWARF 2 */
    .debug_aranges  0 : { *(.debug_aranges) }
    .debug_pubnames 0 : { *(.debug_pubnames) }
    /* DWARF 2 */
    .debug_info     0 : { *(.debug_info .gnu.linkonce.wi.*) }
    .debug_abbrev   0 : { *(.debug_abbrev) }
    .debug_line     0 : { *(.debug_line) }
    .debug_frame    0 : { *(.debug_frame) }
    .debug_str      0 : { *(.debug_str) }
    .debug_loc      0 : { *(.debug_loc) }
    .debug_macinfo  0 : { *(.debug_macinfo) }
    /* SGI/MIPS DWARF 2 extensions */
    .debug_weaknames 0 : { *(.debug_weaknames) }
    .debug_funcnames 0 : { *(.debug_funcnames) }
    .debug_typenames 0 : { *(.debug_typenames) }
    .debug_varnames  0 : { *(.debug_varnames) }
	
	. = ALIGN(4);
	
	.fini : ALIGN(4) {				/* used by TGDS-Newlib C/C++ code */
		PROVIDE (__fini_start__ = ABSOLUTE(.));
		*(.fini)
		*(.fini*)
		PROVIDE (__fini_end__ = ABSOLUTE(.));
		FILL(0x40);
	} > IWRAM = 0xff
	
	PROVIDE (__lib__end__ = __fini_end__);
	. = ALIGN(4);
	PROVIDE (__vma_stub_end__ = __lib__end__ + 0x40);
}
