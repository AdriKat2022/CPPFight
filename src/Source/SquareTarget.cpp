#include "SquareTarget.hpp"
#include "GroupTarget.hpp"

using namespace std;
using namespace sf;


std::unique_ptr<Target> SquareTarget::Copy() const
{
	auto newSquareTarget = make_unique<SquareTarget>(speedX, speedY, mShape->getPosition().x, mShape->getPosition().y, size, mShape->getFillColor());

	return move(newSquareTarget);
}

void SquareTarget::Split(std::vector<std::unique_ptr<Target>>& root)
{
	if (size < 10)
	{
		Die();
		return;
	}

	size /= 2;
	auto roundShape = static_cast<RectangleShape*>(mShape.get());
	roundShape->setSize(Vector2f(size, size));

	auto newRoundTarget = this->Copy();
	auto currentSpeed = newRoundTarget->GetSpeed();
	float currentAngle = acos(currentSpeed.x / 100.f); // 100 is known to be the magnitude of the speed vector
	float newAngle1 = currentAngle + deviation;
	float newAngle2 = currentAngle - deviation;
	float dir = currentSpeed.y > 0 ? 1.f : -1.f;

	// Set the new speed for the current target and the new target
	newRoundTarget->SetSpeed(100 * cos(newAngle1), dir * 100 * sin(newAngle1));
	this->SetSpeed(100 * cos(newAngle2), dir * 100 * sin(newAngle2));

	if (parent) {
		auto group = static_cast<GroupTarget*>(parent);
		group->subTargets.push_back(move(newRoundTarget));
	}
	else
		root.push_back(move(newRoundTarget));
}

void SquareTarget::Print(std::ostream& os, const std::string& indent) const
{
	os << indent << "SquareTarget: x=" << mShape->getPosition().x << ", y=" << mShape->getPosition().y << std::endl;
}

void SquareTarget::Die() {
	Target::Die();

	mShape->setFillColor(sf::Color::Red);

	if (targetStatus != TargetStatus::Alive)
		return;
}


bool SquareTarget::operator==(const SquareTarget& other) const
{
	bool result = true;
	result &= mShape->getPosition() == other.mShape->getPosition();
	result &= mShape->getFillColor() == other.mShape->getFillColor();
	result &= mShape->getOutlineColor() == other.mShape->getOutlineColor();
	result &= mShape->getOutlineThickness() == other.mShape->getOutlineThickness();
	result &= size == other.size;
	result &= speedX == other.speedX;
	result &= speedY == other.speedY;
	result &= targetStatus == other.targetStatus;
	result &= framesToLive == other.framesToLive;
	result &= parent == other.parent;

	return result;
}