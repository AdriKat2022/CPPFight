#pragma once

#include <string>

namespace FilePaths {

	// Font for every text
	constexpr char UNDERTALE_FONT[] = "resources/Font/HachicroUndertaleBattleFontRegular-L3zlg.ttf";

	// Put all sprites sheets in here
	constexpr char SP_SH_MENU_BG[] = "resources/Sprites/menu_background.png";

	// Menu buttons
	constexpr char SP_SH_PLAY_BTN[] = "resources/Sprites/play_button.png";
	constexpr char SP_SH_RULES_BTN[] = "resources/Sprites/rules_button.png";
	constexpr char SP_SH_QUIT_BTN[] = "resources/Sprites/quit_button.png";

	// Encounter buttons
	constexpr char SP_SH_FIGHT_BTN[] = "resources/Sprites/fight_button.png";
	constexpr char SP_SH_ACTION_BTN[] = "resources/Sprites/action_button.png";

	constexpr char ENEMY_DATA_LIST[] = "resources/Enemies/Enemies.txt";

}

namespace Config {

	// Window config
	constexpr char WINDOW_TITLE[] = "Cpp Game";
	constexpr unsigned int WINDOW_WIDTH = 800;
	constexpr unsigned int WINDOW_HEIGHT = 600;


	// Buttons animations
	constexpr float BUTTON_SCALE_SPEED = 20.0f;
	constexpr float BUTTON_TARGET_SCALE_IDLE = 1.f;
	constexpr float BUTTON_TARGET_SCALE_HOVER = 1.1f;
	constexpr float BUTTON_TARGET_SCALE_PRESSED = 0.95f;
	constexpr float BUTTON_TARGET_SCALE_DISABLED = 1.f;

}