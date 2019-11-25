#include "LGDisruptor.h"
#include "LLowPassFilter.h"
#include <Arduino.h>
#include "Servo.h"

LGDisruptor::LGDisruptor()
{
    _horizontalServo = new Servo();
    _verticalServo = new Servo();
    _fireServo = new Servo();

    _commandReader = new CommandReader();

    _currentHorizontalValue = 90;
    _currentVerticalValue = 103;
}

void LGDisruptor::setup()
{
    Serial.begin(9600);

    _horizontalServo->attach(9);
    _verticalServo->attach(10);
    _fireServo->attach(11);

    _fireServo->write(5);
    delay(500);
    _horizontalServo->write(_currentHorizontalValue);
    delay(500);
    _verticalServo->write(_currentVerticalValue);
    delay(500);

    Serial.println("Ready... Set... Go...");
}

void LGDisruptor::loop()
{
    _commandReader->read();

    if (_commandReader->shouldMove())
    {
        move();
    }

    if (_commandReader->shouldFire())
    {
        fire();
    }
}

void LGDisruptor::move()
{
    int xOffset = _commandReader->getXOffsetPercent();
    int yOffset = _commandReader->getYOffsetPercent();

    int xDiff = map(xOffset, -100, 100, 15, -15);
    int yDiff = map(yOffset, -100, 100, 5, -5);

    _currentHorizontalValue += xDiff;
    _currentVerticalValue += yDiff;

    Serial.print("     x: ");
    Serial.print(_currentHorizontalValue);
    Serial.print("; y:");
    Serial.println(_currentVerticalValue);

    _currentHorizontalValue = max(40, min(140, _currentHorizontalValue));
    _currentVerticalValue = max(83, min(113, _currentVerticalValue));

    _horizontalServo->write(_currentHorizontalValue);
    delay(50);
    _verticalServo->write(_currentVerticalValue);
    delay(50);

    _commandReader->moved();
}

void LGDisruptor::fire()
{
    _commandReader->fired();

    _fireServo->write(40);
    delay(500);
    _fireServo->write(5);
    delay(500);
}
