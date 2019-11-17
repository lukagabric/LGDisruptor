#include <Arduino.h>
#include "CommandReader.h"

#define SERIAL_PRINT_PARSING 0
#define SERIAL_PRINT_RESULT 0

CommandReader::CommandReader()
{
    _xOffsetPercent = 0;
    _yOffsetPercent = 0;
    _shouldMove = false;
    _shouldFire = false;
    _buffer = "";
}

void CommandReader::read()
{
    if (!Serial.available()) return;

    do
    {
        int readByte = Serial.read();
        _buffer += (char)readByte;

        if (readByte == '\n')
        {
            parseBuffer();
        }
    } while (Serial.available() > 0);    
}

void CommandReader::parseBuffer()
{
    String parsedString = "";
    int currentIndex = 0;
    int numbers[3] = {0, 0, 0};

    for (int index = 0; index < (int)_buffer.length(); index++)
    {
        char currentChar = _buffer.charAt(index);

        if (currentChar == ',' || currentChar == '\n')
        {
            int number = parsedString.toInt();
            numbers[currentIndex] = number;

            #if SERIAL_PRINT_PARSING
            Serial.print("Buffer: '");
            Serial.print(parsedString);
            Serial.print("'; Read number: '");
            Serial.print(number);
            Serial.print("'; Index: '");
            Serial.print(currentIndex);
            Serial.println("'");
            #endif

            parsedString = "";
            currentIndex++;
        }
        else
        {
            parsedString += currentChar;

            #if SERIAL_PRINT_PARSING
            Serial.print("Appending to buffer value:'");
            Serial.print(currentChar);
            Serial.print("'. Buffer: '");
            Serial.print(parsedString);
            Serial.println("'");
            #endif
        }
    }

    _buffer = "";

    processCommandBuffer(numbers);
}

void CommandReader::processCommandBuffer(int numbers[3])
{
    CommandType commandType = (CommandType)numbers[0];

    switch (commandType)
    {
    case CommandTypeMove:
        _xOffsetPercent = numbers[1];
        _yOffsetPercent = numbers[2];
        if (_xOffsetPercent != 0 || _yOffsetPercent != 0)
        {
            _shouldMove = true;
        }
        
        #if SERIAL_PRINT_RESULT
        Serial.print("     x: ");
        Serial.print(getXOffsetPercent());
        Serial.print("; y:");
        Serial.println(getYOffsetPercent());
        #endif

        break;
    case CommandTypeFire:
        _shouldFire = true;
        break;
    }
}

bool CommandReader::shouldMove()
{
    return _shouldMove;
}

void CommandReader::moved()
{
    _shouldMove = false;
    _xOffsetPercent = 0;
    _yOffsetPercent = 0;
}

int CommandReader::getXOffsetPercent()
{
    return _xOffsetPercent;
}

int CommandReader::getYOffsetPercent()
{
    return _yOffsetPercent;
}

bool CommandReader::shouldFire()
{
    return _shouldFire;
}

void CommandReader::fired()
{
    _shouldFire = false;
}
