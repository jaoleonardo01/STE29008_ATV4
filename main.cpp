#include "gpio.h"
#include "uart.h"
#include "cycle_counter.h"
#include "adc.h"
#include <stdio.h>

GPIO led(13, GPIO::GPIO_OUTPUT); //pino 13
UART uart; //9600 8N1
Cycle_Counter ccounter;
ADC_Channel adc(0);

void delay500()
{
    unsigned long i = 0x7ffff;
    while(i--);
}

int main(void)
{
    char buff[32];
    unsigned char cycles;
    unsigned int adc_value;
    while(true)
    {
        uart.puts("oi\n");
        led.high();
        delay500();
        adc_value = adc.sample();
        sprintf(buff, "ADC 0: %u\n", adc_value);
        ccounter.start();
        uart.puts(buff);
        cycles = ccounter.stop();
        sprintf(buff, "cycles: %u\n", cycles);
        uart.puts(buff);
        led.low();
        uart.puts("tchau\n");
        delay500();
    }
}