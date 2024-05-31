#include "Target.hpp"

using namespace std;

void Target::DecreaseFramesToLive()
{
    if(framesToLive <= 0)
		targetStatus = TargetStatus::Dead;
    else
	    framesToLive -= 1;
}

bool Target::HasTimeExpired() const
{
	return targetStatus == TargetStatus::Dead;
}

bool Target::Contains(const sf::Vector2f& point) const
{
	return mShape->getGlobalBounds().contains(point);
}

float Target::GetSize() const
{
    return size;
}

void Target::DrawCurrent(sf::RenderWindow& mWindow) const
{
    mWindow.draw(*mShape);
}


void Target::Update(const sf::Time& elapsedTime, const sf::Vector2u& windowSize) {

    sf::Vector2f shapePosition = mShape->getPosition();

    if (targetStatus == TargetStatus::Dead)
		return;
	
    if (targetStatus == TargetStatus::Dying) {
        DecreaseFramesToLive();
        auto scale = mShape->getScale().x;
        auto newScale = scale * 0.8f;
        mShape->setScale({newScale , newScale});
        float newLocation = (scale - newScale) * size/2;
        mShape->move({newLocation, newLocation});

        return;
    }

    // Left bounce
    if (shapePosition.x + speedX * elapsedTime.asSeconds() < 0) {
        speedX = -speedX;
    }
    // Right bounce
    else if (shapePosition.x + size + speedX * elapsedTime.asSeconds() > static_cast<float>(windowSize.x)) {
        speedX = -speedX;
    }

    // Up bounce
    if (shapePosition.y + speedY * elapsedTime.asSeconds() < 0) {
        speedY = -speedY;
    }
    // Bottom bounce
    else if (shapePosition.y + size + speedY * elapsedTime.asSeconds() > static_cast<float>(windowSize.y)) {
        speedY = -speedY;
    }

    sf::Vector2f movement{ speedX, speedY };


    mShape->move(movement * elapsedTime.asSeconds());
}

void Target::Die()
{
    if (targetStatus != TargetStatus::Alive)
        return;

    targetStatus = TargetStatus::Dying;

    if (parent)
		parent->Die();
	
}