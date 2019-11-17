#ifndef __CommandReader__
#define __CommandReader__

#include <Arduino.h>

class CommandReader
{
private:
    String _buffer;

    bool _shouldFire;

    bool _shouldMove;
    int _xOffsetPercent;
    int _yOffsetPercent;

    void parseBuffer();
    void processCommandBuffer(int[3]);

    enum CommandType { CommandTypeMove = 0, CommandTypeFire = 999 };
public:
    CommandReader();

    bool shouldMove();
    void moved();
    int getXOffsetPercent();
    int getYOffsetPercent();

    bool shouldFire();
    void fired();

    void read();
};

#endif /* defined(__CommandReader__) */
