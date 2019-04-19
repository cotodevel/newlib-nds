

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
	DTCM : ORIGIN = 0x0b000000, LENGTH = 16K	
	ITCM : ORIGIN = 0x01000000, LENGTH = 32K	/* alternate 0x00000000 vectors here */
	GBAROM : ORIGIN = 0x08000000, LENGTH = 32M
	EWRAM : ORIGIN = 0x02000000, LENGTH = 4M
}

_itcm_start = ORIGIN(ITCM);
_itcm_end = ORIGIN(ITCM)	+	LENGTH(ITCM);

_ewram_start = ORIGIN(EWRAM);
_ewram_end = ORIGIN(EWRAM)	+	LENGTH(EWRAM);

_gba_start = ORIGIN(GBAROM);
_gba_end = ORIGIN(GBAROM)	+	LENGTH(GBAROM);

_dtcm_start = ORIGIN(DTCM);
_dtcm_end = ORIGIN(DTCM)	+	LENGTH(DTCM);

/* ARM9 Specific */
_arm9_irqcheckbits = ORIGIN(DTCM) + 0x3FF8;	/* __irq_flags */
_arm9_irqhandler = ORIGIN(DTCM) + 0x3FFC;	/* __irq_vector */

/* ARM ABI says stacks are full decreasing */
sp_SVC	= _dtcm_end  - 0x200;	/* reset, swi exception*/
sp_IRQ	= sp_SVC - 0x200;	/*irq exception*/
sp_FIQ	= sp_IRQ - 0x200;	/* fiq exception */
sp_ABT	= sp_FIQ - 0x200;	/* prefetch / data aborts exception */
sp_UND	= sp_ABT - 0x200;	/* undefined exception */
sp_USR	= sp_UND - 0x200;	/* usr / sys stacks */

ENTRY (_start)
SECTIONS
{
	.init : ALIGN(4) { __init_start__ = .;	/* used by TGDS-Newlib C/C++ code */
		. = ALIGN(4);
		KEEP(*(.init*))
	} > EWRAM = 0xff
	__init_end__ = .;
	. = ALIGN(4);
	.text : ALIGN(4) {				/* used by TGDS-Newlib C/C++ code */
		__text_start__ = .;
		. = ALIGN(4);
		*(.text*)
	} > EWRAM = 0xff
	__text_end__ = .;
	. = ALIGN(4);
	.data : ALIGN(4) {				/* used by TGDS-Newlib C/C++ code */
		__data_start__ = .;
		. = ALIGN(4);
		*(.data)
		*(.data.*)
		*(.gnu.linkonce.d*)
		*(.gnu.linkonce.t*)
	} > EWRAM = 0xff
	__data_end__ = .;
	. = ALIGN(4);
	.rodata : ALIGN(4) {			/* used by TGDS-Newlib C/C++ code */
		__rodata_start__ = .;
		. = ALIGN(4);
		*(.rdata)
		*(.rodata)
		*(.rodata.*)
    	*(.gnu.linkonce.r.*)
	} > EWRAM = 0xff
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
	} > EWRAM = 0xff
	__bss_vma_end = .;
	. = ALIGN(4);
	.ARM.exidx : ALIGN(4) {			/* not used at all, but some code rely on ARM debugging symbols */
		__exidx_start = .;
		*(.ARM.exidx)
		*(.ARM.exidx*)
		*(.gnu.linkonce.armexidx.)
		*(.gnu.linkonce.armexidx.*)
	} > EWRAM = 0xff
    __exidx_end = .;
	. = ALIGN(4);
	.fini : ALIGN(4) {				/* used by TGDS-Newlib C/C++ code */
		__fini_start__ = .;
		. = ALIGN(4);
		*(.fini)
		*(.fini*)
	} > EWRAM = 0xff
	__fini_end__ = .;
	__lib__end__ = .;
	. = ALIGN(4);
	__itcm_vma_start = .;
	.itcm : ALIGN(4) {
		_vectors_start = .;
		__vectors_vma_start = _vectors_start;
		. = ALIGN(4);
		KEEP (*(.vectors*))
		_vectors_end = .;
		KEEP (*(.itcm*))
	} > ITCM AT > EWRAM
	__itcm_vma_end__ = .;
	__dtcm_vma_start = .;
	.dtcm : ALIGN(4) {
		. = ALIGN(4);
		KEEP (*(.dtcm*))
	} > DTCM AT > EWRAM
	__dtcm_vma_end__ = .;
	. = ALIGN(64);
	__vma_stub_end__ = __lib__end__ + SIZEOF(.itcm) + SIZEOF(.dtcm);
}
