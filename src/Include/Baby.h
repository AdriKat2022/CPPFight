#pragma once

#include "Configs.h"

class Baby {

public:
	Baby();

	float GetMult() const;
	int GetHappiness() const;
	void Modify(int);

private:
	int m_happinessLvl = Config::DEFAULT_BABY_START_HAPPINESS; // From 0 to 100
};