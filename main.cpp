//STE29008 - Joao - ATV4 
#include "gpio.h"
#include "uart.h"
#include "cycle_counter.h"
#include "adc.h"
#include <stdio.h>

GPIO led(13, GPIO::GPIO_OUTPUT); //pino 13
UART uart; //9600 8N1
Cycle_Counter ccounter;
ADC_Channel adc(0);

const float U1 = 5;
const int ADC_MAX = 1023;
const float R2 = 10000;

const float SHH_A = 0.0010157;
const float SHH_B = 0.00025690;
const float SHH_C = -0.0000000097097;

void delay500()
{
    unsigned long i = 0x7ffff;
    while(i--);
}

void delay60000()
{
    unsigned long i2 = 0x3bfff88;
    while(i2--);
}

int main(void)
{
    char buff[32];
    unsigned char cycles;
    unsigned int adc_value;
    
	//3-coletar coeficientes via UART
    uart.puts("DIGITE OS COEFICIENTES SEM ESPACO\n");
	
    uint8_t bufRecSize = 5;
    char bufRec[bufRecSize];

    uart.getLine(bufRec, bufRecSize);

    uart.puts("Valores recebidos: ");
    uart.puts(bufRec);
    uart.puts('\n');
	
	//1 - adquirir temp. a cada min.
    while(true)
    {
		adc_value = adc.sample();
		float U2 = f(adc_value);
		float R1 = g(U2);
		float T = h(R1);
		
		
		delay60000();
		
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

float f(float x){
	return U1 * x / ADC_MAX;
}

float g(float x){
	return U1 * R2 / x - R2;
}

float h(float x){
	float logX = log(x);
	float T = SHH_A + SHH_B*logX + SHH_C*logX*logX*logX;
	return 1.0/T - 273.15;
}
