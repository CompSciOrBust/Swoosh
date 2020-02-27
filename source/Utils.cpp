#include <time.h>

float GetTime()
{
    return (float)clock()/CLOCKS_PER_SEC;
}