#include "Player.h"


Player::Player(const std::string& playerName, int maxHP) :
	Damageable(maxHP),
	m_name(playerName)
{
	// Construct the player
}


void Player::Draw(sf::RenderWindow& window) const
{
	// Draw the player
}


const std::string& Player::GetName() const
{
	return m_name;
}

void Player::SetName(std::string name) {
	m_name = name;
}

