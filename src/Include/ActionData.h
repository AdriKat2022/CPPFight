#pragma once

#include "Dialogue.h"
#include <string>

struct ActionData {
	std::string ActionName;

	Dialogue AssociatedDialogue;
	
	int HappinessMultiplier;
};