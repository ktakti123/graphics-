
#pragma once
#define GameResWidth 384
#define GameResHeight 216
#define GameBpp 32
#define GAME_MEMORY_SIZE (GameResWidth*GameResHeight * (GameBpp/8))
#define color_black 0,0,0
#define color_red 255,0,0
#define color_blue 0,0,255
#define color_green 0,255,0
#define color_white 255,255,255
#define main() WINAPI WinMain(HINSTANCE Instance, HINSTANCE PreviousInstance, LPSTR CommandLine, int CmdShow)

#include <stdio.h> 
#include<windows.h>
#include<stdbool.h>


BOOL run = true;
HWND gGameWindow;
RECT windowRect;
int windowWidth = 640;
int windowHeight = 480;
BOOL GameStart = 1;
MSG Message = {0};


void fill_screen(BYTE , BYTE , BYTE );
void set_point(int , int , BYTE , BYTE , BYTE );
void Render(void);
void checkWindowSize(void);


typedef struct GameBitmap
 {
    BITMAPINFO BitmapInfo;
    void *memory;
 }GameBitmap;
 GameBitmap gDrawingSurface;


LRESULT CALLBACK MainWindowProc(HWND WindowHandle,UINT Message,       
    WPARAM wParam,LPARAM lParam)  
{ 
 
    switch (Message) 
    { 
        case WM_CREATE: 
            return 0; 
        case WM_SIZE: 
            checkWindowSize();
            return 0;
        case WM_DESTROY: 
            run = FALSE;
            PostQuitMessage(0); 
            return 0; 
        default: 
            return DefWindowProc(WindowHandle, Message, wParam, lParam); 
    } 
    return 0; 
}

DWORD start(void)
{

    WNDCLASSEXA WindowClass = {0};
    WindowClass.cbSize   = sizeof(WNDCLASSEXA);
    WindowClass.lpfnWndProc   = MainWindowProc;
    WindowClass.hInstance     = GetModuleHandleA(NULL);
    WindowClass.lpszClassName = "3D_PROGRAM";
    WindowClass.hbrBackground = CreateSolidBrush(RGB(45,0,0));
    
    RegisterClassExA(&WindowClass);

     gDrawingSurface.BitmapInfo.bmiHeader.biSize = sizeof(gDrawingSurface.BitmapInfo.bmiHeader);
     gDrawingSurface.BitmapInfo.bmiHeader.biWidth = GameResWidth;
     gDrawingSurface.BitmapInfo.bmiHeader.biHeight = -GameResHeight;
     gDrawingSurface.BitmapInfo.bmiHeader.biBitCount = GameBpp;
     gDrawingSurface.BitmapInfo.bmiHeader.biCompression = BI_RGB;
     gDrawingSurface.BitmapInfo.bmiHeader.biPlanes = 1;
     gDrawingSurface.memory = VirtualAlloc(NULL,GAME_MEMORY_SIZE,MEM_RESERVE|MEM_COMMIT , PAGE_READWRITE );
     memset(gDrawingSurface.memory, 0x00, GAME_MEMORY_SIZE); 
     gGameWindow   = CreateWindowExA(WS_EX_CLIENTEDGE,WindowClass.lpszClassName,"3D_SOFTWARE",WS_OVERLAPPEDWINDOW|WS_VISIBLE,
     CW_USEDEFAULT, CW_USEDEFAULT,640,480,NULL,NULL,GetModuleHandleA(NULL), NULL);
    if (gGameWindow == NULL)
    {
    return (0);
    }
    
}

void Events(void)
{
    while (PeekMessageA(&Message, NULL, 0, 0, PM_REMOVE))
    {
        DispatchMessageA(&Message);
    }
}


void Render(void)
{
   if (GameStart ==1){
    checkWindowSize();
    GameStart = 0;
   }
    HDC DeviceContext = GetDC(gGameWindow);

    StretchDIBits(DeviceContext, 0, 0, windowWidth, windowHeight, 0, 0, GameResWidth, GameResHeight,
                  gDrawingSurface.memory, &gDrawingSurface.BitmapInfo, DIB_RGB_COLORS, SRCCOPY);

    // Release device context
    ReleaseDC(gGameWindow, DeviceContext);
    Sleep(1);
}


void fill_screen(BYTE red, BYTE green, BYTE blue)
{
    // Fill the memory with the desired color
    for (int y = 0; y < GameResHeight; ++y)
    {
        for (int x = 0; x < GameResWidth; ++x)
        {
            // Calculate the index for the pixel in the memory buffer
            int pixelIndex = (y * GameResWidth + x) * 4; // 4 bytes per pixel for 32 BPP
            BYTE *pixel = (BYTE *)gDrawingSurface.memory + pixelIndex;

            // Set the pixel color
            pixel[0] = blue;  // Blue component
            pixel[1] = green; // Green component
            pixel[2] = red;   // Red component
            pixel[3] = 0;     // Alpha component (not used)
        }
    }
}

void set_point(int x , int y, BYTE red, BYTE green, BYTE blue)
{
            int pixelIndex = (y * GameResWidth + x) * 4;
            BYTE *pixel = (BYTE *)gDrawingSurface.memory + pixelIndex;
            pixel[0] = blue;  // Blue component
            pixel[1] = green; // Green component
            pixel[2] = red;   // Red component
            pixel[3] = 0;     // Alpha component (not used)
}

void checkWindowSize()
{
 GetClientRect(gGameWindow, &windowRect);
 windowWidth = windowRect.right - windowRect.left;
 windowHeight = windowRect.bottom - windowRect.top;
}
