#ifndef SRAM_H
#define SRAM_H

#include <Arduino.h>

void initSRAM();
uint8_t readSRAM(uint16_t address);
void writeSRAM(uint16_t address, uint8_t data);

#endif
