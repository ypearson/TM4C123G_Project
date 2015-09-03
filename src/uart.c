#include "tm4c123gh6pm.h"
#include "uart.h"
#include "cfifo.h"
#include "ascii_helpers.h"
#include "cmds.h"

cmd_t cmds[6] = {
                  {"help", "this is the usage statement for help.", test_function0 },
                  {"ls", "this is the usage statement for hello.", test_function1},
                  {"cd", "this is the usage statement for hello.", test_function1},
                  {"action1", "this is the usage statement for hello.", test_function1},
                  {"action2", "this is the usage statement for hello.", test_function1},
                  {0,0,0}};

static cfifo_t uart0_cfifo;
static buffer_t buffer0;

const char* BACKSPACE = "\x8\x20\x8";
const char* NEWLINE   = "\r\n";
const char* SPACES = "    ";
const char* PROMPT   = "es>";
const char* ERROR   = "error\r\n";

static uint8_t char_count = 0;

uint8_t test_function0(int argc, char **argv)
{
  uint8_t i = 0;

  while(cmds[i].name)
  {
    uart0_put_string(NEWLINE);
    uart0_put_string(cmds[i].name);
    uart0_put_string(SPACES);
    uart0_put_string(cmds[i].usage);
    i++;
  }
  uart0_put_string(NEWLINE);
  return 0;
}
uint8_t test_function1(int argc, char **argv)
{
  uart0_put_string("test_function1\r\n");
  return 0;
}

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

void uart0_start(void)
{
    cfifo_init( &uart0_cfifo);
    buffer_init( &buffer0, bSZ);
    uart0_init();
    uart0_newline();
    uart0_put_string("# embedded shell\r\n");
    uart0_prompt();
}

void uart0_enable_int(void)
{
  // p.104 UART INT# 5
  //NVIC_EN0_R |= ( 1 << ( INT_UART0 - 16) );
  NVIC_EN0_R |= (1<<5);
  NVIC_PRI1_R = NVIC_PRI1_INT5_M;
}

void uart0_put_byte(uint8_t data)
{
  while( (UART0_FR_R & UART_FR_TXFF) != 0);
  UART0_DR_R = data;
}

void uart0_put_string(char *str)
{
    while(*str)
    {
        uart0_put_byte(*str++);
    }
}

void uart0_newline(void)
{
  uart0_put_string(NEWLINE);
}
void uart0_backspace(void)
{
  uart0_put_string(BACKSPACE);
}
void uart0_prompt(void)
{
 uart0_put_string(PROMPT);
}
void uart0_error(void)
{
 uart0_put_string(ERROR);
}


void uart0_consume_incoming_data(void) // change to switch or small statemachine
{
  uint8_t byte;

  while(! (UART0_FR_R & UART_FR_RXFE) )
  {
    byte = (UART0_DR_R & 0xFF);

    if(byte == '\r' || byte == 3)
    {
      uart0_newline();
      uart0_prompt();
      buffer0.data[char_count] = 0;
      if(char_count)
      {
        uart0_buffer_to_cfifo_transfer();
        process_cmd();
        uart0_newline();
        uart0_prompt();
      }
      char_count = 0;
      // while( cfifo_cnt(&uart0_cfifo) ) // test
      // {
      //   cfifo_get(&uart0_cfifo, &byte);
      //   uart0_put_byte(byte);
      // }
    }
    else if(byte == 0x7F)
    {
      if(char_count)
      {
        uart0_backspace();
        char_count--;
      }
    }
    else
    {
      if( char_count < buffer0.sz - 1)
      {
        uart0_put_byte(byte);
        buffer0.data[char_count++] = byte;
      }

    }
    // uint32_to_ascii(&buffer0, byte);
    // uart0_put_string(buffer0.data);

  }
}

void uart0_buffer_to_cfifo_transfer(void)
{
    uint8_t *pdata = buffer0.data; //TODO:use params

    while(*pdata)
    {
        cfifo_put(& uart0_cfifo, pdata++);
    }
}

void process_cmd(void)
{
  uint8_t i, buf[64];
  uint8_t byte = 0;
  uint8_t ret = 0;

  char *s = buf;
  for(i = 0; i < 64; i++)
  {
    buf[i] = 0;
  }
  i = 0;

  while(byte != 0x20 && ret == 0)
  {
    ret = cfifo_get(&uart0_cfifo, &byte);
    buf[i++] = byte;
  }
  buf[i-1] = 0;
  i = 0;

  while(cmds[i].name)
  {
    if(!cstrcmp(s, cmds[i].name))
    {
      ret = cmds[i].fnc(0,0);
      break;
    }
    i++;
  }

}

void UART0_Handler(void)
{
    UART0_ICR_R |= UART_ICR_RXIC;
}