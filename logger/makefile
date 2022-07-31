# makefile logger

TARGET = logger_example.out
CC = g++
CFLAGS = -ansi -g3 -pedantic -Wall -Werror -Weffc++ -std=c++11
OBJS = stream_adapter.o output_stream.o writer.o set_level.o writer_buffer.o\
	write_by_type.o logger_proxy.o client.o logger.o logger_example.o


$(TARGET) : $(OBJS)
	$(CC) -o $(TARGET) $(OBJS) -lpthread
stream_adapter.o : stream_adapter.h stream_adapter.cpp client.cpp client.h
	$(CC) -c $(CFLAGS) stream_adapter.cpp

output_stream.o : output_stream.h output_stream.cpp stream_adapter.h stream_adapter.cpp
	$(CC) -c $(CFLAGS) output_stream.cpp

writer.o : writer.h writer.cpp output_stream.h output_stream.cpp
	$(CC) -c $(CFLAGS) writer.cpp

set_level.o : set_level.h set_level.cpp writer.h writer.cpp
	$(CC) -c $(CFLAGS) set_level.cpp

writer_buffer.o : writer_buffer.h writer_buffer.cpp output_stream.h output_stream.cpp
	$(CC) -c $(CFLAGS) writer_buffer.cpp

write_by_type.o : write_by_type.h write_by_type.cpp
	$(CC) -c $(CFLAGS) write_by_type.cpp

logger_proxy.o : logger_proxy.h logger_proxy.cpp writer.h writer.cpp output_stream.h\
	output_stream.cpp writer_buffer.h writer_buffer.cpp write_by_type.h write_by_type.cpp
	$(CC) -c $(CFLAGS) logger_proxy.cpp

client.o : client.cpp client.h
	$(CC) -c $(CFLAGS) client.cpp

logger.o : logger.h logger.cpp set_level.h set_level.cpp output_stream.h\
	output_stream.cpp logger_proxy.h logger_proxy.cpp writer.h writer.cpp
		$(CC) -c $(CFLAGS) logger.cpp

logger_example.o : logger_example.cpp logger.h\
						 logger.cpp  logger_proxy.h logger_proxy.cpp
		$(CC) -c $(CFLAGS) logger_example.cpp

clean:
	rm -f $(TARGET) $(OBJS)
