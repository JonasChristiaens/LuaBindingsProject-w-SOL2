//-----------------------------------------------------------------
// Main Game File
// C++ Source - Game.cpp - version v8_01
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
#include "Game.h"

//-----------------------------------------------------------------
// Game Member Functions																				
//-----------------------------------------------------------------

Game::Game() 																	
{
	// nothing to create
	m_LuaEngine.DoFile("lua/init.lua");
}

Game::~Game()																						
{
	// nothing to destroy
}

void Game::Initialize()			
{
	// Code that needs to execute (once) at the start of the game, before the game window is created

	AbstractGame::Initialize();
	GAME_ENGINE->SetTitle(_T("Game Engine version 8_01"));	
	
	GAME_ENGINE->SetWidth(1024);
	GAME_ENGINE->SetHeight(768);
    GAME_ENGINE->SetFrameRate(50);
	
	auto result = m_LuaEngine.GetTable("game")["initialize"]();
	if (!result.valid()) //failed
	{
		sol::error error = result;
		std::cerr << "Lua error: " << error.what() << std::endl;
	}

	// Set the keys that the game needs to listen to
	//tstringstream buffer;
	//buffer << _T("KLMO");
	//buffer << (char) VK_LEFT;
	//buffer << (char) VK_RIGHT;
	//GAME_ENGINE->SetKeyList(buffer.str());
}

void Game::Start()
{
	// Insert code that needs to execute (once) at the start of the game, after the game window is created
	m_LuaEngine.GetTable("game")["start"]();
}

void Game::End()
{
	// Insert code that needs to execute when the game ends
	m_LuaEngine.GetTable("game")["end"]();

}

void Game::Paint(RECT rect)
{
	/*
	=================================================================
	Had to remove const since lua can not guarantee const correctness
	=================================================================
	*/

	auto luaRect = m_LuaEngine.GetState().create_table_with("left", rect.left, "top", rect.top,
		"right", rect.right, "bottom", rect.bottom);

	// Insert paint code
	auto result = m_LuaEngine.GetTable("game")["paint"](luaRect);
	if (!result.valid()) //failed
	{
		sol::error error = result;
		std::cerr << "Lua error: " << error.what() << std::endl;
	}
}

void Game::Tick()
{
	// Insert non-paint code that needs to execute each tick 
	m_LuaEngine.GetTable("game")["tick"]();
}

void Game::MouseButtonAction(bool isLeft, bool isDown, int x, int y, WPARAM wParam)
{	
	// Insert code for a mouse button action

	/* Example:
	if (isLeft == true && isDown == true) // is it a left mouse click?
	{
		if ( x > 261 && x < 261 + 117 ) // check if click lies within x coordinates of choice
		{
			if ( y > 182 && y < 182 + 33 ) // check if click also lies within y coordinates of choice
			{
				GAME_ENGINE->MessageBox(_T("Clicked."));
			}
		}
	}
	*/
	auto luaMouseActions = m_LuaEngine.GetState().create_table_with("isLeft", isLeft, "isDown", isDown, "x", x, "y", y);
	m_LuaEngine.GetTable("game")["mouseButtonAction"](luaMouseActions);
}

void Game::MouseWheelAction(int x, int y, int distance, WPARAM wParam)
{	
	// Insert code for a mouse wheel action
	m_LuaEngine.GetTable("game")["mouseWheelAction"]();
}

void Game::MouseMove(int x, int y, WPARAM wParam)
{	
	// Insert code that needs to execute when the mouse pointer moves across the game window

	/* Example:
	if ( x > 261 && x < 261 + 117 ) // check if mouse position is within x coordinates of choice
	{
		if ( y > 182 && y < 182 + 33 ) // check if mouse position also is within y coordinates of choice
		{
			GAME_ENGINE->MessageBox("Mouse move.");
		}
	}
	*/
	m_LuaEngine.GetTable("game")["mouseMove"]();
}

void Game::CheckKeyboard()
{	
	// Here you can check if a key is pressed down
	// Is executed once per frame 

	/* Example:
	if (GAME_ENGINE->IsKeyDown(_T('K'))) xIcon -= xSpeed;
	if (GAME_ENGINE->IsKeyDown(_T('L'))) yIcon += xSpeed;
	if (GAME_ENGINE->IsKeyDown(_T('M'))) xIcon += xSpeed;
	if (GAME_ENGINE->IsKeyDown(_T('O'))) yIcon -= ySpeed;
	*/

	m_LuaEngine.GetTable("game")["checkKeyboard"]();
}

void Game::KeyPressed(TCHAR key)
{	
	// DO NOT FORGET to use SetKeyList() !!

	// Insert code that needs to execute when a key is pressed
	// The function is executed when the key is *released*
	// You need to specify the list of keys with the SetKeyList() function

	/* Example:
	switch (key)
	{
	case _T('K'): case VK_LEFT:
		GAME_ENGINE->MessageBox("Moving left.");
		break;
	case _T('L'): case VK_DOWN:
		GAME_ENGINE->MessageBox("Moving down.");
		break;
	case _T('M'): case VK_RIGHT:
		GAME_ENGINE->MessageBox("Moving right.");
		break;
	case _T('O'): case VK_UP:
		GAME_ENGINE->MessageBox("Moving up.");
		break;
	case VK_ESCAPE:
		GAME_ENGINE->MessageBox("Escape menu.");
	}
	*/

	m_LuaEngine.GetTable("game")["keyPressed"]();
}

void Game::CallAction(Caller* callerPtr)
{
	// Insert the code that needs to execute when a Caller (= Button, TextBox, Timer, Audio) executes an action
	m_LuaEngine.GetTable("game")["callAction"]();
}




