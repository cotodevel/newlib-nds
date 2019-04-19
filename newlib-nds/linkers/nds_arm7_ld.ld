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

/* Coto: own linker stuff. Written by me. for NDS hardware (non DSi-3DS)*/
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
	.init : ALIGN(4) { __init_start__ = .;	/* used by TGDS-Newlib C/C++ code */
		. = ALIGN(4);
		KEEP(*(.init*))
	} > IWRAM = 0xff
	__init_end__ = .;
	. = ALIGN(4);
	.text : ALIGN(4) {				/* used by TGDS-Newlib C/C++ code */
		__text_start__ = .;
		. = ALIGN(4);
		*(.text*)
	} > IWRAM = 0xff
	__text_end__ = .;
	. = ALIGN(4);
	.data : ALIGN(4) {				/* used by TGDS-Newlib C/C++ code */
		__data_start__ = .;
		. = ALIGN(4);
		*(.data)
		*(.data.*)
		*(.gnu.linkonce.d*)
		*(.gnu.linkonce.t*)
	} > IWRAM = 0xff
	__data_end__ = .;
	. = ALIGN(4);
	.rodata : ALIGN(4) {			/* used by TGDS-Newlib C/C++ code */
		__rodata_start__ = .;
		. = ALIGN(4);
		*(.rdata)
		*(.rodata)
		*(.rodata.*)
    	*(.gnu.linkonce.r.*)
	} > IWRAM = 0xff
	__rodata_end__ = .;
	. = ALIGN(4);
	.bss (NOLOAD): {				/* used by TGDS-Newlib C/C++ code */
		__bss_vma_start = .;
		. = ALIGN(4);
		*(COMMON)					/* libc requires these for uninitialized objects, include any heap uninit vars*/
		*(.dynbss*)
		*(.bss*)
		*(.bss)
		*(.gnu.linkonce.b*.)
	} > IWRAM = 0xff
	__bss_vma_end = .;
	. = ALIGN(4);
	.ARM.exidx : ALIGN(4) {			/* not used at all, but some code rely on ARM debugging symbols */
		__exidx_start = .;
		*(.ARM.exidx)
		*(.ARM.exidx*)
		*(.gnu.linkonce.armexidx.)
		*(.gnu.linkonce.armexidx.*)
	} > IWRAM = 0xff
    __exidx_end = .;
	. = ALIGN(4);
	.fini : ALIGN(4) {				/* used by TGDS-Newlib C/C++ code */
		__fini_start__ = .;
		. = ALIGN(4);
		*(.fini)
		*(.fini*)
	} > IWRAM = 0xff
	__fini_end__ = .;
	__lib__end__ = .;
	. = ALIGN(64);
	__vma_stub_end__ = __lib__end__ ;
}
