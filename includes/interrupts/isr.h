#ifndef __ISR_H_
#define __ISR_H_ 1

#include "idt.h"

/**
 * The default ISR handler that will be called during an exception
 */
void isr_handler(struct interrupt_event *error); 

void isr_install(uint8_t num, interrupt_handler handler);

void isr_uninstall(uint8_t num);

/**
 * Init the ISRs
 */
void init_isr();

#endif