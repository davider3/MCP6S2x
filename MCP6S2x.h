#ifndef MCP6S2X_H
#define MCP6S2X_H

#define GAIN_1X 0b00000000
#define GAIN_2X 0b00000001
#define GAIN_4X 0b00000010
#define GAIN_5X 0b00000011
#define GAIN_8X 0b00000100
#define GAIN_10X 0b00000101
#define GAIN_16X 0b00000110
#define GAIN_32X 0b00000111

#define CH0 0b00000000
#define CH1 0b00000001
#define CH2 0b00000010
#define CH3 0b00000011
#define CH4 0b00000100
#define CH5 0b00000101
#define CH6 0b00000110
#define CH7 0b00000111

#define WRITE_GAIN 0b01000000
#define WRITE_CHANNEL 0b01000001
#define SHUTDOWN 0b00100000

#define SCK_4MHz 4e6
#define SCK_10MHz 10e6
#define SCK_30MHz 30e6


#include <Arduino.h>
#include <SPI.h>


/**
 * @brief Class for controlling the MCP6S2x Programmable Gain Amplifier 
 *        (PGA) using SPI communication.
 */
class MCP6S2x {
private:
    uint8_t cs;
    uint8_t channels;
    uint8_t inputPin;
    uint8_t gain;
    uint8_t channel;
    SPISettings settings;

public:
    MCP6S2x(uint8_t inputPin=A0, uint8_t cs=53, uint8_t channels=1);

    bool setGain(uint8_t newGain);
    bool changeChannel(uint8_t ch);
    int getValue();
    uint8_t getGain();
    bool isValidGain(uint8_t newGain);
    bool shutdown();
};

#endif