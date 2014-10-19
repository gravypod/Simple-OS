#ifndef __ISR_H_
#define __ISR_H_ 1

#define ISR_FLAG 0x8E

/*
 * The exception thrown when the kernel throws an ISR
 */
struct isr_error
{
	uint32_t gs, fs, es, ds; // pushed the last seg
	uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax; // Pushed by pusha
	uint32_t int_no, err_code; // push byte #, our ISRs
	uint32_t eip, cs, eflags, useresp, ss; // Pushed by processor automatically
};


/**
 * The default ISR handler that will be called during an exception
 */
void isr_handler(struct isr_error *error); 


/**
 * Init the ISRs
 */
void init_isr();

#endif