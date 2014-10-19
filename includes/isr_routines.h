#ifndef __ISR_ROUTINES_H
#define __ISR_ROUTINES_H 1


/*
 These are exceptions used in ISRs 
 These should all be defined in Assembly
 
 */


/**
 * ISR for Division By Zero Exception
 */
extern void isr_0();
/**
 * ISR for Debug Exception
 */
extern void isr_1();
/**
 * ISR for Non Maskable Interrupt Exception
 */
extern void isr_2();
/**
 * ISR for Breakpoint Exception
 */
extern void isr_3();
/**
 * ISR for Into Detected Overflow Exception
 */
extern void isr_4();
/**
 * ISR for Out of bounds exception
 */
extern void isr_5();
/**
 * ISR for invalid opcode exception
 */
extern void isr_6();
/**
 * ISR for no coprocessor exception
 */
extern void isr_7();
/**
 * ISR for double fault exception
 */
extern void isr_8();
/**
 * ISR for coprocessor segment overrun exception
 */
extern void isr_9();
/**
 * ISR for bad tss exception
 */
extern void isr_10();
/**
 * ISR for segment not present exception
 */
extern void isr_11();
/**
 * ISR for stack fault exception
 */
extern void isr_12();
/**
 * ISR for general protection fault exception
 */
extern void isr_13();
/**
 * ISR for page fault exception
 */
extern void isr_14();
/**
 * ISR for unknown interrupt exception
 */
extern void isr_15();
/**
 * ISR for coprocessor fault exception
 */
extern void isr_16();
/**
 * ISR for Alignment check exception (486+)
 */
extern void isr_17();
/**
 * ISR for Machine check exception (Pentium/586+)
 */
extern void isr_18();
/**
 * Reserved Exception (Unused?)
 */
extern void isr_19();
/**
 * Reserved Exception (Unused?)
 */
extern void isr_20();
/**
 * Reserved Exception (Unused?)
 */
extern void isr_21();
/**
 * Reserved Exception (Unused?)
 */
extern void isr_22();
/**
 * Reserved Exception (Unused?)
 */
extern void isr_23();
/**
 * Reserved Exception (Unused?)
 */
extern void isr_24();
/**
 * Reserved Exception (Unused?)
 */
extern void isr_25();
/**
 * Reserved Exception (Unused?)
 */
extern void isr_26();
/**
 * Reserved Exception (Unused?)
 */
extern void isr_27();
/**
 * Reserved Exception (Unused?)
 */
extern void isr_28();
/**
 * Reserved Exception (Unused?)
 */
extern void isr_29();
/**
 * Reserved Exception (Unused?)
 */
extern void isr_30();
/**
 * Reserved Exception (Unused?)
 */
extern void isr_31();

#endif