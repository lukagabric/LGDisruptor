#include <Arduino.h>
#include "CommandReader.h"

#define DEBUG_TO_SERIAL 0

CommandReader::CommandReader()
{
    _verticalDegrees = -1;
    _horizontalDegrees = -1;
    _shouldFire = false;
    _buffer = "";
}

int CommandReader::getVerticalDegrees()
{
    return _verticalDegrees;
}

int CommandReader::getHorizontalDegrees()
{
    return _horizontalDegrees;
}

bool CommandReader::shouldFire()
{
    return _shouldFire;
}

void CommandReader::fired()
{
    _shouldFire = false;
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
    String buffer = "";
    int currentIndex = 0;
    int numbers[2] = {-1, -1};

    for (int index = 0; index < (int)_buffer.length(); index++)
    {
        char currentChar = _buffer.charAt(index);

        if (currentChar == ',' || currentChar == '\n')
        {
            int number = buffer.toInt();
            numbers[currentIndex] = number;

            #if DEBUG_TO_SERIAL
            Serial.print("Buffer: '");
            Serial.print(buffer);
            Serial.print("'; Read number: '");
            Serial.print(number);
            Serial.print("'; Index: '");
            Serial.print(currentIndex);
            Serial.println("'");
            #endif

            buffer = "";
            currentIndex++;
        }
        else
        {
            buffer += currentChar;

            #if DEBUG_TO_SERIAL
            Serial.print("Appending to buffer value:'");
            Serial.print(currentChar);
            Serial.print("'. Buffer: '");
            Serial.print(buffer);
            Serial.println("'");
            #endif
        }
    }

    _buffer = "";

    if (numbers[0] == 999 && numbers[1] == 999)
    {
        _shouldFire = true;
    }
    else
    {
        _verticalDegrees = numbers[0];
        _horizontalDegrees = numbers[1];
    }
}
