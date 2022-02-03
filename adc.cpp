#include "adc.h"
#include <avr/io.h>

ADC_Channel::ADC_Channel(unsigned char channel)
{
    ADCSRA = (1 << ADEN) | (4 << ADPS0);
    ADCSRB = 0;
    ADMUX = (1 << REFS0) | ((channel & 0x0f) << MUX0);
}

ADC_Channel::~ADC_Channel()
{
}

unsigned int ADC_Channel::sample()
{
    ADCSRA |= (1 << ADSC);
    while (ADCSRA & (1 << ADSC)) ;
    return ADC;
}
