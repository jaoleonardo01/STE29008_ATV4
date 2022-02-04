#ifndef __UART_H__
#define __UART_H__

#include "fifo.h"

class UART
{
public:
    UART();

    void put(unsigned char c);
    void puts(const char *str);
	void getc(void);
	void getLine(char* buf, uint8_t n);
    unsigned char get(); // TODO: tarefa

    void handle_udre();

    static UART *instance() { return _instance; }

private:
    typedef FIFO<unsigned char, 16> UART_FIFO_t;
    UART_FIFO_t _tx_fifo;
    static UART *_instance;
};

#endif // __UART_H__