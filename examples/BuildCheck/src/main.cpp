#include "testBoard.h"

TestBoard board;
BoardConfig config;

void setup()
{
    Serial.begin(115200);

    board.Initialize(&config);
}

void loop()
{
    board.CheckConnection(true);
    
    yield();
}
