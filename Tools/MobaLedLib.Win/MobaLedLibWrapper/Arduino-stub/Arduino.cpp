#include "Arduino.h"

#include <stdio.h>
#include <stdarg.h>
#include <ctype.h>
#include <Windows.h>
#include <ostream>
#include <sstream>
#include <string>

using std::chrono::system_clock;

using namespace std;


long millis() 
{
    auto ret = GetTickCount();

    /*TCHAR s[256];
    swprintf(s, 256, L"millis = %d\n", ret);
    OutputDebugString((LPCWSTR)s);
    */
    return ret;
}

uint8_t digitalRead(uint8_t pin) { return 0; }
void digitalWrite(uint8_t pin, uint8_t value) {}
void pinMode(uint8_t pin, uint8_t mode) {}
