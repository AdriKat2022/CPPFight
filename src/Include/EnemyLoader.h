#pragma once

#include "EnemyData.h"
#include "ActionData.h"
#include <ctype.h>
#include <map>
#include <iostream>
#include <fstream>
#include <string>

// Utility class to load enemies from a file
// Create the object and call ReadFromFile() to load the enemies
// Call GetEnemies() to get the pointer to the vector of enemies
// Do not use the object again after calling GetEnemies()
class EnemyLoader {

public:
	std::unique_ptr<std::vector<EnemyData>> GetEnemies();

	void ReadFromFile(const std::string& fileName, std::unique_ptr<std::vector<EnemyData>>& enemyVector);

private:
	void LoadEnemy(std::ifstream& stream);
	void ProcessActions(std::ifstream& stream);
	void AssignActionsFromStreamToEnemyData(std::ifstream& stream, EnemyData& enemyData);
	void CacheAction(const std::string& actionID, const ActionData& actionData);
	void GetDialogue(std::ifstream& stream, std::vector<std::string>& buffer) const;


private:
	std::map<std::string, ActionData, std::less<>> m_cachedActions;
	std::unique_ptr<std::vector<EnemyData>> m_enemies;

	bool m_used = false;
};