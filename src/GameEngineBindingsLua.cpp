#include "GameEngineBindingsLua.h"
#include "GameEngine.h"

sol::table open_gameEngine(sol::this_state s) {
	sol::state_view lua(s);

	// register functions
	sol::table module = lua.create_table();
	module["quit"] = []() {
		GAME_ENGINE->Quit();
	};

	module["getWidth"] = []() {
		return GAME_ENGINE->GetWidth();
	};

	module["getHeight"] = []() {
		return GAME_ENGINE->GetHeight();
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

	module["fillRect"] = [](int left, int top, float right, float bottom) {
		return GAME_ENGINE->FillRect(left, top, (int)right, (int)bottom);
	};

	module["drawBitmapScale"] = [](const Bitmap* bitmapPtr, int left, int top, float srcLeft, float srcTop, float srcWidth, float srcHeight, float destWidth, float destHeight) {
		RECT srcRect{ srcLeft, srcTop, srcLeft + (int)srcWidth, srcTop + (int)srcHeight };
		RECT destRect{0, 0, (int)destWidth, (int)destHeight };
		return GAME_ENGINE->DrawBitmap(bitmapPtr, left, top, srcRect, destRect);
	};

	module["drawButton"] = [](const Bitmap* bitmapPtr, float left, float top, int srcLeft, int srcTop, float srcRight, float srcBottom) {
		RECT srcRect{ srcLeft, srcTop, (int)srcRight, (int)srcBottom };
		return GAME_ENGINE->DrawBitmap(bitmapPtr, (int)left, (int)top, srcRect);
	};

	module["isPointInRect"] = [](int x, int y, float rectLeft, float rectTop, float rectRight, float rectBottom) {
		RECT rectangle{ (int)rectLeft, (int)rectTop, (int)rectLeft + (int)rectRight, (int)rectTop + (int)rectBottom };
		return GAME_ENGINE->IsPointInRect(x, y, rectangle);
	};


	// register a class
	module.new_usertype<Font>("Font", sol::constructors<sol::types<const tstring&, bool, bool, bool, int>>());
	module.new_usertype<Bitmap>(
		"Bitmap",
		sol::constructors<Bitmap(const tstring&, bool)>(),
		"GetWidth", &Bitmap::GetWidth,
		"GetHeight", &Bitmap::GetHeight
	);

	return module;
}
