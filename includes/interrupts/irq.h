
#ifndef __IRQ_H
#define __IRQ_H 1
#include "idt.h"

typedef void (*irq_function)(struct interrupt_event *event);

void init_irq();

/**
 * Install and IRQ handler
 * irq     - IRQ the handler is for
 * handler - The handler function that will handle the IRQ
 */
void irq_install(int irq, irq_function handler);

/**
 * Unregister an IRQ
 * irq - The IRQ to unregister
 */
void irq_uninstall(int irq);

/**
 * default handler for IRQs
 */
void irq_handler(struct interrupt_event *event);

#endif