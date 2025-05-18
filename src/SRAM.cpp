#include "SRAM.h"

// Pin Definitions
const int addressPins[15] = {22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36};
const int dataPins[8] = {2, 3, 4, 5, 6, 7, 8, 9};
constexpr int csPin = 37;
constexpr int oePin = 38;
constexpr int wePin = 39;

void initSRAM() {
    // Set address pins as output
    for (int i = 0; i < 15; i++) {
        pinMode(addressPins[i], OUTPUT);
    }

    // Set control pins
    pinMode(csPin, OUTPUT);
    pinMode(oePin, OUTPUT);
    pinMode(wePin, OUTPUT);

    // Default states
    digitalWrite(csPin, HIGH);
    digitalWrite(oePin, HIGH);
    digitalWrite(wePin, HIGH);
}

void setDataPinsInput() {
    for (int i = 0; i < 8; i++) {
        pinMode(dataPins[i], INPUT);
    }
}

void setDataPinsOutput() {
    for (int i = 0; i < 8; i++) {
        pinMode(dataPins[i], OUTPUT);
    }
}

uint8_t readSRAM(const uint16_t address) {
    // Set address pins
    for (int i = 0; i < 15; i++) {
        digitalWrite(addressPins[i], (address >> i) & 1);
    }

    setDataPinsInput();

    digitalWrite(csPin, LOW);
    digitalWrite(oePin, LOW);
    digitalWrite(wePin, HIGH);

    delayMicroseconds(1);  // Allow data lines to stabilize

    uint8_t data = 0;
    for (int i = 0; i < 8; i++) {
        data |= (digitalRead(dataPins[i]) << i);
    }

    digitalWrite(csPin, HIGH);
    digitalWrite(oePin, HIGH);

    return data;
}

void writeSRAM(const uint16_t address, const uint8_t data) {
    // Set address pins
    for (int i = 0; i < 15; i++) {
        digitalWrite(addressPins[i], (address >> i) & 1);
    }

    setDataPinsOutput();

    // Write data to data pins
    for (int i = 0; i < 8; i++) {
        digitalWrite(dataPins[i], (data >> i) & 1);
    }

    digitalWrite(csPin, LOW);
    digitalWrite(wePin, LOW);
    digitalWrite(oePin, HIGH);

    delayMicroseconds(1);  // Minimum write pulse width

    digitalWrite(wePin, HIGH);
    digitalWrite(csPin, HIGH);

    setDataPinsInput();  // Return data pins to input mode for future reads
}
