# makefile cdr project server

TARGET = server.out
CC = g++
CFLAGS = -ansi -g3 -pedantic -Wall -Werror -std=c++11
OBJS = server_driver.o recive_msg_handler.o main.o

$(TARGET) : $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)
	


recive_msg_handler.o : recive_msg_handler.cpp recive_msg_handler.h
	$(CC) -c $(CFLAGS) recive_msg_handler.cpp

server_driver.o : server_driver.cpp server_driver.h\
				server_driver_exceptions.h recive_msg_handler.cpp recive_msg_handler.h
	$(CC) -c $(CFLAGS) server_driver.cpp


main.o : main.cpp server_driver.cpp server_driver.h\
		 recive_msg_handler.cpp recive_msg_handler.h\
		server_driver_exceptions.h
	$(CC) -c $(CFLAGS) main.cpp

clean:
	rm -f $(TARGET) $(OBJS)
