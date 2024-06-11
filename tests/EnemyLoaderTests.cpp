#include <gtest/gtest.h>
#include "Enemy.h"
#include "EnemyLoader.h"
#include <fstream>


#define WRITE_IN_FILE(fileName, content) \
{ \
	std::ofstream file(fileName); \
	file << content; \
	file.close(); \
}


constexpr auto FILE_NAME = "Enemy_test.txt";



namespace EnemyReaderTests {

	TEST(LoadEnemiesFromFile, SimpleEnemyOneAction)
	{

		std::string content = R"(
[Action]
Id: 1
Name: FakeAttack
Dialogue:
This is a fake attack! And its description.
---
HappinessModifier: 15
[/Action]

[Enemy]
Name: TestEnemy
Health: 100
Attack: 10
Defense: 5
Speed: 0
Actions: 1 1
[/Enemy]
)";

		WRITE_IN_FILE(FILE_NAME, content)

		auto loader = EnemyLoader();

		auto enemies = loader.ReadFromFile(FILE_NAME);

		if (enemies == nullptr)
		{
			FAIL() << "Loader returned nullptr";
			return;
		}

		EXPECT_EQ(enemies->size(), 1);
		EXPECT_EQ(enemies->at(0).Name, "TestEnemy");
		EXPECT_EQ(enemies->at(0).Health, 100);
		EXPECT_EQ(enemies->at(0).Attack, 10);
		EXPECT_EQ(enemies->at(0).Defense, 5);
		EXPECT_EQ(enemies->at(0).Speed, 0);
		EXPECT_EQ(enemies->at(0).Actions.size(), 2);
		EXPECT_EQ(enemies->at(0).Actions.at(0).Name, "FakeAttack");
		EXPECT_EQ(enemies->at(0).Actions.at(0).AssociatedDialogue.GetLinesReference().size(), 1);
		EXPECT_EQ(enemies->at(0).Actions.at(0).HappinessShift, 15);
		EXPECT_EQ(enemies->at(0).Actions.at(0).AssociatedDialogue.GetLinesReference().at(0), "This is a fake attack! And its description.");
	}





	TEST(LoadEnemiesFromFile, MultipleDialogueLines)
	{
		// This test is to check if the loader can read multiple lines of dialogue in an action
		std::string content = R"(
[Action]
Id: 5
Name: FakeAttack
Dialogue:
This is a fake attack! And its description.
-
This is a second line of the fake attack.
But this is NOT third line.
---
HappinessModifier: 15
[/Action]

[Enemy]
Name: TestEnemy
Health: 100
Attack: 10
Defense: 5
Speed: 0
Actions: 5
[/Enemy]
)";

		WRITE_IN_FILE(FILE_NAME, content)

			auto loader = EnemyLoader();

		auto enemies = loader.ReadFromFile(FILE_NAME);

		if (enemies == nullptr)
		{
			FAIL() << "Loader returned nullptr";
			return;
		}

		EXPECT_EQ(enemies->size(), 1);
		EXPECT_EQ(enemies->at(0).Name, "TestEnemy");
		EXPECT_EQ(enemies->at(0).Health, 100);
		EXPECT_EQ(enemies->at(0).Attack, 10);
		EXPECT_EQ(enemies->at(0).Defense, 5);
		EXPECT_EQ(enemies->at(0).Speed, 0);
		EXPECT_EQ(enemies->at(0).Actions.size(), 1);
		EXPECT_EQ(enemies->at(0).Actions.at(0).Name, "FakeAttack");
		EXPECT_EQ(enemies->at(0).Actions.at(0).AssociatedDialogue.GetLinesReference().size(), 2);
		EXPECT_EQ(enemies->at(0).Actions.at(0).HappinessShift, 15);
		EXPECT_EQ(enemies->at(0).Actions.at(0).AssociatedDialogue.GetLinesReference().at(0), "This is a fake attack! And its description.");
		EXPECT_EQ(enemies->at(0).Actions.at(0).AssociatedDialogue.GetLinesReference().at(1), "This is a second line of the fake attack.\nBut this is NOT third line.");
	}





	TEST(LoadEnemiesFromFile, MistakeControl)
	{
		// This test is to check if the loader can handle mistakes in the file

		// It should ignore the 1 and 3 paragraphs as their names are wrong and load the 2nd and 4th paragraphs

		std::string content = R"(
[Actionnn]
Id: 5
Name: FakeAttack
Dialogue:
This is a fake attack! And its description.
-
This is a second line of the fake attack.
But this is NOT third line.
---
HappinessModifier: 15
[/Action]

[Action]
Id: 4
Name: FakeAttack
Dialogue:
This is a fake attack! And its description.
-
This is a second line of the fake attack.
But this is NOT third line.
---
HappinessModifier: 50
[/Action]

[Enemyy]
Name: TestEnemy
Health: 100
Attack: 10
Defense: 5
Speed: 0
Actions: 5
[/Enemy]

[Enemy]
Name: TestEnemy
Health: 100
Attack: 10
Defense: 5
Speed: 0
Actions: 4 4 4 4
[/Enemy]
)";

		WRITE_IN_FILE(FILE_NAME, content)

			auto loader = EnemyLoader();

		auto enemies = loader.ReadFromFile(FILE_NAME);

		if (enemies == nullptr)
		{
			FAIL() << "Loader returned nullptr";
			return;
		}

		EXPECT_EQ(enemies->size(), 1);
		EXPECT_EQ(enemies->at(0).Name, "TestEnemy");
		EXPECT_EQ(enemies->at(0).Health, 100);
		EXPECT_EQ(enemies->at(0).Attack, 10);
		EXPECT_EQ(enemies->at(0).Defense, 5);
		EXPECT_EQ(enemies->at(0).Speed, 0);
		EXPECT_EQ(enemies->at(0).Actions.size(), 4);
		EXPECT_EQ(enemies->at(0).Actions.at(0).Name, "FakeAttack");
		EXPECT_EQ(enemies->at(0).Actions.at(0).AssociatedDialogue.GetLinesReference().size(), 2);
		EXPECT_EQ(enemies->at(0).Actions.at(0).HappinessShift, 50);
		EXPECT_EQ(enemies->at(0).Actions.at(0).AssociatedDialogue.GetLinesReference().at(0), "This is a fake attack! And its description.");
		EXPECT_EQ(enemies->at(0).Actions.at(0).AssociatedDialogue.GetLinesReference().at(1), "This is a second line of the fake attack.\nBut this is NOT third line.");
	}

}