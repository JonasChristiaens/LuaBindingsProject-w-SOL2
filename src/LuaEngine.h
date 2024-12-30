#pragma once
#include <string>
#include <variant>

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <sol/sol.hpp>

class LuaEngine
{
public:
	explicit LuaEngine();

	void DoFile(const std::string& file);
	sol::table GetTable(const std::string& name);
	sol::state_view GetState();

private:
	sol::state m_Lua{};
};