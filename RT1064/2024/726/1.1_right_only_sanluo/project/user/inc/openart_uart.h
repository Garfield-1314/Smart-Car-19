#ifndef __OPENART_UART_H
#define __OPENART_UART_H

#include "user_include.h"

void openart1_uart_init(void);
void openart1_uart_Rece_Prepare(uint8 data);
void openart1_uart_rx_interrupt_handler(void);

void openart2_uart_init(void);
void openart2_uart_rx_interrupt_handler(void);
void openart2_uart_Rece_Prepare(uint8 data);

void MXC_uart_init(void);
void MCX_uart_rx_interrupt_handler(void);
void MCX_uart_Rece_Prepare (uint8 MCX_uart_data);

#endif
