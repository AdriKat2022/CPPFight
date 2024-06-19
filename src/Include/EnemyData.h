#pragma once

#include "ActionData.h"
#include "Configs.h"

struct EnemyData {

	std::string Name = "Unnamed";

	int Health = 10;
	int Attack = 1;		// Its attack power
	int Defense = 0;	// Its resistance to damage
	int Speed = 0;		// How fast the reaction time required to guard attacks

	std::string SpritePath = FilePaths::DEFAULT_ENEMY_SPRITE;

	std::vector<ActionData> Actions; // The actions the player can do towards this enemy
};