#include "main.h"
#include<stdio.h>
int WINAPI WinMain(HINSTANCE Instance, HINSTANCE PreviousInstance, LPSTR CommandLine, int CmdShow)
{   
    
    CreateMainGameWindow();
      
    g_GameIsRunning = TRUE;
    while(g_GameIsRunning){
    Events(); 
    FillScreen(color_white); 
    SetPoint(12,10,255,2,0);
    SetLine(12,10,100,100,0,0,0);
    SetPoint(12,20,color_black);
    Render();
    Sleep(1);

    }

    
    return(0);
}
    




