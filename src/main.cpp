#include "Game.h"
#include <Windows.h>



int WINAPI WinMain(HINSTANCE hThisInstance, HINSTANCE hPrevInstance, LPSTR lpszArgument, int nCmdShow)
{
     Snake_Engine game;
     game.Run();
     return 0;
}