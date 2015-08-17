#include "tm4c123gh6pm.h"
#include "uart.h"

void uart0_init(void)
{
  SYSCTL_RCGC1_R |= SYSCTL_RCGC1_UART0; // activate UART0
  SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOA; // activate port A
  UART0_CTL_R    &= ~UART_CTL_UARTEN;      // disable UART
  UART0_IBRD_R    = 43;                    // IBRD = int(80,000,000 / (16 * 115200)) = int(43.402778)
  UART0_FBRD_R    = 26;                    // FBRD = round(0.402778 * 64) = 26
                                        // 8 bit word length (no parity bits, one stop bit, FIFOs)
  UART0_LCRH_R = (UART_LCRH_WLEN_8|UART_LCRH_FEN);

  UART0_IFLS_R = (UART_IFLS_RX1_8 | UART_IFLS_TX1_8); // Interrupt trigger FIFO level
  UART0_IM_R   = UART_IM_RXIM;           // Enable RX interrupt
  UART0_CTL_R |= UART_CTL_UARTEN;       // enable UART

  GPIO_PORTA_AFSEL_R |= 0x03;           // enable alt funct on PA1,PA0
  GPIO_PORTA_DEN_R   |= 0x03;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                       // enable digital I/O on PA1,PA0
                                        // configure PA1,PA0 as UART0
  GPIO_PORTA_PCTL_R   = (GPIO_PORTA_PCTL_R & 0xFFFFFF00) + 0x00000011;
  GPIO_PORTA_AMSEL_R &= ~0x03;          // disable analog functionality on PA1,PA0
}

void uart0_enable_int(void)
{
  // p.104 UART INT# 5
  //NVIC_EN0_R |= ( 1 << ( INT_UART0 - 16) );
  NVIC_EN0_R |= (1<<5);
  NVIC_PRI1_R = NVIC_PRI1_INT5_M;
}

void putbyte(uint8_t data)
{
  while( (UART0_FR_R & UART_FR_TXFF) != 0);
  UART0_DR_R = data;
}

void UART0_Handler(void)
{
    UART0_ICR_R |= UART_ICR_RXIC;

    putbyte( (uint8_t)(UART0_DR_R & 0xFF) );
    putbyte( (uint8_t)(UART0_DR_R & 0xFF) );

}