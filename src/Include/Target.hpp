#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <numbers>


enum class TargetStatus {
    Alive,
    Dying,
    Dead
};


class Target {

public:

    static constexpr float deviation = 30.f * static_cast<float>(std::numbers::pi) / 180.f; // 30 degrees in radians


	Target(float speedX, float speedY, float size) : speedX(speedX), speedY(speedY), size(size) {}
    Target(Target&) = delete;
    virtual ~Target() = default;


    virtual std::unique_ptr<Target> Copy() const = 0;
    virtual void Split(std::vector<std::unique_ptr<Target>>& root) = 0;


    // Update functions
    virtual void Update(const sf::Time& elapsedTime, const sf::Vector2u& windowSize);
    void DecreaseFramesToLive();
    virtual void Die(); // Sets targetStatus to Dying. Override for animations.
    void SetParent(Target* newParent) { parent = newParent; }
    void SetSpeed(float spdX, float spdY) { speedX = spdX; speedY = spdY; }



    // Info functions
    virtual bool HasTimeExpired() const;
    virtual bool Contains(const sf::Vector2f&) const;
    float GetSize() const;
    Target* GetParent() const { return parent; }
    sf::Vector2f GetSpeed() const { return sf::Vector2f(speedX, speedY); }
    virtual void Print(std::ostream& os, const std::string& indent) const = 0;


    // Drawing functions
    virtual void DrawCurrent(sf::RenderWindow&) const;

    // Operators
    bool operator==(const Target&) const = default;

    
    // Getters
    sf::Shape* GetShape() const { return mShape.get(); }


    std::unique_ptr<sf::Shape> mShape;
    
    float speedX;
    float speedY;
    float size;
    int framesToLive = 60;
    Target* parent = nullptr;
    TargetStatus targetStatus = TargetStatus::Alive;

};