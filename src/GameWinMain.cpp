//-----------------------------------------------------------------
// Game Engine WinMain Function
// C++ Source - GameWinMain.cpp - version v8_01
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
#include "GameWinMain.h"
#include "GameEngine.h"

#include "Game.h"	

//-----------------------------------------------------------------
// Create GAME_ENGINE global (singleton) object and pointer
//-----------------------------------------------------------------
GameEngine myGameEngine;
GameEngine* GAME_ENGINE{ &myGameEngine };

static bool CreateTerminalWindow()
{
	if (!AllocConsole())
	{
		MessageBoxA(nullptr, "AllConsole failed", "GameEngine", MB_OK | MB_ICONERROR);
		return false;
	}

	FILE* fp = nullptr;
	freopen_s(&fp, "CONIN$", "r", stdin);
	freopen_s(&fp, "CONOUT$", "w", stdout);
	freopen_s(&fp, "CONOUT$", "w", stderr);

	std::ios::sync_with_stdio(true);
	return true;
}

//-----------------------------------------------------------------
// Main Function
//-----------------------------------------------------------------
int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
#ifdef _DEBUG

	CreateTerminalWindow();
#endif

	GAME_ENGINE->SetGame(new Game());					// any class that implements AbstractGame

	return GAME_ENGINE->Run(hInstance, nCmdShow);		// here we go
}

