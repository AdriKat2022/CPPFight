#pragma once

class Baby {

public:
	Baby();

	float GetMult() const;
	int GetHappiness() const;
	void Modify(int);

private:
	int m_happinessLvl = 20; // From 0 to 100
};