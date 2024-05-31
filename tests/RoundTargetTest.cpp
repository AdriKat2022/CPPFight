#include <gtest/gtest.h>

#include "RoundTarget.hpp"
#include "SquareTarget.hpp"
#include "GroupTarget.hpp"


using namespace std;


namespace RoundTarget_test {

	static const sf::Time elapsedTime = sf::seconds(1.f / 60.f);
	constexpr auto notScreenBoundary = 200.f;
	constexpr auto radius = 50.f;
	constexpr auto speed = 100.f;
	const sf::Vector2u windowSize{ 640, 480 };

	TEST(RoundTargetTest, update_noBounce) {
		RoundTarget target{ speed, speed, notScreenBoundary, notScreenBoundary, radius, sf::Color::Cyan};

		target.Update(elapsedTime, windowSize);
		EXPECT_FLOAT_EQ(notScreenBoundary + speed * elapsedTime.asSeconds(), target.GetShape()->getPosition().x);
		EXPECT_FLOAT_EQ(notScreenBoundary + speed * elapsedTime.asSeconds(), target.GetShape()->getPosition().y);

		target.Update(elapsedTime, windowSize);
		EXPECT_FLOAT_EQ(notScreenBoundary + 2 * speed * elapsedTime.asSeconds(), target.GetShape()->getPosition().x);
		EXPECT_FLOAT_EQ(notScreenBoundary + 2 * speed * elapsedTime.asSeconds(), target.GetShape()->getPosition().y);
	}

	TEST(RoundTargetTest, update_bounceLeft) {
		RoundTarget target{ -speed, -speed, 0.f, notScreenBoundary, radius,  sf::Color::Cyan};

		target.Update(elapsedTime, windowSize);
		EXPECT_FLOAT_EQ(speed * elapsedTime.asSeconds()                         , target.GetShape()->getPosition().x);
		EXPECT_FLOAT_EQ(notScreenBoundary - speed * elapsedTime.asSeconds()     , target.GetShape()->getPosition().y);

		target.Update(elapsedTime, windowSize);
		EXPECT_FLOAT_EQ(2 * speed * elapsedTime.asSeconds()                     , target.GetShape()->getPosition().x);
		EXPECT_FLOAT_EQ(notScreenBoundary - 2 * speed * elapsedTime.asSeconds() , target.GetShape()->getPosition().y);
	}

	TEST(RoundTargetTest, update_bounceUp) {
		RoundTarget target{ speed, -speed, notScreenBoundary, 0.f, radius,  sf::Color::Cyan };

		target.Update(elapsedTime, windowSize);
		EXPECT_FLOAT_EQ(notScreenBoundary + speed * elapsedTime.asSeconds()     , target.GetShape()->getPosition().x);
		EXPECT_FLOAT_EQ(speed * elapsedTime.asSeconds()                         , target.GetShape()->getPosition().y);

		target.Update(elapsedTime, windowSize);
		EXPECT_FLOAT_EQ(notScreenBoundary + 2 * speed * elapsedTime.asSeconds() , target.GetShape()->getPosition().x);
		EXPECT_FLOAT_EQ(2 * speed * elapsedTime.asSeconds()                     , target.GetShape()->getPosition().y);
	}

	TEST(RoundTargetTest, update_bounceRight) {
		RoundTarget target{ speed, speed , static_cast<float>(windowSize.x) - 2 * radius, notScreenBoundary, radius, sf::Color::Cyan };

		float rad = dynamic_cast<sf::CircleShape*>(target.GetShape())->getRadius();

		EXPECT_FLOAT_EQ(rad, radius);

		target.Update(elapsedTime, windowSize);
		EXPECT_FLOAT_EQ(static_cast<float>(windowSize.x) - 2 * radius - speed * elapsedTime.asSeconds()		, target.GetShape()->getPosition().x);
		EXPECT_FLOAT_EQ(notScreenBoundary + speed * elapsedTime.asSeconds()									, target.GetShape()->getPosition().y);

		target.Update(elapsedTime, windowSize);
		EXPECT_FLOAT_EQ(static_cast<float>(windowSize.x) - 2 * radius - 2 * speed * elapsedTime.asSeconds()	, target.GetShape()->getPosition().x);
		EXPECT_FLOAT_EQ(notScreenBoundary + 2 * speed * elapsedTime.asSeconds()								, target.GetShape()->getPosition().y);
	}

	TEST(RoundTargetTest, update_bounceBottom) {
		RoundTarget target{ speed, speed, notScreenBoundary, static_cast<float>(windowSize.y) - 2 * radius, radius, sf::Color::Cyan};

		float rad = dynamic_cast<sf::CircleShape*>(target.GetShape())->getRadius();

		EXPECT_FLOAT_EQ(rad, radius);

		target.Update(elapsedTime, windowSize);
		EXPECT_FLOAT_EQ(notScreenBoundary + speed * elapsedTime.asSeconds()									, target.GetShape()->getPosition().x);
		EXPECT_FLOAT_EQ(static_cast<float>(windowSize.y) - 2 * radius - speed * elapsedTime.asSeconds()		, target.GetShape()->getPosition().y);

		target.Update(elapsedTime, windowSize);
		EXPECT_FLOAT_EQ(notScreenBoundary + 2 * speed * elapsedTime.asSeconds()								, target.GetShape()->getPosition().x);
		EXPECT_FLOAT_EQ(static_cast<float>(windowSize.y) - 2 * radius - 2 * speed * elapsedTime.asSeconds() , target.GetShape()->getPosition().y);
	}


	// GROUP TARGET TESTS


	TEST(GroupTargetTests, SimpleConstructor) {

		auto rT = make_unique<RoundTarget>(speed, speed, notScreenBoundary, notScreenBoundary, radius, sf::Color::Cyan);
		auto sT = make_unique<SquareTarget>(speed, speed, notScreenBoundary, notScreenBoundary, radius, sf::Color::Cyan);


		std::vector<std::unique_ptr<Target>> targets;
		targets.push_back(make_unique<RoundTarget>(speed, speed, notScreenBoundary, notScreenBoundary, radius, sf::Color::Cyan));
		targets.push_back(make_unique<SquareTarget>(speed, speed, notScreenBoundary, notScreenBoundary, radius, sf::Color::Cyan));


		GroupTarget group{ targets };


		EXPECT_EQ(group.subTargets.size(), 2);

		const auto& rT2 = group.subTargets[0].get();
		const auto& sT2 = group.subTargets[1].get();

		ostringstream osrT1;
		ostringstream osrT2;
		ostringstream ossT1;
		ostringstream ossT2;

		rT->Print(osrT1, "");
		rT2->Print(osrT2, "");
		sT->Print(ossT1, "");
		sT2->Print(ossT2, "");

		EXPECT_TRUE(osrT1.str() == osrT2.str());
		EXPECT_TRUE(ossT1.str() == ossT2.str());
	}

	TEST(RoundTargetComparaison, SimpleEqual) {

		RoundTarget t1(speed, speed, notScreenBoundary, notScreenBoundary, radius, sf::Color::Cyan);
		RoundTarget t2(speed, speed, notScreenBoundary, notScreenBoundary, radius, sf::Color::Cyan);

		RoundTarget t3(speed, speed	, notScreenBoundary, notScreenBoundary, radius, sf::Color::Red);
		RoundTarget t4(speed, speed	, notScreenBoundary, notScreenBoundary, radius, sf::Color::Cyan);
		RoundTarget t5(speed, 0		, notScreenBoundary, notScreenBoundary, radius, sf::Color::Cyan);
		RoundTarget t6(speed, 0		, notScreenBoundary, notScreenBoundary, radius, sf::Color::Cyan);



		EXPECT_TRUE(t1 == t2);
		EXPECT_TRUE(t1 != t3);
		EXPECT_TRUE(t2 != t3);
		EXPECT_TRUE(t4 != t5);
		EXPECT_TRUE(t5 == t6);
	}

	TEST(SquareTargetComparaison, SimpleEqual) {

		SquareTarget t1(speed, speed, notScreenBoundary, notScreenBoundary, radius, sf::Color::Cyan);
		SquareTarget t2(speed, speed, notScreenBoundary, notScreenBoundary, radius, sf::Color::Cyan);

		SquareTarget t3(speed, speed, notScreenBoundary, notScreenBoundary, radius, sf::Color::Red);
		SquareTarget t4(speed, speed, notScreenBoundary, notScreenBoundary, radius, sf::Color::Cyan);
		SquareTarget t5(speed, 0, notScreenBoundary, notScreenBoundary, radius, sf::Color::Cyan);
		SquareTarget t6(speed, 0, notScreenBoundary, notScreenBoundary, radius, sf::Color::Cyan);

		EXPECT_TRUE(t1 == t2);
		EXPECT_TRUE(t1 != t3);
		EXPECT_TRUE(t2 != t3);
		EXPECT_TRUE(t4 != t5);
		EXPECT_TRUE(t5 == t6);
	}

	TEST(CopyMechanism, RoundTargetCopy) {

		RoundTarget t1(speed, speed, notScreenBoundary, notScreenBoundary, radius, sf::Color::Cyan);
		auto t2 = t1.Copy();


		ostringstream osrT1;
		ostringstream osrT2;

		t1.Print(osrT1, "");
		t2->Print(osrT2, "");

		EXPECT_TRUE(osrT1.str() == osrT2.str());
	}
}