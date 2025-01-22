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
	GAME_ENGINE->SetHeight(810);
    GAME_ENGINE->SetFrameRate(50);

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
	auto result = m_LuaEngine.GetTable("game")["start"]();
	if (!result.valid()) //failed
	{
		sol::error error = result;
		std::cerr << "Lua error: " << error.what() << std::endl;
	}
}

void Game::End()
{
	// Insert code that needs to execute when the game ends

}

void Game::Paint(RECT rect)
{
	/*
	=================================================================
	Had to remove const since lua can not guarantee const correctness
	=================================================================
	*/

	// Insert paint code
	auto result = m_LuaEngine.GetTable("game")["paint"]();
	if (!result.valid()) //failed
	{
		sol::error error = result;
		std::cerr << "Lua error: " << error.what() << std::endl;
	}
}

void Game::Tick()
{
	// Insert non-paint code that needs to execute each tick 
}

void Game::MouseButtonAction(bool isLeft, bool isDown, int x, int y, WPARAM wParam)
{	
	// Insert code for a mouse button action
	auto luaMouseActions = m_LuaEngine.GetState().create_table_with(
		"isLeft", isLeft, 
		"isDown", isDown, 
		"x", x, 
		"y", y
	);

	auto gameTable = m_LuaEngine.GetTable("game");
	if (gameTable.valid() && gameTable["mouseButtonAction"].valid())
	{
		gameTable["mouseButtonAction"](isLeft, isDown, x, y);
	}
}

void Game::MouseWheelAction(int x, int y, int distance, WPARAM wParam)
{	
	// Insert code for a mouse wheel action
	auto luaMouseWheel = m_LuaEngine.GetState().create_table_with("x", x, "y", y, "distance", distance);
	m_LuaEngine.GetTable("game")["mouseWheelAction"](luaMouseWheel);
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
	auto result = m_LuaEngine.GetTable("game")["callAction"](callerPtr);
	if (!result.valid()) {
		sol::error error = result;
		std::cerr << "Lua error in callAction: " << error.what() << std::endl;
	}

	//m_LuaEngine.GetTable("game")["callAction"]();
}




