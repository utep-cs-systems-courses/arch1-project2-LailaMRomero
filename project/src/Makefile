# makfile configuration
COMMON_OBJECTS  =
CPU             = msp430g2553
CFLAGS          = -mmcu=${CPU} -I../h -L/opt/ti/msp430_gcc/include


#switch the compiler (for the internal make rules)

CC              = msp430-elf-gcc
AS              = msp430-elf-as

all: project2.elf

#additional rules for files
project2.elf: ${COMMON_OBJECTS} main.o stateMachine.s buzzer.o interrupts.o led.o switches.o  ../lib/libTimer.a

	${CC} ${CFLAGS} -o $@ $^

load: project2.elf

	msp430loader.sh project2.elf


clean:
	rm -f *.o *.elf

main.c: buzzer.h switches.h
buzzer.c: buzzer.h
switches.c: switches.h buzzer.h led.h
stateMachine.s: stateMachine.h led.h switches.h
interrupts.c: switches.h led.h stateMachine.h buzzer.h
led.c: led.h stateMachine.h




