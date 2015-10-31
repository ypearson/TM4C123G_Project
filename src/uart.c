#include "tm4c123gh6pm.h"
#include "uart.h"
#include "cfifo.h"
#include "ascii.h"
#include "cmds.h"

static cfifo_t  uart0_cf;
static cfifo_t  user_cf;

void uart_init(void)
{
    cfifo_init(&uart0_cf);
    cfifo_init(&user_cf);

    uart0.self         = 0;
    uart0.cf           = &uart0_cf;
    uart0.ucf          = &user_cf;
    uart0.init         = uart0_init;
    uart0.print        = uart_print;
    uart0.print_string = uart_print_string;

    uart0.init();
}

void uart0_init(void)
{
  SYSCTL_RCGC1_R |= SYSCTL_RCGC1_UART0;    // activate UART0
  SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOA;    // activate port A
  UART0_CTL_R    &= ~UART_CTL_UARTEN;      // disable UART
  UART0_IBRD_R    = 43;                    // IBRD = int(80,000,000 / (16 * 115200)) = int(43.402778)
  UART0_FBRD_R    = 26;                    // FBRD = round(0.402778 * 64) = 26
                                           // 8 bit word length (no parity bits, one stop bit, FIFOs)
  UART0_LCRH_R = (UART_LCRH_WLEN_8|UART_LCRH_FEN);

  UART0_IFLS_R = (UART_IFLS_RX1_8 | UART_IFLS_TX1_8); // Interrupt trigger FIFO level
  UART0_IM_R   = UART_IM_RXIM;           // Enable RX interrupt
  UART0_CTL_R |= UART_CTL_UARTEN;        // enable UART

  GPIO_PORTA_AFSEL_R |= 0x03;            // enable alt funct on PA1,PA0
  GPIO_PORTA_DEN_R   |= 0x03;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                       // enable digital I/O on PA1,PA0
                                         // configure PA1,PA0 as UART0
  GPIO_PORTA_PCTL_R   = (GPIO_PORTA_PCTL_R & 0xFFFFFF00) + 0x00000011;
  GPIO_PORTA_AMSEL_R &= ~0x03;           // disable analog functionality on PA1,PA0
}

void uart0_enable_int(void)
{
  NVIC_EN0_R |= ( 1 << ( INT_UART0 - 16) );
  NVIC_PRI1_R = NVIC_PRI1_INT5_M;
}

void uart_put_byte(device_t device, uint8_t data)
{
    switch(device)
    {
        default:
        while( (UART0_FR_R & UART_FR_TXFF) != 0);
        UART0_DR_R = data;
        break;
    }
}

void uart_print(device_t device, cfifo_t *cf)
{
  uint8_t val;

  while(cfifo_cnt(cf))
  {
    cfifo_get(cf, &val);

    switch(device)
    {
        default:
        uart_put_byte(device, val);
        break;
    }
  }
}

void uart_print_string(device_t device, const char *str)
{
  uint8_t val;

  while(*str)
  {
    switch(device)
    {
        default:
        uart_put_byte(device, (uint8_t)*str++);
        break;
    }
  }
}


void uart_cli(uart_t *uart)
{
  uint8_t byte;
  uint8_t cnt;

  if( !(UART0_FR_R & UART_FR_RXFE) )
  {
    byte = (UART0_DR_R & 0xFF);
    cnt = cfifo_cnt(uart->ucf);

    switch(byte)
    {
        case CR:
        if(cnt)
        {
            cfifo_init(uart->cf);
            cfifo_to_cfifo_transfer(uart->ucf, uart->cf);
            process_cmd(uart->cf);
        }
        uart->print(uart->self, uart->cf);
        uart->print_string(uart->self, ascii_get_prompt() );
        break;

        case DEL:
        if(cnt)
        {
            cfifo_pop(uart->ucf, &byte);
            uart->print_string(uart->self, ascii_get_backspace() );
        }
        break;

        default:
        uart_put_byte(uart->self, byte);
        cfifo_put(uart->ucf, &byte);
        break;
    }
  }
}

void UART0_Handler(void)
{
    UART0_ICR_R |= UART_ICR_RXIC;
}