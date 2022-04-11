#include "pch.h"
#include <MobaLedLib.h>
#include "resource.h"

/*
MobaLedLibWrapper: Wrapper around to LED library for model railways
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Copyright(C) 2022  Jürgen Winkler : MobaLedLib@gmx.at

This library is free software; you can redistribute itand /or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110 - 1301 USA
*/

/*
 * Change Log
 * ============================================================================
 * 
 * 2022-03-22  KG  Added third show style "combined" to visual output
 * 2022-04-11  KG  Added support for Z or S style wired matrix boards (keys S or Z)
 * 2022-04-11  KG  Added support for displaying the led number (keys N)
 */

extern "C" {
    __declspec(dllexport) int __stdcall GetWrapperVersion();
    __declspec(dllexport) const unsigned char* __stdcall Create(unsigned char* config, int configLenght);
    __declspec(dllexport) const unsigned char* __stdcall CreateSampleConfig();
    __declspec(dllexport) void __stdcall Update();
    __declspec(dllexport) int __stdcall GetLedColor(unsigned char ledNr);
    __declspec(dllexport) void __stdcall SetInput(unsigned char channel, unsigned char On);
    __declspec(dllexport) unsigned char __stdcall GetInput(unsigned char channel);
    __declspec(dllexport) void __stdcall ShowLEDWindow(unsigned char ledsX, unsigned char ledsY, unsigned char ledSize, unsigned char ledOffset, int windowPosX, int windowPosY, bool autoUpdate);
    __declspec(dllexport) void __stdcall CloseLEDWindow();
    __declspec(dllexport) bool __stdcall IsLEDWindowVisible();
    __declspec(dllexport) bool __stdcall GetLEDWindowRect(LPRECT rect);
}

#define NUM_LEDS 256

static CRGB* pLeds = new CRGB[NUM_LEDS];
char classname[] = "LEDSimulatorClass";
static uint8_t MyConfigRam[2048];
static HWND myhWnd = NULL;
static HANDLE hThread = NULL;
static DWORD dwThreadId = NULL;
static HMODULE myModule = NULL;
static CRITICAL_SECTION lock;
uint8_t _ledX;
uint8_t _ledY;
uint8_t _ledOffset;
uint8_t _ledSize;

enum LedVisualStyle { lvsRGB = 1, lvsSingles, lvsCombined, lvsMax };
enum LedVisualOrder { lvoZ = 1, lvoS, lvoMax };

LedVisualStyle showLedStyle = lvsRGB;
LedVisualOrder showLedOrder = lvoZ;
bool showLedNumbers = false;

int _windowPosX;
int _windowPosY;
bool _autoUpdate;

int baseX = 0, baseY = 0;
int border = 15;
int space = 2;

int windowBoardX = 40;
int windowBoardY = 20;
bool isRegistered = false;
bool running = false;
bool updateThreadRunning = false;

MobaLedLib_Prepare();


LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

void DrawLEDs(const HWND& hWnd);

void Register()
{
    //MessageBox(NULL, L"MessageThread", L"", 0);

    WNDCLASSEX wcex;
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
    wcex.lpfnWndProc = (WNDPROC)WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = (HINSTANCE)myModule;
    wcex.hIcon = LoadIcon((HINSTANCE)myModule, MAKEINTRESOURCE(IDI_ICON1));
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = CreateSolidBrush(RGB(0, 0, 0));
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = (LPCWSTR)classname;
    wcex.hIconSm = NULL;
    RegisterClassEx(&wcex);
}

//*******************************************************************
// *** Configuration array which defines the behavior of the LEDs ***
MobaLedLib_Configuration()
{
    RGB_Heartbeat(0) // Use the last LED in the  stripe as heartbeat
        RGB_Heartbeat(1) // Use the last LED in the  stripe as heartbeat
        RGB_Heartbeat(2) // Use the last LED in the  stripe as heartbeat
        RGB_Heartbeat(3) // Use the last LED in the  stripe as heartbeat
        RGB_Heartbeat(4) // Use the last LED in the  stripe as heartbeat
        RGB_Heartbeat(5) // Use the last LED in the  stripe as heartbeat
        RGB_Heartbeat(6) // Use the last LED in the  stripe as heartbeat
        RGB_Heartbeat(7) // Use the last LED in the  stripe as heartbeat
    ConstRGB(8, SI_1, 0, 0, 0, 127, 127, 127)
        ConstRGB(9, SI_1, 0, 0, 0, 0, 127, 0)
        ConstRGB(10, SI_1, 0, 0, 0, 0, 0, 127)
        WeldingCont(11, SI_1)
        AndreaskrRGB(12, SI_1)
        AndreaskrRGB(44, SI_1)
        AndreaskrRGB(55, SI_1)
        RGB_Heartbeat_Color(63,0,255,70,1000)
        EndCfg // End of the configuration
};

int __stdcall GetWrapperVersion()
{
    // major.minor.revision e.g. 10000 = 01.00.00
    // in case the exported function interface changes you need to increase major/and or minor version
    // if interface is compatible only revision changes
    return 10000;           // version 01.00.00
}

const unsigned char* __stdcall CreateSampleConfig()
{
    EnterCriticalSection(&lock);

    memset(pLeds, 0, NUM_LEDS* sizeof(CRGB));

    if (pMobaLedLib != NULL) delete pMobaLedLib;
    pMobaLedLib = new MobaLedLib_C(pLeds, NUM_LEDS, Config, MyConfigRam, sizeof(MyConfigRam), NULL, NULL);
    LeaveCriticalSection(&lock);
    return &pLeds[0].r;
}

const unsigned char* __stdcall Create(unsigned char* config, int configLenght)
{
    EnterCriticalSection(&lock);
    memset(pLeds, 0, NUM_LEDS * sizeof(CRGB));

    void* myConfig = malloc(configLenght);
    memcpy(myConfig, config, configLenght);

    if (pMobaLedLib != NULL) delete pMobaLedLib;
    pMobaLedLib = new MobaLedLib_C(pLeds, NUM_LEDS, (unsigned char*)myConfig, MyConfigRam, sizeof(MyConfigRam), NULL, NULL);
    LeaveCriticalSection(&lock);
    return &pLeds[0].r;
}

void __stdcall Update()
{
    EnterCriticalSection(&lock);
    if (pMobaLedLib != NULL)
    {
        pMobaLedLib->Update();
    }
    LeaveCriticalSection(&lock);
    if (running && myhWnd != NULL)
    {
        RECT rc;
        GetClientRect(myhWnd, &rc);
        InvalidateRect(myhWnd, &rc, false);
    }
}

int __stdcall GetLedColor(unsigned char ledNr)
{
    if (pMobaLedLib == NULL) return 0;
    return pLeds[ledNr].r + (pLeds[ledNr].g<<8) + (pLeds[ledNr].b<<16);
}

bool __stdcall GetLEDWindowRect(LPRECT rect)
{
    if (myhWnd == NULL) return false;
    return GetWindowRect(myhWnd, rect);
}

#include <Windows.h>

DWORD WINAPI UpdateThread(LPVOID lpParam)
{
    updateThreadRunning = true;
    while (running && myhWnd!=NULL)
    {
        EnterCriticalSection(&lock);
        Update();
        LeaveCriticalSection(&lock);
        Sleep(20);
    }
    updateThreadRunning = false;
    return 0;
}


DWORD WINAPI MessageThread(LPVOID lpParam)
{
    int height = (GetSystemMetrics(SM_CYFRAME) + GetSystemMetrics(SM_CYCAPTION) +
        GetSystemMetrics(SM_CXPADDEDBORDER));
    int frameBorderWidth = GetSystemMetrics(SM_CXPADDEDBORDER) + GetSystemMetrics(SM_CXBORDER);

    myhWnd = CreateWindow((LPCWSTR)classname, L"Leds",
        WS_OVERLAPPEDWINDOW, _windowPosX, _windowPosY,
        _ledX * (_ledSize + space) + baseX + border * 2 + frameBorderWidth * 2, _ledY * (_ledSize + space) + baseY + border * 2 + height, NULL,
        NULL, (HINSTANCE)myModule, NULL);

    if (myhWnd)
    {
        ShowWindow(myhWnd, SW_NORMAL);
        SetWindowPos(myhWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
        UpdateWindow(myhWnd);
        BringWindowToTop(myhWnd);
        running = true;
        //MessageBox(NULL, L"Window", L"", 0);

        HANDLE hThread2 = NULL;
        if (_autoUpdate)
        {
            DWORD dwThreadId;
            hThread2 = CreateThread(
                NULL,                   // default security attributes
                0,                      // use default stack size  
                UpdateThread,       // thread function name
                NULL,          // argument to thread function 
                0,                      // use default creation flags 
                &dwThreadId);   // returns the thread identifier
        }

        MSG msg;
        while (running && myhWnd!=NULL && GetMessage(&msg, 0, 0, 0))
        {
            DispatchMessage(&msg);
        }
        //MessageBox(NULL, L"End1", L"", 0);

        if (hThread2 != NULL)
        {
            // wait for update thread to stop
            // Wait doesn't work when running inside Excel
            //WaitForSingleObject(hThread2, INFINITE);

            while (updateThreadRunning)
                Sleep(20);

            TerminateThread(hThread2, 0);
            CloseHandle(hThread2);
        }
    }
    else
    {
        MessageBox(NULL, L"Create Window failed", L"", 0);
    }
    HANDLE hTmp = hThread;
    hThread = NULL;
    TerminateThread(hTmp, 0);
    return 0;
}
uint8_t CorrectColor(uint8_t color)
{
    int offset = 80;
    if (color == 0) return 0;
    int newColor = color * (255 - offset);
    newColor /= 255;
    return (uint8_t)(offset + newColor);
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_DESTROY:
        running = false;
        CloseWindow(myhWnd);
        break;
    case WM_USER:
        DestroyWindow(myhWnd);
        break;
    case WM_PAINT:
    {
        DrawLEDs(hWnd);
        break;
    }
    case WM_LBUTTONDBLCLK:
    {
        showLedStyle = LedVisualStyle(showLedStyle + 1);
        if (showLedStyle == lvsMax)
            showLedStyle = lvsRGB;

        InvalidateRect(hWnd, NULL, TRUE);
        DrawLEDs(hWnd);
        break;
    }

    case WM_KEYUP:
    {
        switch (wParam)
        {
        case 'N':
        {
            showLedNumbers = !showLedNumbers;
            InvalidateRect(hWnd, NULL, TRUE);
            DrawLEDs(hWnd);
            break;
        }

        case 'S':
        {
            showLedOrder = lvoS;
            InvalidateRect(hWnd, NULL, TRUE);
            DrawLEDs(hWnd);
            break;
        }

        case 'Z':
        {
            showLedOrder = lvoZ;
            InvalidateRect(hWnd, NULL, TRUE);
            DrawLEDs(hWnd);
            break;
        }
        }
        break;
    }

    default:
        if (message != 127 && message!=70 && message!=133 && message != 20 && message != 71 && message != 28 && message != 134 && message != 6 && message != 641
            && message != 642 && message != 61 && message != 7 && message != 8 && message != 49422 && message != 132 && message != 512 && message != 32
            && message != 160 && message != 674 && message != 513 && message != 514 && message != 161 && message != 274 && message != WM_MOUSEACTIVATE)
        {
            int a = 0;
            a++;
        }
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}


void DrawLEDs(const HWND& hWnd)
{
    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(hWnd, &ps);
    TCHAR number[5];

    int posX = 10, posY = 100;
    int size = _ledSize;
    int _ZSx = 0;

    for (int y = 0; y < _ledY; y++)
    {
        for (int x = 0; x < _ledX; x++)
        {
            if (showLedOrder == lvoZ)
                _ZSx = x;
            else
                if (y % 2 == 1)
                    _ZSx = _ledX - x - 1;
                else
                    _ZSx = x;

            int ledIndex = _ledOffset + y * _ledX + _ZSx;
            if (ledIndex < NUM_LEDS)
            {
                posX = baseX + border + x * (size + space);
                posY = baseY + border + y * (size + space);

                HPEN hPen = CreatePen(PS_SOLID, 1, 0x404040);
                SelectObject(ps.hdc, hPen);

                if (showLedStyle == lvsRGB  ||  showLedStyle == lvsCombined)
                {
                    // blue green red
                    int color = (CorrectColor(pLeds[ledIndex].b) << 16) + (CorrectColor(pLeds[ledIndex].g) << 8) + CorrectColor(pLeds[ledIndex].r);
                    HBRUSH hBrush = CreateSolidBrush(color);
                    SelectObject(ps.hdc, hBrush);
                    Ellipse(ps.hdc, posX, posY, posX + size, posY + size);
                    DeleteObject(hBrush);
                }

                if (showLedStyle == lvsSingles || showLedStyle == lvsCombined)
                {
                    int ledsize;
                    int centerX = posX + size / 2;
                    int centerY = posY + size / 2;
                    int deltaX = 2;
                    int deltaY = 2;

                    if (showLedStyle == lvsSingles)
                        ledsize = size / 2;
                    else
                        ledsize = size / 3;

                    int color = CorrectColor(pLeds[ledIndex].r);
                    HBRUSH hBrush = CreateSolidBrush(color);
                    SelectObject(ps.hdc, hBrush);
                    Ellipse(ps.hdc, centerX - ledsize, centerY - ledsize + deltaY, centerX, centerY + deltaY);
                    DeleteObject(hBrush);

                    color = (CorrectColor(pLeds[ledIndex].g) << 8);
                    hBrush = CreateSolidBrush(color);
                    SelectObject(ps.hdc, hBrush);
                    Ellipse(ps.hdc, centerX, centerY - ledsize + deltaY, centerX + ledsize, centerY + deltaY);
                    DeleteObject(hBrush);

                    color = (CorrectColor(pLeds[ledIndex].b) << 16);
                    hBrush = CreateSolidBrush(color);
                    SelectObject(ps.hdc, hBrush);
                    int xOffset = ((size * 25) / 100);
                    int yOffset = ((size * 42) / 100);
                    Ellipse(ps.hdc, centerX - ledsize / 2, centerY - deltaY, centerX + ledsize / 2, centerY + ledsize - deltaY);
                    DeleteObject(hBrush);
                }

                if (showLedNumbers)
                {
                    RECT rect;
                    GetClientRect(hWnd, &rect);

                    SetTextColor(ps.hdc, RGB(0xA0, 0xA0, 0xA0));
                    SetBkMode(ps.hdc, TRANSPARENT);
                    rect.left = posX;
                    rect.top = posY + _ledSize - 14;
                    swprintf(number, 4, L"%d", ledIndex);
                    DrawText(hdc, number, -1, &rect, DT_SINGLELINE | DT_NOCLIP);
                }

                DeleteObject(hPen);
            }
        }
    }
    EndPaint(hWnd, &ps);
}

void __stdcall SetInput(unsigned char channel, unsigned char On)
{
    EnterCriticalSection(&lock);
    if (pMobaLedLib != NULL)
    {
        pMobaLedLib->Set_Input(channel, On);
    }
    LeaveCriticalSection(&lock);

}

void _stdcall ShowLEDWindow(unsigned char ledsX, unsigned char ledsY, unsigned char ledSize, unsigned char ledOffset, int windowPosX, int windowPosY, bool autoUpdate)
{
    _ledX = ledsX;
    _ledY = ledsY;
    _ledSize = ledSize;
    _ledOffset = ledOffset;
    _windowPosX = windowPosX;
    _windowPosY = windowPosY;
    _autoUpdate = autoUpdate;
    Register();
    if (hThread == NULL)
    {
        hThread = CreateThread(
            NULL,                   // default security attributes
            0,                      // use default stack size  
            MessageThread,       // thread function name
            NULL,          // argument to thread function 
            0,                      // use default creation flags 
            &dwThreadId);   // returns the thread identifier
    }
    else
    {
        InvalidateRect(myhWnd, NULL, TRUE);
    }

}

void _stdcall CloseLEDWindow()
{
    if (running && myhWnd!=NULL)
    {
        PostMessage(myhWnd, WM_USER, NULL, NULL);
        if (WaitForSingleObject(hThread, 1000) != WAIT_OBJECT_0)
        {
            TerminateThread(hThread, 0);
        }
    }
}

bool _stdcall IsLEDWindowVisible()
{
    return running && myhWnd != NULL;
}

unsigned char __stdcall GetInput(unsigned char channel)
{
    EnterCriticalSection(&lock);
    auto result = pMobaLedLib->Get_Input(channel);
    LeaveCriticalSection(&lock);
    return result;
}

void OnAttach(HMODULE hModule)
{
    myModule = hModule;
    InitializeCriticalSection(&lock);
}

void OnDetach(HMODULE hModule) 
{
    CloseLEDWindow();
    DeleteCriticalSection(&lock);
}
