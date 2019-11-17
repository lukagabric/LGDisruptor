#ifndef __LGDisruptor__
#define __LGDisruptor__

#include "Servo.h"
#include "CommandReader.h"

class LGDisruptor
{
private:
    Servo *_horizontalServo;
    Servo *_verticalServo;
    Servo *_fireServo;
    CommandReader *_commandReader;

    int _currentVerticalValue;
    int _currentHorizontalValue;

    void fire();
    void move();
public:
    LGDisruptor();

    void setup();    
    void loop();
};

#endif /* defined(__LGDisruptor__) */
