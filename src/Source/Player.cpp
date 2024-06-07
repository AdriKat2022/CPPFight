#include "Player.h"


Player::Player(const std::string& playerName, int maxHP) :
	Damageable(maxHP),
	m_name(playerName)
{
	// Construct the player
}

const std::string& Player::GetName() const
{
	return m_name;
}