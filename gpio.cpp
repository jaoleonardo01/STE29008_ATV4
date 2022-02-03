#include "gpio.h"
#include <avr/io.h>

GPIO::GPIO(int pin, GPIO_Mode_t dir)
{
    if (pin > 7) // DDRB
    {
        _port = 0;
        pin -= 8;
        _mask = (1 << pin);
        if (dir == GPIO_OUTPUT)
        {
            DDRB |= _mask;
        }
        else // dir == GPIO_INPUT
        {
            DDRB &= ~_mask;
        }
    }
    else // DDRD
    {
        _port = 1;
        _mask = (1 << pin);
        if (dir == GPIO_OUTPUT)
        {
            DDRD |= _mask;
        }
        else // dir == GPIO_INPUT
        {
            DDRD &= ~_mask;
        }
    }
}

GPIO::~GPIO() {}

void GPIO::high()
{
    if (_port == 1) // PORTD
    {
        PORTD |= _mask;
    }
    else
    {
        PORTB |= _mask;
    }
}

void GPIO::low()
{
    if (_port == 1) // PORTD
    {
        PORTD &= ~_mask;
    }
    else
    {
        PORTB &= ~_mask;
    }
}
