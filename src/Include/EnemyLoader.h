#pragma once

#include "EnemyData.h"
#include "ActionData.h"
#include <ctype.h>
#include <map>
#include <iostream>
#include <fstream>
#include <string>


class EnemyLoader {

public:
	void ReadFromFile(const std::string& fileName, std::unique_ptr<std::vector<EnemyData>>& enemyVector);


private:
	void LoadEnemy(std::ifstream& stream);
	void CacheAction(std::ifstream& stream);

	void GetDialogue(std::ifstream& stream, std::vector<std::string>& buffer) const;


private:
	std::map<std::string, ActionData, std::less<>> m_cachedActions;
	std::unique_ptr<std::vector<EnemyData>> m_enemies;
};