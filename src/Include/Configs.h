#pragma once

#include <string>

namespace FilePaths {

	// Fonts for every text
	constexpr char FONT_DAMAGE[] = "resources/Font/HachicroUndertaleBattleFontRegular-L3zlg.ttf";
	constexpr char FONT_MAIN[] = "resources/Font/main_font.ttf";
	constexpr char FONT_TITLE[] = "resources/Font/title_font.ttf";
	constexpr char FONT_STATS[] = "resources/Font/stat_font.ttf";

	// Musics
	constexpr char MUSIC_RUN_MAIN[] = "resources/Audio/Music/menu_music.ogg";
	constexpr char MUSIC_MENU_MAIN[] = "resources/Audio/Music/menu_music.ogg";

	// Backgrounds
	constexpr char MENU_BG[] = "resources/Sprites/menu_background.png";
	constexpr char RULES_BG[] = "resources/Sprites/rules_background.png";
	constexpr char ENCOUNTER_BG[] = "resources/Sprites/encounter_background.png";

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

	// Gameplay config
	constexpr unsigned short int MAX_RUN_ENEMIES = 3;
	constexpr unsigned short int DEFAULT_BABY_START_HAPPINESS = 25;
	constexpr unsigned short int DEFAULT_PLAYER_MAX_HP = 20;
	constexpr char DEFAULT_PLAYER_NAME[] = "Chara";


	// Window config
	constexpr char WINDOW_TITLE[] = "Cpp Game";
	constexpr unsigned short int WINDOW_WIDTH = 800;
	constexpr unsigned short int WINDOW_HEIGHT = 600;


	// Buttons animations
	constexpr float BUTTON_SCALE_SPEED = 20.0f;
	constexpr float BUTTON_TARGET_SCALE_IDLE = 1.f;
	constexpr float BUTTON_TARGET_SCALE_HOVER = 1.1f;
	constexpr float BUTTON_TARGET_SCALE_PRESSED = 0.95f;
	constexpr float BUTTON_TARGET_SCALE_DISABLED = 1.f;

}