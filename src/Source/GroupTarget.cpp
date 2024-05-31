#include <iostream>
#include "GroupTarget.hpp"

using namespace std;
using namespace sf;


std::unique_ptr<Target> GroupTarget::Copy() const
{
	// no need to implement this yet
	return nullptr;
}

void GroupTarget::Split(std::vector<std::unique_ptr<Target>>& newTargets)
{
	// Split all subtargets up to the last one
	// (we need to stop at the last one) because the split will create a new target that we don't want to split
	size_t last = subTargets.size();

	for (size_t i = 0; i < last; i++) {
		subTargets[i]->Split(newTargets);
	}
}

void GroupTarget::Print(std::ostream& os, const std::string& indent) const
{
	os << "GroupTarget: subTargets: {" << endl;

	for (auto& subTarget : subTargets) {
		subTarget.get()->Print(os, indent + "| ");
	}
}

bool GroupTarget::HasTimeExpired() const
{
	return std::ranges::all_of(subTargets, [](const auto& target) { return target->HasTimeExpired(); });
}

void GroupTarget::Die() {
	Target::Die();

	for (const auto& target : subTargets) {
		target->Die();
	}
}

void GroupTarget::Update(const sf::Time& elapsedTime, const sf::Vector2u& windowSize)
{
	for (auto const& target : subTargets) {
		target->Update(elapsedTime, windowSize);
	}
}

void GroupTarget::DrawCurrent(sf::RenderWindow& mWindow) const
{
	for (const auto& target : subTargets) {
		target->DrawCurrent(mWindow);
	}

	if(targetStatus != TargetStatus::Alive)
		return;

	// Trace a line between the targets
	for (size_t i = 0; i < subTargets.size() - 1; i++) {
		const Vector2f pos1 = subTargets[i]->mShape->getPosition() + Vector2f(subTargets[i]->GetSize()/2, subTargets[i]->GetSize()/2);
		const Vector2f pos2 = subTargets[i + 1]->mShape->getPosition() + Vector2f(subTargets[i+1]->GetSize()/2, subTargets[i+1]->GetSize()/2);

		const vector<Vertex> line = {
			Vertex(pos1),
			Vertex(pos2)
		};

		mWindow.draw(line.data(), line.size(), PrimitiveType::Lines);
	}


}

bool GroupTarget::Contains(const sf::Vector2f& point) const
{
	if(std::ranges::any_of(subTargets, [&point](const auto& target) { return target->Contains(point); }))
		return true;

	return false;
}

bool GroupTarget::operator==(const GroupTarget& other) const
{
	cout << "--- Operator == NOT SUPPORTED (yet) ---" << endl;

	return false;

	//for (auto& target : subTargets) {
	//	if(std::find(other.subTargets.begin(), other.subTargets.end(), target) == other.subTargets.end())
	//		return false;
	//}
}
