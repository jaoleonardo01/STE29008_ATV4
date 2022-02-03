#ifndef __GPIO_H__
#define __GPIO_H__

class GPIO
{
public:
    enum GPIO_Mode_t
    {
        GPIO_INPUT = 0,
        GPIO_OUTPUT = 1
    };
    GPIO(int pin, GPIO_Mode_t dir);
    ~GPIO();

    void high();
    void low();

    void get(); // TODO: tarefa

private:
    unsigned char _mask;
    char _port; // 0 - portb; 1 - portd
};

#endif // __GPIO_H__