#include <gtest/gtest.h>
#include "Player.h"
#include "Enemy.h"



using namespace std;


namespace Global_test {

	TEST(PlayerTest, CorrectInitialization)
	{
		Player player("PlayerTest", 100);
		EXPECT_EQ(player.GetName(), "PlayerTest");
		EXPECT_EQ(player.GetHP(), 100);

		Player player2("PlayerTest", 50);
		EXPECT_EQ(player2.GetName(), "PlayerTest");
		EXPECT_EQ(player2.GetHP(), 50);
	}

	TEST(EnemyTest, CorrectInitialization)
	{
		Enemy enemy("EnemyTest", 100, 12);
		EXPECT_EQ(enemy.GetName(), "EnemyTest");
		EXPECT_EQ(enemy.GetHP(), 100);
		EXPECT_EQ(enemy.GetAttackPower(), 12);

		Enemy enemy2("EnemyTest", 50, 6);
		EXPECT_EQ(enemy2.GetName(), "EnemyTest");
		EXPECT_EQ(enemy2.GetHP(), 50);
		EXPECT_EQ(enemy2.GetAttackPower(), 6);
	}
	
}