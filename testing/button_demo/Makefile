# makfile configuration
COMMON_OBJECTS  = 
CPU             = msp430g2553
CFLAGS          = -mmcu=${CPU} -I../h
LDFLAGS		= -L/opt/ti/msp430_gcc/include

#switch the compiler (for the internal make rules)
CC              = msp430-elf-gcc
AS              = msp430-elf-as

all: button.elf buzzer.elf 

#additional rules for files
button.elf: ${COMMON_OBJECTS} p1_interrupt_handler.o led.o switches.o buttonMain.o ../lib/libTimer.a
	${CC} ${CFLAGS} ${LDFLAGS} -o $@ $^

buzzer.elf:  ${COMMON_OBJECTS} buzzer.o interrupts.o switches.o buzzerMain.o ../lib/libTimer.a

	${CC} ${CFLAGS} -o $@ $^

load: button.elf buzzer.elf
	msp430loader.sh button.elf blink.elf

clean:
	rm -f *.o *.elf
buzzer.c: buzzer.h

buzzerMain.c: buzzer.h

