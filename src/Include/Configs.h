#pragma once

#include <string>
#include <array>


namespace FilePaths {

	// Fonts for every text
	constexpr char FONT_DAMAGE[] = "resources/Font/HachicroUndertaleBattleFontRegular-L3zlg.ttf";
	constexpr char FONT_MAIN[] = "resources/Font/main_font.ttf";
	constexpr char FONT_TITLE[] = "resources/Font/title_font.ttf";
	constexpr char FONT_STATS[] = "resources/Font/stat_font.ttf";

	// Sound effects
	constexpr char SOUND_BABY_CRYING[] = "resources/Audio/Sound_effect/baby_crying.wav";
	constexpr char SOUND_BABY_LAUGHING[] = "resources/Audio/Sound_effect/baby_laughing.ogg";
	constexpr char SOUND_HIT[] = "resources/Audio/Sound_effect/hit_sound.wav";
	constexpr char SOUND_CRITICAL_HIT[] = "resources/Audio/Sound_effect/critical_attack.wav";
	constexpr char SOUND_SHOWDOWN[] = "resources/Audio/Sound_effect/showdown.wav";
	constexpr char SOUND_GET_READY[] = "resources/Audio/Sound_effect/get_ready.wav";
	constexpr char SOUND_SUCCESS[] = "resources/Audio/Sound_effect/success.wav";
	constexpr char SOUND_MISSED[] = "resources/Audio/Sound_effect/miss.wav";
	constexpr char SOUND_UNBELIEVABLE_ATTACK[] = "resources/Audio/Sound_effect/unbelievable_attack.wav";
	constexpr char SOUND_PERFECT_ATTACK[] = "resources/Audio/Sound_effect/perfect_attack.wav";
	constexpr char SOUND_EXCELLENT_ATTACK[] = "resources/Audio/Sound_effect/excellent_attack.wav";
	constexpr char SOUND_NORMAL_ATTACK[] = "resources/Audio/Sound_effect/normal_attack.wav";

	// Musics
	constexpr char MUSIC_RUN_MAIN[] = "resources/Audio/Music/battle_theme.wav";
	constexpr char MUSIC_MENU_MAIN[] = "resources/Audio/Music/MainMenuTheme.wav";

	// Backgrounds
	constexpr char MENU_BG[] = "resources/Sprites/menu_background.png";
	constexpr char RULES_BG[] = "resources/Sprites/rules_background.png";
	constexpr char ENCOUNTER_BG[] = "resources/Sprites/encounter_background.png"; 

	// Menu buttons
	constexpr char SP_SH_PLAY_BTN[] = "resources/Sprites/play_button.png";
	constexpr char SP_SH_RULES_BTN[] = "resources/Sprites/rules_button.png";
	constexpr char SP_SH_QUIT_BTN[] = "resources/Sprites/quit_button.png";
	constexpr char SP_SH_BACK_BTN[] = "resources/Sprites/play_button.png";

	// Encounter buttons
	constexpr char SP_SH_FIGHT_BTN[] = "resources/Sprites/fight_button.png";
	constexpr char SP_SH_ACTION_BTN[] = "resources/Sprites/action_button.png";

	// Attack Assets
	constexpr char SP_SH_ATTACK_BOX[] = "resources/Sprites/attack_target.png";
	constexpr char SP_SH_CURSOR[] = "resources/Sprites/cursor_sh.png"; 
	constexpr char SP_SH_ATTACK_ANIMATION[] = "resources/Sprites/slash_outline.png";

	// Misc
	constexpr char WARNING_SIGN[] = "resources/Sprites/warning_sign.png";

	constexpr char ENEMY_DATA_LIST[] = "resources/Enemies/Enemies.txt";

	constexpr char DEFAULT_ENEMY_SPRITE[] = "resources/Sprites/cool_ghost.png";

}

namespace Config {

	// Gameplay config
	constexpr unsigned short int MAX_RUN_ENEMIES = 3;
	constexpr unsigned short int DEFAULT_BABY_START_HAPPINESS = 20;
	constexpr unsigned short int DEFAULT_PLAYER_MAX_HP = 20;
	constexpr unsigned short int DEFAULT_PLAYER_BASE_DAMAGE = 21;
	constexpr unsigned short int GLOBAL_MONSTER_HP_MULT = 2;
	constexpr float DEFAULT_MONSTER_BASE_MULT = 3.f;
	constexpr char DEFAULT_PLAYER_NAME[] = "Charles";

	constexpr char DEFAULT_BABY_NAME[] = "Baboum";
	constexpr char HAPPINESS_MULT_PRE_TEXT[] = "MULT\n\nx ";

	constexpr float INCREDIBLE_ATTACK_TOLERANCE = 0.02f;
	constexpr float INCREDIBLE_ATTACK_MULT = 3.f;
	constexpr char CRIT_TEXT[] = "CRIT (x3)";

	constexpr char PARRY_TEXT[] = "GARDE";
	constexpr float PARRY_BONUS_DEFENSE_MULT = 2.f;

	constexpr float GLOBAL_ATTACK_TIME = 1.3f;
	constexpr float GLOBAL_ATTACK_TIME_VARIANCE = .3f;
	constexpr float WAIT_TIME_AFTER_ATTACK = 2.f;

	constexpr float MAX_WAIT_ATTACK_TIME = 4.f;
	constexpr float MIN_WAIT_ATTACK_TIME = 1.f;

	// Window config
	constexpr char WINDOW_TITLE[] = "Cpp Game";
	constexpr unsigned short int WINDOW_WIDTH = 800;
	constexpr unsigned short int WINDOW_HEIGHT = 600;


	// Buttons animations
	constexpr float BUTTON_SCALE_SPEED = 1.0f;
	constexpr float BUTTON_TARGET_SCALE_IDLE = 1.f;
	constexpr float BUTTON_TARGET_SCALE_HOVER = 1.1f;
	constexpr float BUTTON_TARGET_SCALE_PRESSED = 0.95f;
	constexpr float BUTTON_TARGET_SCALE_DISABLED = 1.f;

	// Volume
	constexpr float GLOBAL_VOLUME_MULT = 1.f;
}

namespace Anchors {

	// TextBox
	constexpr std::array<short int, 2> TEXT_BOX_FROM_MIDDLE = { 0, 200 };
	// AttackBox
	constexpr std::array<short int, 2> ATTACK_BOX_FROM_MIDDLE = { 0, 100 };
	// DamageText
	constexpr std::array<short int, 2> MULT_TEXT_FROM_DMG_TEXT = { 50, 20 };
	// ActionButtons
	constexpr std::array<short int, 4> ACTION_BUTTONS_FROM_MIDDLE = { -100, 100, 50, 150}; // First column, second column, first row, second row
	// Baby and HappinessBar
	constexpr std::array<short int, 2> BABY_NAME_FROM_BOTTOM_RIGHT = { 75, 40 };
	constexpr std::array<short int, 2> BABY_HAPPINESS_BAR_FROM_BOTTOM_RIGHT_BG = { 75, 120 };
	constexpr std::array<short int, 2> BABY_HAPPINESS_BAR_FROM_BOTTOM_RIGHT = { 75, 120 };
	constexpr std::array<short int, 2> BABY_HAPPINESS_MULT_TEXT_FROM_TOP_RIGHT = { 20, 50 };
	constexpr std::array<short int, 2> BABY_WARNING_SIGN_FROM_MULT_TEXT = { 20, 0 };

	// Player

}

namespace Sizes {

	constexpr std::array<unsigned short int, 2> BABY_HAPPINESS_BAR_BG = { 40, 200 };
	constexpr std::array<unsigned short int, 2> BABY_HAPPINESS_BAR = { 40, 200 };

}

namespace Colors {

	// DamageText
	constexpr std::array<unsigned short int, 4> DAMAGE_PLAYER_TEXT_COLOR = { 255, 210, 10, 255 }; // Orange-Yellow
	constexpr std::array<unsigned short int, 4> DAMAGE_TEXT_COLOR_HIT = { 255, 0, 0, 255 }; // Red
	constexpr std::array<unsigned short int, 4> DAMAGE_TEXT_COLOR_MISSED = { 128, 128, 128, 255 }; // Gray
	constexpr std::array<unsigned short int, 4> MULT_TEXT_COLOR = { 210, 111, 0, 255 }; // Orange
	constexpr std::array<unsigned short int, 4> CRIT_TEXT_COLOR = { 60, 150, 255, 255 }; // Blueish120
	constexpr std::array<unsigned short int, 4> DANGER_COLOR = { 255, 20, 0, 255 }; // Red
	constexpr std::array<unsigned short int, 4> WARNING_COLOR = { 210, 160, 0, 255 }; // Orange
	constexpr std::array<unsigned short int, 4> INFO_COLOR = { 60, 150, 255, 255 }; // Blueish120

}