#include "uart.h"

#include <avr/io.h>
#include <avr/interrupt.h>

UART *UART::_instance = 0;

// UART::UART(int baudrate) // TODO: tarefa
UART::UART()
{
    _instance = this;

    unsigned int ubrr = 103; // 9600bps
    UBRR0H = (unsigned char)(ubrr>>8);
    UBRR0L = (unsigned char)ubrr;
    // Enable receiver and transmitter
    UCSR0B = (1 << RXEN0) | (1 << TXEN0);
    UCSR0C = (3 << UCSZ00); // 8N1
}

void UART::put(unsigned char c)
{
    UART_FIFO_t::FIFO_Errors err;
    do
    {
        asm ("cli\n");
        err = _tx_fifo.push(c);
        asm ("sei\n");
    }
    while (err != UART_FIFO_t::FIFO_SUCCESS);

    // enable udre interrupt
    UCSR0B |= (1 << UDRIE0);
}

void UART::puts(const char *str)
{
    int i = 0;
    while (str[i] != '\0')
    {
        this->put(str[i]);
        i++;
    }
}

ISR(USART_UDRE_vect)
{
    UART::instance()->handle_udre();
}
void UART::handle_udre()
{
    if (_tx_fifo.size() == 0)
    {
        // disable udre interrupt
        UCSR0B &= ~(1 << UDRIE0);
    }
    else
    {
        unsigned char tmp;
        _tx_fifo.pop(&tmp);
        while (!(UCSR0A & (1 << UDRE0))) ; // wait until last tx finishes
        UDR0 = tmp;
    }
}
