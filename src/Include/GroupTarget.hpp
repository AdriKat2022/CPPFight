#pragma once

#include <vector>
#include <memory>
#include "Target.hpp"


class GroupTarget : public Target {

public:

    GroupTarget() :
		Target(0, 0, 0),
        subTargets(0)
	{}

    explicit GroupTarget(std::vector<std::unique_ptr<Target>>& targets) :
        Target(0, 0, 0),
        subTargets(std::move(targets))
    {}

    std::unique_ptr<Target> Copy() const override;
    void Split(std::vector<std::unique_ptr<Target>>& root) override;


    // Update functions
    void Update(const sf::Time& elapsedTime, const sf::Vector2u& windowSize) override;
    void DrawCurrent(sf::RenderWindow& mWindow) const override;
    bool Contains(const sf::Vector2f& point) const override;


    // Info functions
    void Print(std::ostream& os, const std::string& indent) const override;
    bool HasTimeExpired() const override;

    // Update functions
    void Die() override;

    // Operators
    bool operator==(const GroupTarget&) const;


    void AddTarget(std::unique_ptr<Target> target) {
		subTargets.push_back(std::move(target));
	}


    std::vector<std::unique_ptr<Target>> subTargets;
};