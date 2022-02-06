//STE29008 - Joao - ATV4 
#include "gpio.h"
#include "uart.h"
#include "buffer.h"
#include "cycle_counter.h"
#include "adc.h"
#include <stdio.h>
#include <math.h>

GPIO led(13, GPIO::GPIO_OUTPUT); //pino 13
UART uart; //9600 8N1
Cycle_Counter ccounter;
ADC_Channel adc(0);
int temp;

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
    unsigned long i2 = 0x1c9c380;
    while(i2--);
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

int main(void)
{
    char buff[32];
    unsigned char cycles;
    unsigned int adc_value;
    
	//3-coletar coeficientes via UART
    uart.puts("DIGITE OS COEFICIENTES SEM ESPACO\n");
	
    uint8_t bufRecSize = 5;
    char bufRec[bufRecSize];

    //char bufRec[] = {'1','1','1','1','1'};
    uart.getLine(bufRec, bufRecSize);   //como receber via UART?

    uart.puts("Valores recebidos: \n");
    uart.puts(bufRec);
    //uart.puts('\n');

    BUFFER buf(bufRec, 5);
	
	//1 - adquirir temp. a cada min.
    while(true)
    {
        for(int z=0; z < 5; z++){
            adc_value = adc.sample();
            float U2 = f(adc_value);
            float R1 = g(U2);
            float T = h(R1);
            temp = buf.fir(T); 
        }
        temp = temp/5;
        uart.puts("Temperatura: ");
        uart.put(temp);
        delay60000();
	}
}