#pragma once

#include <SFML/Graphics.hpp>
#include <cmath>
#include "Target.hpp"


class SquareTarget : public Target {

public:
    SquareTarget(float speedX, float speedY, float x, float y, float sideLength, sf::Color color) :
        Target(speedX, speedY, sideLength),
        mRectangleShape({sideLength, sideLength})
    {
        mRectangleShape.setFillColor(color);
        mRectangleShape.setPosition(x, y);
        mShape = std::make_unique<sf::RectangleShape>(mRectangleShape);
    }
    SquareTarget(float speedX, float speedY, const sf::RectangleShape& square) :
        Target(speedX, speedY, square.getSize().x * 2),
        mRectangleShape(square.getSize())
    {
        mRectangleShape.setFillColor(square.getFillColor());
        mRectangleShape.setPosition(square.getPosition());
        mShape = std::make_unique<sf::RectangleShape>(mRectangleShape);
    }

    SquareTarget(SquareTarget&) = delete;


    std::unique_ptr<Target> Copy() const override;
    void Split(std::vector<std::unique_ptr<Target>>& newTargets) override;


    // Info functions
    void Print(std::ostream& os, const std::string& indent) const override;


    // Update functions
    void Die() override;

    // Operators
    bool operator==(const SquareTarget&) const;


private:
    sf::RectangleShape mRectangleShape;

};