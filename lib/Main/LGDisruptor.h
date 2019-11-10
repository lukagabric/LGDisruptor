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

    long _verticalTimer = 0;
    long _horizontalTimer = 0;

    int _currentVerticalValue;
    int _currentHorizontalValue;

    void verticalTimerLoop();
    void horizontalTimerLoop();

    void fire();
public:
    LGDisruptor();

    void setup();    
    void loop();
};

#endif /* defined(__LGDisruptor__) */
