#include "EnemyLoader.h"


std::unique_ptr<std::vector<EnemyData>> EnemyLoader::ReadFromFile(const std::string& fileName)
{
	// Reset the EnemyData vector (in case it was already used)
	m_enemies = std::make_unique<std::vector<EnemyData>>();

	std::ifstream file(fileName);

	if (!file.is_open()) {
		std::cout << "Failed to open file: " << fileName << std::endl;
		return nullptr;
	}

	std::string buffer;

	while (file)
	{
		std::getline(file, buffer);

		if (buffer == "[Enemy]")
		{
			LoadEnemy(file);
		}
		else if (buffer == "[Action]")
		{
			CacheAction(file);
		}
		else if (buffer != "")
		{
			std::cout << "(Warning) Unknown section: " << buffer << ". Ignoring." << std::endl;
		}
		// Else ignore it without warning
	}


	return std::move(m_enemies);
}

void EnemyLoader::LoadEnemy(std::ifstream& stream)
{
	std::string buffer;
	EnemyData enemyData;

	while (stream)
	{
		stream >> buffer;

		if (buffer == "[/Enemy]")
		{
			m_enemies->push_back(enemyData);
			break;
		}

		if (buffer == "Name:")
			stream >> enemyData.Name;
		else if (buffer == "Health:")
			stream >> enemyData.Health;
		else if (buffer == "Attack:")
			stream >> enemyData.Attack;
		else if (buffer == "Defense:")
			stream >> enemyData.Defense;
		else if (buffer == "Speed:")
			stream >> enemyData.Speed;
		else if (buffer == "Actions:")
		{
			while (true) {
				stream >> buffer;

				if (!isdigit(buffer.at(0)))
					break;

				int actionID = std::stoi(buffer);

				// Check if the action ID exists as a key in the cached actions
				if (!m_cachedActions.contains(actionID))
					std::cout << "Action ID " << actionID << " out of bounds. Ignoring.\n";
				else
					enemyData.Actions.push_back(m_cachedActions[actionID]);
			}
		}
		
	}
}

void EnemyLoader::CacheAction(std::ifstream& stream)
{
	std::string buffer;
	int actionID = -1;

	ActionData actionData;

	while (stream)
	{
		stream >> buffer;

		if (buffer == "[/Action]")
		{
			if (actionID < 0)
				std::cout << "Action ID not found or invalid. (ID must be positive) Ignoring.\n";
			else
				m_cachedActions[actionID] = actionData;

			break;
		}

		if (buffer == "Id:")
			stream >> actionID;
		else if (buffer == "Name:")
			stream >> actionData.Name;
		else if (buffer == "HappinessModifier:")
			stream >> actionData.HappinessShift;
		else if (buffer == "Dialogue:")
			GetDialogue(stream, actionData.AssociatedDialogue.GetLinesReference());
	}
}

void EnemyLoader::GetDialogue(std::ifstream& stream, std::vector<std::string>& vectBuffer) const
{
	std::string line;

	while (stream)
	{
		std::string buffer;
		

		std::getline(stream, buffer);

		if (buffer == "-")
		{
			vectBuffer.push_back(line);
			line.clear();
		}
		else if (buffer == "---")
		{
			vectBuffer.push_back(line);
			line.clear();
			break;
		}
		else
		{
			if(line.empty())
				line = buffer;
			else
				line += "\n" + buffer;
		}
	}
}
