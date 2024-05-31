#ifndef SIMPLE_GAME_ROUND_TARGET_H
#define SIMPLE_GAME_ROUND_TARGET_H

#include <SFML/Graphics.hpp>
#include "Target.hpp"


class RoundTarget : public Target {
public:
    RoundTarget(float speedX, float speedY, float x, float y, float radius, sf::Color color) :
        Target(speedX, speedY, radius*2),
        mCircleShape(radius)
    {
        mCircleShape.setFillColor(color);
        mCircleShape.setPosition(x, y);
        mShape = std::make_unique<sf::CircleShape>(mCircleShape);
    }
    RoundTarget(float speedX, float speedY, const sf::CircleShape& circle) :
		Target(speedX, speedY, circle.getRadius()*2),
        mCircleShape(circle.getRadius())
	{
        mCircleShape.setFillColor(circle.getFillColor());
		mCircleShape.setPosition(circle.getPosition());
		mShape = std::make_unique<sf::CircleShape>(mCircleShape);
    }

    RoundTarget(const RoundTarget&) = delete;


    std::unique_ptr<Target> Copy() const override;
    void Split(std::vector<std::unique_ptr<Target>>& newTargets) override;


    // Info functions
    void Print(std::ostream& os, const std::string& indent) const override;


    // Update functions
    void Die() override;

    // Operators
    bool operator==(const RoundTarget&) const;


private:
    sf::CircleShape mCircleShape;

};


#endif //SIMPLE_GAME_ROUND_TARGET_H
