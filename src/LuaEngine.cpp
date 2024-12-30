#include "LuaEngine.h"
#include "lua.hpp"
#include "GameEngineBindingsLua.h"

#include <cassert>
#include <iostream>

LuaEngine::LuaEngine()
{
	//load standard libraries from lua
	m_Lua.open_libraries();
	m_Lua.require("gameEngine", sol::c_call<decltype(&open_gameEngine), &open_gameEngine>, true);

	//define a global table (object) named "game"
	m_Lua["game"] = m_Lua.create_table();
}

void LuaEngine::DoFile(const std::string& file)
{
	auto result = m_Lua.safe_script_file(file);
	if (!result.valid()) //failed
	{
		sol::error error = result;
		std::cerr << "Lua error: " << error.what() << std::endl;
	}
}

sol::table LuaEngine::GetTable(const std::string& name)
{
	return m_Lua[name];
}

sol::state_view LuaEngine::GetState()
{
	return m_Lua;
}
