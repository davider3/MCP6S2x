#include "MCP6S2x.h"


/** @brief Constructor for the MCP6S2x class.
 *  @param inputPin Analog input pin to read the signal (default A0).
 *  @param cs       Chip select (CS) pin for SPI communication (default 53).
 *  @param channels Number of channels the amplifier supports (default 1).
 */
MCP6S2x::MCP6S2x(uint8_t inputPin, uint8_t cs, uint8_t channels){
    // ANALOG INPUT PIN
    this->inputPin = inputPin;
    pinMode(inputPin, INPUT);

    // CHIP SELECT PIN
    this->cs = cs;
    pinMode(cs, OUTPUT);
    digitalWrite(cs, HIGH);

    // HOW MANY CHANNELS DOES THE AMPLIFIER HAVE
    this->channels = channels;
    channel = CH0;

    // SET GAIN TO 1
    gain = GAIN_1X;

    // SETUP SPI COMMUNICATION
    settings = SPISettings(SCK_10MHz, MSBFIRST, SPI_MODE0);
    SPI.begin();
};


/** @brief Sets the gain of the amplifier.
 *  @param newGain The new gain value to set.
 *  @return true if the gain is valid and set successfully, false otherwise.
 */
bool MCP6S2x::setGain(uint8_t newGain){
    // IF GAIN IS ALREADY SET DONT CHANGE IT
    if(gain == newGain)
        return true;

    // VERIFIES VALID GAIN
    if(!isValidGain(newGain))
        return false;
    
    // SETS THE NEW GAIN USING SPI COMMS
    gain = newGain;

    SPI.beginTransaction(settings);
    digitalWrite(cs, LOW);

    SPI.transfer(WRITE_GAIN);
    SPI.transfer(gain);

    digitalWrite(cs, HIGH);
    SPI.endTransaction();

    return true;
};


/** @brief Changes the amplifier channel.
 *  @param ch The new channel to select (CH0, CH1, etc.).
 *  @return True if the channel is valid and changed successfully, false otherwise.
 */
bool MCP6S2x::changeChannel(uint8_t ch){
    // FIXME: IF THE CHANNEL IS ALREADY SET THEN DON'T CHANGE IT
    // if(ch == channel)
    //     return true;

    // FIXME: VERIFIES THAT IT IS A VALID CHANNEL
    // if(ch < CH0 || ch >= channels)
    //     return false;

    // CHANGES THE CHANNELS USING SPI COMMS
    channel = ch;

    SPI.beginTransaction(settings);
    digitalWrite(cs, LOW);

    SPI.transfer(WRITE_CHANNEL);
    SPI.transfer(channel);

    digitalWrite(cs, HIGH);
    SPI.endTransaction();

    return true;
};


/** @brief Reads the current value from the selected analog input pin.
 *  @return The analog reading (ADC value).
 */
int MCP6S2x::getValue(){
    return analogRead(inputPin);
};


/** @brief Retrieves the current gain setting.
 *  @return The current gain multiplier (1x, 2x, 4x, etc.).
 */
uint8_t MCP6S2x::getGain(){
    switch (gain){
        case GAIN_1X:
            return 1;
        case GAIN_2X:
            return 2;
        case GAIN_4X:
            return 4;
        case GAIN_5X:
            return 5;
        case GAIN_8X:
            return 8;
        case GAIN_10X:
            return 10;
        case GAIN_16X:
            return 16;
        case GAIN_32X:
            return 32;
        default:
            return 0;
    }
};


/** @brief Checks if the given gain value is valid.
 *  @param newGain The gain value to be checked.
 *  @return true if the gain value is one of the valid 
 *          predefined gain settings; false otherwise.
 */
bool MCP6S2x::isValidGain(uint8_t newGain) {
    switch (newGain) {
        case GAIN_1X:
        case GAIN_2X:
        case GAIN_4X:
        case GAIN_5X:
        case GAIN_8X:
        case GAIN_10X:
        case GAIN_16X:
        case GAIN_32X:
            return true;
        default:
            return false;
    }
}


// TEST
/** @brief Shuts down the amplifier.
 *  @return True if the shutdown command is sent successfully.
 */
bool MCP6S2x::shutdown(){
    SPI.beginTransaction(settings);
    digitalWrite(cs, LOW);

    SPI.transfer(SHUTDOWN);
    SPI.transfer(channel);

    digitalWrite(cs, HIGH);
    SPI.endTransaction();

    return true;
}



uint8_t MCP6S2x::getChannel(){
    return channel;
}
