 #include "SerialIO.h"

 static FILE uartout = {0};
 static FILE uartin = {0};
 
 void stdio_init(unsigned long baud) {
     Serial.begin(115200);
     
     while (!Serial && millis() < 5000);
     
     fdev_setup_stream(&uartout, uart_putchar, NULL, _FDEV_SETUP_WRITE);
     stdout = &uartout;
     
     fdev_setup_stream(&uartin, NULL, uart_getchar, _FDEV_SETUP_READ);
     stdin = &uartin;
 }
 
 int uart_putchar(char c, FILE *stream) {
     Serial.write(c);
     return 0;
 }
 
 int uart_getchar(FILE *stream) {
     while (!Serial.available());
     return Serial.read();
 }
 
 bool stdio_available() {
     return Serial.available() > 0;
 }
 
 bool stdio_readstring(char* buffer, size_t max_length) {
     if (!stdio_available()) {
         return false;
     }
     
     size_t index = 0;
     buffer[0] = '\0';
     
     unsigned long start_time = millis();
     while (!stdio_available() && (millis() - start_time < 500));
     
     if (!stdio_available()) {
         return false;
     }
     
     while (stdio_available() && index < max_length - 1) {
         char c = Serial.read();
         
         if (c == '\n' || c == '\r') {
             break;
         }
         
         buffer[index++] = c;
         buffer[index] = '\0';
         
         delay(2);
     }
     
     while (stdio_available()) {
         char c = Serial.read();
         if (c == '\n' || c == '\r') {
             break;
         }
         delay(1);
     }
     
     return index > 0;
 }