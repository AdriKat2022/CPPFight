#ifndef BOOK_GAME_HPP
#define BOOK_GAME_HPP

#include "SFML/Graphics.hpp"
#include "RoundTarget.hpp"
#include <vector>
#include <list>


class Game : private sf::NonCopyable
{
	public:
								Game();
		void					run();
		

	private:
		void					processEvents();
		void					update(sf::Time elapsedTime);
		void					render();
		void					DrawShapes();
		void					LeftClickHandle();
		void					RightClickHandle();

		// Generate functions
		void 					GenerateRandomTargets(std::vector<std::unique_ptr<Target>>&);
		void 					GenerateRandomTargetsGame(std::vector<std::unique_ptr<Target>>&);
		void 					GenerateRandomTargetsDebug(std::vector<std::unique_ptr<Target>>&);
		void 					GenerateRandomRoundTarget(std::vector<std::unique_ptr<Target>>&, const std::vector<sf::Color>&);
		void 					GenerateRandomSquareTarget(std::vector<std::unique_ptr<Target>>&, const std::vector<sf::Color>&);
		void 					GenerateRandomGroupOfTargets(std::vector<std::unique_ptr<Target>>&, const std::vector<sf::Color>&);

		void					SplitTarget(const std::reverse_iterator<std::vector<std::unique_ptr<Target>> ::iterator>&);

		void					DumpAllTargets() const;

		void					RemoveTarget(const std::reverse_iterator<std::vector<std::unique_ptr<Target>> ::iterator>&);

		void					updateStatistics(sf::Time elapsedTime);


		static const sf::Time	TimePerFrame;

		sf::RenderWindow		mWindow{sf::VideoMode{640, 480}, "SFML Application", sf::Style::Close};
		sf::Texture				mTexture;
		sf::Font				mFont;
		sf::Text				mStatisticsText;
		sf::Time				mStatisticsUpdateTime;

		std::size_t				mStatisticsNumFrames{0};

		std::vector<std::unique_ptr<Target>> targets;
};

#endif // BOOK_GAME_HPP
