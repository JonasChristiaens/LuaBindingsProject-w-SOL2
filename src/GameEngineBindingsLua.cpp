#include "GameEngineBindingsLua.h"
#include "GameEngine.h"

sol::table open_gameEngine(sol::this_state s) {
	sol::state_view lua(s);

	// register functions
	sol::table module = lua.create_table();
	module["quit"] = []() {
		GAME_ENGINE->Quit();
	};

	module["setColor"] = [](int color) {
		GAME_ENGINE->SetColor(color);
	};

	module["setFont"] = [](Font* fontPtr) {
		GAME_ENGINE->SetFont(fontPtr);
	};

	module["drawString"] = [](const tstring& text, int left, int top) {
		GAME_ENGINE->DrawString(text, left, top);
	};


	module["fillRect"] = [](int left, int top, int right, int bottom) {
		return GAME_ENGINE->FillRect(left, top, right, bottom);
	};


	// register a class
	module.new_usertype<Font>("Font", sol::constructors<sol::types<const tstring&, bool, bool, bool, int>>());

	return module;
}
