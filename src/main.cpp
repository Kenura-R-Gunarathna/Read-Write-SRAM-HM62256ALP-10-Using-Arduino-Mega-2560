#include <Arduino.h>
#include "SRAM.h"

void setup() {
    Serial.begin(9600);
    initSRAM();
    Serial.println("SRAM Reader/Writer Ready");
}

void loop() {
    if (Serial.available()) {
        String command = Serial.readString();
        command.trim();

        // Read command
        if (command.startsWith("read=")) {
            const String addressStr = command.substring(5);
            const auto address = static_cast<uint16_t>(strtoul(addressStr.c_str(), nullptr, 16));
            const uint8_t data = readSRAM(address);
            Serial.print("Address 0x");
            Serial.print(address, HEX);
            Serial.print(" -> Data: 0x");
            Serial.println(data, HEX);
        }
        // Write command
        else if (command.startsWith("write=")) {
            const int sepIndex = command.indexOf(',');
            if (sepIndex != -1) {
                const String addressStr = command.substring(6, sepIndex);
                const String dataStr = command.substring(sepIndex + 1);

                const auto address = static_cast<uint16_t>(strtoul(addressStr.c_str(), nullptr, 16));
                const auto data = static_cast<uint8_t>(strtoul(dataStr.c_str(), nullptr, 16));

                writeSRAM(address, data);

                Serial.print("Wrote 0x");
                Serial.print(data, HEX);
                Serial.print(" to Address 0x");
                Serial.println(address, HEX);
            } else {
                Serial.println("Invalid write command format. Use write=address,data");
            }
        }
        // Unknown command
        else {
            Serial.println("Unknown command. Use read=address or write=address,data");
        }
    }
}
