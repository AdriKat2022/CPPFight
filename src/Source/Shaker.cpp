#include "Shaker.h"



Shaker::Shaker(sf::Transformable* object) :
	m_objectToShake(object),
	dis(0, 1),
	m_basePosition(object->getPosition())
{}

Shaker::Shaker(sf::Transformable * object, bool keepShake) :
	m_objectToShake(object),
	m_basePosition(object->getPosition()),
	m_keepShake(keepShake)
{}


void Shaker::Update(float deltaTime)
{
	if (!m_shakeActive && m_shakeStress <= 0)
		return;

	ShakeObject(m_shakeStress);

	if(!m_keepShake)
		m_shakeStress -= deltaTime * m_shakeDrainSpeed;
}

void Shaker::SetObjectToShake(sf::Transformable* object)
{
	m_objectToShake = object;
}

void Shaker::SetPreferedVector(const sf::Vector2f& vector)
{
	m_preferedVector = vector;
}

void Shaker::AddShakeStress(float stress)
{
	m_shakeStress += stress;
}

void Shaker::SetShakeActive(bool active)
{
	m_shakeActive = active;
}

void Shaker::SetKeepShake(bool keepShake)
{
	m_keepShake = keepShake;
}

void Shaker::SetDrainSpeed(float drainSpeed)
{
	m_shakeDrainSpeed = drainSpeed;
}

void Shaker::ShakeObject(float maxAmplitude)
{
	if (m_objectToShake == nullptr)
		return;

	float x = static_cast<float>(dis(gen) - .5f) * maxAmplitude * 2;
	float y = static_cast<float>(dis(gen) - .5f) * maxAmplitude * 2;
	

	m_objectToShake->move(x, y);
}

