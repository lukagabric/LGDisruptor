#ifndef __CommandReader__
#define __CommandReader__

#include <Arduino.h>

class CommandReader
{
private:
    String _buffer;

    int _verticalDegrees;
    int _horizontalDegrees;
    bool _shouldFire;

    void parseBuffer();
public:
    CommandReader();

    int getVerticalDegrees();
    int getHorizontalDegrees();
    
    bool shouldFire();
    void fired();

    void read();
};

#endif /* defined(__CommandReader__) */
