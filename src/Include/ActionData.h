#pragma once

#include "Dialogue.h"
#include <string>

struct ActionData {
	std::string Name;

	Dialogue AssociatedDialogue;
	
	int HappinessShift;
};