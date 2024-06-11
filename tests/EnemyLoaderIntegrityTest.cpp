#include <gtest/gtest.h>
#include "Enemy.h"
#include "EnemyLoader.h"
#include <fstream>


constexpr auto FILE_NAME = "resources/Enemies/Enemies.txt";


namespace EnemyLoaderIntegrityTest {

	TEST(IntegrityTest, GeneralIntegrity)
	{
		// Not working yet, need to fix the "file path"
		
		auto loader = EnemyLoader();

		auto enemies = loader.ReadFromFile(FILE_NAME, );

		if (enemies == nullptr)
		{
			FAIL() << "Loader returned nullptr";
			return;
		}
	}
}