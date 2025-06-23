#ifndef __OPENART2_H
#define __OPENART2_H

#include "user.h"

void openart2_uart_init(void);
void openart2_uart_rx_interrupt_handler(void);
void openart2_uart_Rece_Prepare(uint8 data);


#endif