#ifndef TYPES_H
#define TYPES_H

void types(Print* p, const String&) {
  p->println("it's a String");
}
void types(Print* p, int a) {
  p->println("it's a int");
}
void types(Print* p, char* a) {
  p->println("it's a char*");
}
void types(Print* p, float a) {
  p->println("it's a float");
}
void types(Print* p, bool a) {
  p->println("it's a bool");
}
void types(Print* p, byte a) {
  p->println("it's a byte");
}
void types(Print* p, double a) {
  p->println("it's a double");
}
void types(Print* p, long a) {
  p->println("it's a long");
}
void types(Print* p, short a) {
  p->println("it's a short");
}
void types(Print* p, size_t a) {
  p->println("it's a size_t");
}
void types(Print* p, SPIClassRP2040* a) {
  p->println("it's a SPIClassRP2040");
}


/*
      SPIClassRP2040 *cc1101spi = &CC1101_SPI;
      SPIClassRP2040 *lcdspi = &LCD_SPI;
      pointerPrint(&SER, "CC1101_SPI", &cc1101spi);
      pointerPrint(&SER, "LCD_SPI", &lcdspi);
*/


void pointerPrint(Print* p, const char* str, SPIClassRP2040 **iptr) {
  p->printf("\nValue of %s: %d\n", str, *(*iptr));
  p->printf("Address of %s: %p\n", str, *iptr);
  p->printf("Address of pointer to %s: %p\n\n", str, &(*iptr));
}

#endif // TYPES_H
