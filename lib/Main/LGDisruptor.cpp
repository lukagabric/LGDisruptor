#include "LGDisruptor.h"
#include "LLowPassFilter.h"
#include <Arduino.h>
#include "Servo.h"

#define VERTICAL_ANGLE 91
#define HORIZONTAL_ANGLE 59

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
}

void LGDisruptor::loop()
{
    _commandReader->read();

    unsigned long currentMillis = millis();

    if (currentMillis - _verticalTimer >= 50)
    {
        verticalTimerLoop();
        _verticalTimer = currentMillis;
    }

    if (currentMillis - _horizontalTimer >= 20)
    {
        horizontalTimerLoop();
        _horizontalTimer = currentMillis;
    }

    if (_commandReader->shouldFire())
    {
        _commandReader->fired();
        fire();
    }
}

void LGDisruptor::verticalTimerLoop()
{
    if (_commandReader->getVerticalDegrees() == _currentVerticalValue) return;

    if (_currentVerticalValue < _commandReader->getVerticalDegrees())
    {
        _currentVerticalValue++;
    }
    else
    {
        _currentVerticalValue--;
    }

    if (_currentVerticalValue > 93 && _currentVerticalValue < 113)
    {
        _verticalServo->write(_currentVerticalValue);
    }    
}

void LGDisruptor::horizontalTimerLoop()
{
    if (_commandReader->getHorizontalDegrees() == _currentHorizontalValue) return;

    if (_currentHorizontalValue < _commandReader->getHorizontalDegrees())
    {
        _currentHorizontalValue++;
    }
    else
    {
        _currentHorizontalValue--;
    }

    if (_currentHorizontalValue > 50 && _currentHorizontalValue < 140)
    {
        _horizontalServo->write(_currentHorizontalValue);
    }
}

void LGDisruptor::fire()
{
    _fireServo->write(40);
    delay(500);
    _fireServo->write(5);
    delay(500);
}
