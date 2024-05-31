#include <cstdlib>
#include <ctime>
#include <iostream>
#include <random>
#include <cmath>
#include <numbers>
#include <algorithm>
#include "Game.hpp"
#include "Target.hpp"
#include "GroupTarget.hpp"
#include "RoundTarget.hpp"
#include "SquareTarget.hpp"
#include "StringHelpers.hpp"



using namespace std;


constexpr int MAX_TARGETS = 100;
constexpr int MAX_TARGETS_DEBUG = 2;

const sf::Time Game::TimePerFrame = sf::seconds(1.f/60.f);



static int Random_0_N(int const nbMax)
{
	static std::random_device rd;
	static std::default_random_engine engine(rd());
	std::uniform_int_distribution distribution(0, nbMax);
	return { distribution(engine) };
}
static sf::Vector2i Random_Vector()
{
	int magnitude = Random_0_N(50)+50;
	int angle = Random_0_N(360);

	return { static_cast<int>(magnitude * cos(angle * std::_Pi_val / 180.f)), static_cast<int>(magnitude * sin(angle * std::_Pi_val  / 180.f)) };
}

Game::Game()
{
	mFont.loadFromFile("media/Sansation.ttf");
	mStatisticsText.setFont(mFont);
	mStatisticsText.setPosition(5.f, 5.f);
	mStatisticsText.setCharacterSize(10);
}

void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	GenerateRandomTargetsDebug(targets);

	DumpAllTargets();

	mWindow.setVerticalSyncEnabled(true);


	while (mWindow.isOpen())
	{
		sf::Time elapsedTime = clock.restart();
		timeSinceLastUpdate += elapsedTime;
		while (timeSinceLastUpdate > TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;

			processEvents();
			update(TimePerFrame);
		}

		updateStatistics(elapsedTime);
		render();
	}
}

void Game::LeftClickHandle() {
	sf::Vector2i mousePosition = sf::Mouse::getPosition(mWindow);

	for (auto iter = targets.rbegin(); iter != targets.rend(); iter++) {
		// If the mouse is inside the target, delete it and stop the loop

		if (iter->get()->Contains(static_cast<sf::Vector2f>(mousePosition))) {
			iter->get()->Die();
			break;
		}
	}
}

void Game::RightClickHandle()
{
	sf::Vector2i mousePosition = sf::Mouse::getPosition(mWindow);

	for (auto iter = targets.rbegin(); iter != targets.rend(); iter++) {
		// If the mouse is inside the target, split it and stop the loop

		if (iter->get()->Contains(static_cast<sf::Vector2f>(mousePosition))) {
			SplitTarget(iter);
			break;
		}
	}
}

void Game::GenerateRandomRoundTarget(std::vector<std::unique_ptr<Target>>& vect, const std::vector<sf::Color>& COLORS)
{
	int size = Random_0_N(40) + 10;
	sf::Vector2i randomVector = Random_Vector();
	sf::Color randomColor = COLORS[Random_0_N(static_cast<int>(COLORS.size()) - 1)];

	vect.push_back(std::make_unique<RoundTarget>(
		randomVector.x,
		randomVector.y,
		Random_0_N(mWindow.getSize().x - 2 * size),
		Random_0_N(mWindow.getSize().y - 2 * size),
		size,
		randomColor
	));
}

void Game::GenerateRandomSquareTarget(std::vector<std::unique_ptr<Target>>& vect, const std::vector<sf::Color>& COLORS)
{
	int size = Random_0_N(40) + 10;
	sf::Vector2i randomVector = Random_Vector();
	sf::Color randomColor = COLORS[Random_0_N(static_cast<int>(COLORS.size()) - 1)];

	vect.push_back(std::make_unique<SquareTarget>(
		randomVector.x,
		randomVector.y,
		Random_0_N(mWindow.getSize().x - 2 * size),
		Random_0_N(mWindow.getSize().y - 2 * size),
		size,
		randomColor
	));
}

void Game::GenerateRandomTargets(std::vector<std::unique_ptr<Target>>& vect)
{
	const std::vector<sf::Color> COLORS = { sf::Color::Green, sf::Color::Magenta, sf::Color::Yellow, sf::Color::Blue, sf::Color::White };

	// Generating the 'MAX_TARGETS' targets
	for (int i = 0; i < MAX_TARGETS; i++) {

		int type = Random_0_N(2); // 0 for RoundTarget, 1 for SquareTarget, 2 for GroupTarget


		if (type == 0)
			GenerateRandomRoundTarget(vect, COLORS);
		else if (type == 1)
			GenerateRandomSquareTarget(vect, COLORS);
		else
			GenerateRandomGroupOfTargets(vect, COLORS);
	}
}

void Game::GenerateRandomTargetsGame(std::vector<std::unique_ptr<Target>>& vect)
{
	const std::vector<sf::Color> COLORS = { sf::Color::Green, sf::Color::Magenta, sf::Color::Yellow, sf::Color::Blue, sf::Color::White };


	GenerateRandomSquareTarget(vect, {sf::Color::Green});

	// Generating the 'MAX_TARGETS' targets
	for (int i = 0; i < MAX_TARGETS; i++) {
		GenerateRandomGroupOfTargets(vect, COLORS);
	}
}

void Game::GenerateRandomTargetsDebug(std::vector<std::unique_ptr<Target>>& vect)
{
	const std::vector<sf::Color> COLORS = { sf::Color::Green, sf::Color::Magenta, sf::Color::Yellow, sf::Color::Blue, sf::Color::White };
	// Generating the 'MAX_TARGETS' targets
	for (int i = 0; i < MAX_TARGETS_DEBUG; i++) {

		int type = Random_0_N(2); // 0 for RoundTarget, 1 for SquareTarget, 2 for GroupTarget


		if (type < 0)
			GenerateRandomRoundTarget(vect, COLORS);
		else if (type < 0)
			GenerateRandomSquareTarget(vect, COLORS);
		else
			GenerateRandomGroupOfTargets(vect, COLORS);
	}
}

void Game::GenerateRandomGroupOfTargets(std::vector<std::unique_ptr<Target>>& vect, [[maybe_unused]] const std::vector<sf::Color>& COLOR)
{
	int size = Random_0_N(3) + 2;

	vect.push_back(std::make_unique<GroupTarget>());
	auto group = static_cast<GroupTarget*>(vect.back().get());


	for (int i = 0; i < size; i++) {
		if (Random_0_N(1)) {
			GenerateRandomRoundTarget(group->subTargets, {sf::Color::Cyan});
			group->subTargets.back()->SetParent(group);
		}
		else {
			GenerateRandomSquareTarget(group->subTargets, {sf::Color::Cyan});
			group->subTargets.back()->SetParent(group);
		}
	}
}

void Game::SplitTarget(const std::reverse_iterator<std::vector<std::unique_ptr<Target>>::iterator>& targetToSplit)
{
	targetToSplit->get()->Split(targets);
}

void Game::DumpAllTargets() const
{
	for (const auto& target : targets) {
		target.get()->Print(std::cout, "");
	}
}

void Game::RemoveTarget(const std::reverse_iterator<std::vector<std::unique_ptr<Target>>::iterator>& iterTarget) {
	// Remove the target from the vector
	targets.erase(std::next(iterTarget).base());
}

void Game::processEvents()
{
    sf::Event event{sf::Event::Count}; // Initialization to an impossible value (in order to suppress Clang-Tidy warning)
	while (mWindow.pollEvent(event))
	{
		switch (event.type)
		{
			case sf::Event::MouseButtonPressed:
				if (event.mouseButton.button == sf::Mouse::Left) LeftClickHandle();
				else if (event.mouseButton.button == sf::Mouse::Right) RightClickHandle();
				break;

			case sf::Event::Closed:
				mWindow.close();
				break;

            default:
                // We simply ignore all other events
                break;
		}
	}
}

void Game::update(sf::Time elapsedTime)
{
	for (auto iter = targets.begin(); iter != targets.end();) {
		iter->get()->Update(elapsedTime, mWindow.getSize());
		if (iter->get()->HasTimeExpired()) {
			iter = targets.erase(iter);
			cout << "Target removed" << endl;
		}
		else {
			++iter;
		}
	}
}

void Game::DrawShapes() {
	for (const auto& roundTarget : targets) {
		roundTarget->DrawCurrent(mWindow);
	}
}

void Game::render()
{
	mWindow.clear();
	DrawShapes();
	mWindow.draw(mStatisticsText);
	mWindow.display();
}

void Game::updateStatistics(sf::Time elapsedTime)
{
	mStatisticsUpdateTime += elapsedTime;
	mStatisticsNumFrames += 1;

	if (mStatisticsUpdateTime >= sf::seconds(1.0f))
	{
		mStatisticsText.setString(
			"Frames / Second = " + toString(mStatisticsNumFrames) + "\n" +
			"Time / Update = " + toString(mStatisticsUpdateTime.asMicroseconds() / mStatisticsNumFrames) + "us");
							 
		mStatisticsUpdateTime -= sf::seconds(1.0f);
		mStatisticsNumFrames = 0;
	}
}