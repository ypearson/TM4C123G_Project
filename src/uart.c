#include "tm4c123gh6pm.h"
#include "uart.h"
#include "cfifo.h"
#include "ascii_helpers.h"
#include "cmds.h"
#include "vars.h"

const char* BACKSPACE = "\x8\x20\x8";
const char* NEWLINE   = "\r\n";
const char* SPACES = "    ";
const char* PROMPT   = ">";
const char* ERROR   = "error\r\n";
const char* HEX   = "  0x";

static cfifo_t  uart0_cf;
static cfifo_t  user_cf;
static uart_t   uart0;

void uart_init(void)
{
    cfifo_init(&uart0_cf);
    cfifo_init(&user_cf);

    uart0.cf    = &uart0_cf;
    uart0.ucf   = &user_cf;
    uart0.init  = uart0_init;
    uart0.print = uart0_print;



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

void uart0_put_byte(uint8_t data)
{
  while( (UART0_FR_R & UART_FR_TXFF) != 0);
  UART0_DR_R = data;
}

void uart0_print(cfifo_t *cf)
{
  uint8_t val;

  while(cfifo_cnt(cf))
  {
    cfifo_get(cf, &val);
    uart0_put_byte(val);
  }
}

void uart_put_string(cfifo_t *cf, const char *str)
{
  while(*str)
  {
    cfifo_put(cf, (uint8_t*)str++);
  }
}

void uart_newline(cfifo_t *cf)
{
    uart_put_string(cf, NEWLINE);
}

void uart_backspace(cfifo_t *cf)
{
    uart_put_string(cf, BACKSPACE);
}

void uart_prompt(cfifo_t *cf)
{
    uart_put_string(cf, PROMPT);
}

void uart_error(cfifo_t *cf)
{
    uart_put_string(cf, ERROR);
}

void uart_hex(cfifo_t *cf)
{
    uart_put_string(cf, HEX);
}

void uart_spaces(cfifo_t *cf)
{
    uart_put_string(cf, SPACES);
}

void uart0_cli(void)
{
  uint8_t byte;
  uint8_t cnt;

  while(! (UART0_FR_R & UART_FR_RXFE) )
  {
    byte = (UART0_DR_R & 0xFF);

    if(byte == '\r')
    {
      cnt = cfifo_cnt(&uart0_cf);
      if(cnt)
      {
        cfifo_to_cfifo_transfer(&user_cf, &uart0_cf);
        process_cmd(&uart0_cf);
      }
      uart_newline(&user_cf);
      uart_prompt(&user_cf);
      uart_print(&user_cf);
    }
    else if(byte == 0x7F)
    {
      cnt = cfifo_cnt(&user_cf);
      if(cnt)
      {
        uart_backspace(&user_cf);
        uart_print(&user_cf);
        cfifo_get(&user_cf, &byte);
      }
    }
    else
    {
        uart_put_byte(byte);
        cfifo_put(&user_cf, &byte);
    }
  }
}

void uart_cli(uart_t *u)
{
  uint8_t byte;
  uint8_t cnt;

  while(! (UART0_FR_R & UART_FR_RXFE) )
  {
    byte = (UART0_DR_R & 0xFF);

    cnt = cfifo_cnt(u->cf);

    if(byte == '\r')
    {
      if(cnt)
      {
        cfifo_to_cfifo_transfer(u->ucf, u->cf);
        process_cmd(u->cf);
      }
      uart_newline(&user_cf);
      uart_prompt(&user_cf);
      uart_print(&user_cf);
    }
    else if(byte == 0x7F)
    {
      if(cnt)
      {
        uart_backspace(&user_cf);
        uart_print(&user_cf);
        cfifo_get(&user_cf, &byte);
      }
    }
    else
    {
        uart_put_byte(byte);
        cfifo_put(&user_cf, &byte);
    }
  }
}

void UART0_Handler(void)
{
    UART0_ICR_R |= UART_ICR_RXIC;
}