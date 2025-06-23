#ifndef __OPENART_H
#define __OPENART_H

#include "user.h"

void openart1_uart_init(void);
void openart1_uart_Rece_Prepare(uint8 data);
void openart1_uart_rx_interrupt_handler(void);

#endif