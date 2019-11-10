#include <Arduino.h>
#include "LGDisruptor.h"

LGDisruptor disruptor;

void setup()
{
  disruptor.setup();
}

void loop()
{
  disruptor.loop();
}
