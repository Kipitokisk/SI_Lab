 #ifndef STDIO_IO_H
 #define STDIO_IO_H
 
 #include <Arduino.h>
 #include <stdio.h>
 
 void stdio_init(unsigned long baud);
 
 int uart_putchar(char c, FILE *stream);
 int uart_getchar(FILE *stream);
 
 bool stdio_available();
 
 bool stdio_readstring(char* buffer, size_t max_length);
 
 #endif 