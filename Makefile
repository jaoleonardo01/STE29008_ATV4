OBJS := uart.o cycle_counter.o adc.o gpio.o fifo.o buffer.o

CXX_FLAGS := -mmcu=atmega328p

all: gpio.o $(OBJS)
	avr-g++ $(CXX_FLAGS) -c main.cpp
	avr-g++ $(CXX_FLAGS) -o main.elf main.o $(OBJS)
	avr-objcopy -O ihex main.elf main.hex

upload: all
	avrdude -p atmega328p -P /dev/ttyACM0 -c arduino -U flash:w:main.hex

%.o: %.cpp
	avr-g++ $(CXX_FLAGS) -c $< -o $@

clean:
	rm -f *.o *.elf *.hex