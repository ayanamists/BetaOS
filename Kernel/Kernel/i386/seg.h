//
//  seg.h
//  BetaOS
//
//  Created by Adam Kopeć on 4/25/16.
//  Copyright © 2016 Adam Kopeć. All rights reserved.
//

#ifndef seg_h
#define seg_h

#ifndef __ASSEMBLY__

#include <stdint.h>
#include <i386/sel.h>
#include <i386/pmap.h>
#include <sys/cdefs.h>

/*
 * i386 segmentation.
 */

static inline uint16_t
sel_to_selector(sel_t	sel) {
    union {
        sel_t		sel;
        uint16_t	selector;
    } tconv;

    tconv.sel = sel;

    return (tconv.selector);
}

static inline sel_t
selector_to_sel(uint16_t selector) {
    union {
        uint16_t	selector;
        sel_t		sel;
    } tconv;
    tconv.selector = selector;
    return (tconv.sel);
}


#define LDTSZ		8192                        /* size of the kernel ldt in entries */
#define LDT_SIZE    LDTSZ
#define	LDTSZ_MIN	SEL_TO_INDEX(USER_SETTABLE)
                    /* kernel ldt entries */

#define	GDTSZ		19
#define GDT_SIZE    GDTSZ
/*
 * Interrupt table is always 256 entries long.
 */
#define	IDTSZ		256
#define IDT_SIZE    IDTSZ

/*
 * Real segment descriptor.
 */
struct real_descriptor {
    uint32_t	limit_low:16,	/* limit 0..15 */
                base_low:16,	/* base  0..15 */
                base_med:8,     /* base  16..23 */
                access:8,       /* access byte */
                limit_high:4,	/* limit 16..19 */
                granularity:4,	/* granularity */
                base_high:8;	/* base 24..31 */
};
struct real_descriptor64 {
    uint32_t	limit_low16:16,	/* limit 0..15 */
                base_low16:16,	/* base  0..15 */
                base_med8:8,	/* base  16..23 */
                access8:8,      /* access byte */
                limit_high4:4,	/* limit 16..19 */
                granularity4:4,	/* granularity */
                base_high8:8,	/* base 24..31 */
                base_top32:32,	/* base 32..63 */
                reserved32:32;	/* reserved/zero */
};
struct real_gate {
    uint32_t	offset_low:16,	/* offset 0..15 */
                selector:16,
                word_count:8,
                access:8,
                offset_high:16;	/* offset 16..31 */
};
struct real_gate64 {
    uint32_t	offset_low16:16,	/* offset 0..15 */
                selector16:16,
                IST:3,
                zeroes5:5,
                access8:8,
                offset_high16:16,	/* offset 16..31 */
                offset_top32:32,	/* offset 32..63 */
                reserved32:32;		/* reserved/zero */
};

#define MAKE_REAL_DESCRIPTOR(base,lim,gran,acc) { \
    .limit_low = lim & 0xffff, \
    .limit_high = (lim >> 16) & 0xf, \
    .base_low = base & 0xffff, \
    .base_med = (base >> 16) & 0xff, \
    .base_high = (base >> 24) & 0xff, \
    .access = acc, \
    .granularity = gran \
}

/*
 * We build descriptors and gates in a 'fake' format to let the
 * fields be contiguous.  We shuffle them into the real format
 * at runtime.
 */
struct fake_descriptor {
    uint32_t	offset:32;          /* offset */
    uint32_t	lim_or_seg:20;		/* limit */
                                    /* or segment, for gate */
    uint32_t	size_or_wdct:4;		/* size/granularity */
                                    /* word count, for gate */
    uint32_t	access:8;           /* access */
};
struct fake_descriptor64 {
    uint64_t	offset64;           /* offset [0..31,32..63] */
    uint32_t	lim_or_seg:20;		/* limit */
                                    /* or segment, for gate */
    uint32_t	size_or_IST:4;		/* size/granularity */
                                    /* IST for gates */
    uint32_t	access:8;           /* access */
    uint32_t	reserved:32;		/* reserved/zero */
};

/*
 * Boot-time data for master (or only) CPU
 */
extern struct fake_descriptor	master_idt[IDTSZ];
extern struct real_descriptor	master_gdt[GDTSZ];
extern struct real_descriptor	master_ldt[LDTSZ];
//extern struct i386_tss          master_ktss;
extern struct sysenter_stack	master_sstk;

extern struct fake_descriptor64	master_idt64[IDTSZ];
extern struct x86_64_tss        master_ktss64;

#endif /* __ASSEMBLY__ */

#define	SZ_64		0x2			/* 64-bit segment */
#define	SZ_32		0x4			/* 32-bit segment */
#define	SZ_G		0x8			/* 4K limit field */

#define	ACC_A		0x01        /* accessed */
#define	ACC_TYPE	0x1e		/* type field: */

#define	ACC_TYPE_SYSTEM	0x00	/* system descriptors: */

#define	ACC_LDT         0x02	/* LDT */
#define	ACC_CALL_GATE_16 0x04	/* 16-bit call gate */
#define	ACC_TASK_GATE	0x05	/* task gate */
#define	ACC_TSS         0x09	/* task segment */
#define	ACC_CALL_GATE	0x0c	/* call gate */
#define	ACC_INTR_GATE	0x0e	/* interrupt gate */
#define	ACC_TRAP_GATE	0x0f	/* trap gate */

#define	ACC_TSS_BUSY	0x02	/* task busy */

#define	ACC_TYPE_USER	0x10	/* user descriptors */

#define	ACC_DATA	0x10        /* data */
#define	ACC_DATA_W	0x12        /* data, writable */
#define	ACC_DATA_E	0x14		/* data, expand-down */
#define	ACC_DATA_EW	0x16		/* data, expand-down, writable */
#define	ACC_CODE	0x18		/* code */
#define	ACC_CODE_R	0x1a		/* code, readable */
#define	ACC_CODE_C	0x1c		/* code, conforming */
#define	ACC_CODE_CR	0x1e		/* code, conforming, readable */
#define	ACC_PL		0x60		/* access rights: */
#define	ACC_PL_K	0x00		/* kernel access only */
#define	ACC_PL_U	0x60		/* user access */
#define	ACC_P		0x80		/* segment present */

/*
 * Components of a selector
 */
#define	SEL_LDTS	0x04		/* local selector */
#define	SEL_PL		0x03		/* privilege level: */
#define	SEL_PL_K	0x00		/* kernel selector */
#define	SEL_PL_U	0x03		/* user selector */

/*
 * Convert selector to descriptor table index.
 */
#define	sel_idx(sel)	(selector_to_sel(sel).index)
#define SEL_TO_INDEX(s)	((s)>>3)

#define NULL_SEG	0


/*
 * Kernel descriptors for MACH - 64-bit flat address space.
 */
#define KERNEL64_CS 	0x08		/* 1:  K64 code */
#define SYSENTER_CS 	0x0b 		/*     U32 sysenter pseudo-segment */
#define	KERNEL64_SS     0x10		/* 2:  KERNEL64_CS+8 for syscall */
#define USER_CS         0x1b		/* 3:  U32 code */
#define USER_DS         0x23		/* 4:  USER_CS+8 for sysret */
#define USER64_CS       0x2b		/* 5:  USER_CS+16 for sysret */
#define USER64_DS       USER_DS		/*     U64 data pseudo-segment */
#define KERNEL_LDT      0x30		/* 6:  */
                                    /* 7:  other 8 bytes of KERNEL_LDT */
#define KERNEL_TSS      0x40		/* 8:  */
                                    /* 9:  other 8 bytes of KERNEL_TSS */
#define KERNEL32_CS     0x50		/* 10: */
#define USER_LDT        0x58		/* 11: */
                                    /* 12: other 8 bytes of USER_LDT */
#define KERNEL_DS       0x68		/* 13: 32-bit kernel data */


#define SYSENTER_TF_CS	(USER_CS|0x10000)
#define	SYSENTER_DS     KERNEL64_SS	/* sysenter kernel data segment */

#ifdef __x86_64__
/*
 * 64-bit kernel LDT descriptors
 */
#define	SYSCALL_CS      0x07		/* syscall pseudo-segment */
#define	USER_CTHREAD	0x0f		/* user cthread area */
#define	USER_SETTABLE	0x1f		/* start of user settable ldt entries */
#endif /* __x86_64__ */

#endif /* seg_h */
