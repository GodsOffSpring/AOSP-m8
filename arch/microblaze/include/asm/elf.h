/*
 * Copyright (C) 2008-2009 Michal Simek <monstr@monstr.eu>
 * Copyright (C) 2008-2009 PetaLogix
 * Copyright (C) 2006 Atmark Techno, Inc.
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License. See the file "COPYING" in the main directory of this archive
 * for more details.
 */

#ifndef _ASM_MICROBLAZE_ELF_H
#define _ASM_MICROBLAZE_ELF_H

#define EM_MICROBLAZE		189
#define EM_MICROBLAZE_OLD	0xbaab
#define ELF_ARCH		EM_MICROBLAZE

#define elf_check_arch(x)	((x)->e_machine == EM_MICROBLAZE \
				 || (x)->e_machine == EM_MICROBLAZE_OLD)

#define ELF_CLASS	ELFCLASS32

#ifndef __uClinux__


#include <asm/ptrace.h>
#include <asm/byteorder.h>

#ifndef ELF_GREG_T
#define ELF_GREG_T
typedef unsigned long elf_greg_t;
#endif

#ifndef ELF_NGREG
#define ELF_NGREG (sizeof(struct pt_regs) / sizeof(elf_greg_t))
#endif

#ifndef ELF_GREGSET_T
#define ELF_GREGSET_T
typedef elf_greg_t elf_gregset_t[ELF_NGREG];
#endif

#ifndef ELF_FPREGSET_T
#define ELF_FPREGSET_T

#define ELF_NFPREG	33	
typedef unsigned long elf_fpreg_t;
typedef elf_fpreg_t elf_fpregset_t[ELF_NFPREG];

#endif


#define ELF_ET_DYN_BASE         (0x08000000)

#ifdef __MICROBLAZEEL__
#define ELF_DATA	ELFDATA2LSB
#else
#define ELF_DATA	ELFDATA2MSB
#endif

#define ELF_EXEC_PAGESIZE	PAGE_SIZE


#define ELF_CORE_COPY_REGS(_dest, _regs)			\
	memcpy((char *) &_dest, (char *) _regs,		\
	sizeof(struct pt_regs));

#define ELF_HWCAP	(0)

#define ELF_PLATFORM  (NULL)

#define ELF_PLAT_INIT(_r, _f)				\
do {							\
	_r->r1 =  _r->r1 =  _r->r2 =  _r->r3 =		\
	_r->r4 =  _r->r5 =  _r->r6 =  _r->r7 =		\
	_r->r8 =  _r->r9 =  _r->r10 = _r->r11 =		\
	_r->r12 = _r->r13 = _r->r14 = _r->r15 =		\
	_r->r16 = _r->r17 = _r->r18 = _r->r19 =		\
	_r->r20 = _r->r21 = _r->r22 = _r->r23 =		\
	_r->r24 = _r->r25 = _r->r26 = _r->r27 =		\
	_r->r28 = _r->r29 = _r->r30 = _r->r31 =		\
	0;						\
} while (0)

#ifdef __KERNEL__
#define SET_PERSONALITY(ex) set_personality(PER_LINUX_32BIT)
#endif

#endif 

#endif 
