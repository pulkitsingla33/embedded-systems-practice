CC = gcc
CFLAGS = -Wall -Wextra -g

OBJ = main.o uart_fsm.o button.o ring_buffer.o timer.o event.o

all: app

app: $(OBJ)
	$(CC) $(OBJ) -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o app