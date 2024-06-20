#pragma once

#include <SFML/Graphics.hpp>
#include <random>

class Shaker
{
public:
	Shaker() = default;
	explicit Shaker(sf::Transformable* object);
	explicit Shaker(sf::Transformable* object, bool keepShake);


	void Update(float deltaTime);
	void SetObjectToShake(sf::Transformable* object);
	void SetPreferedVector(const sf::Vector2f& vector);
	void SetMaxAmplitude(float amplitude);
	void ResetBasePosition();
	void AddShakeStress(float stress);
	void SetShakeStress(float stress);
	void SetShakeActive(bool active);
	void SetKeepShake(bool keepShake);
	void SetDrainSpeed(float speed);
	void StopShake();

private:
	void ShakeObject(float multiplier);

	sf::Transformable* m_objectToShake = nullptr;

	std::mt19937 gen{ std::random_device()() };
	std::uniform_real_distribution<> dis { 0.f, 1.f };

	sf::Vector2f m_preferedVector = { 1.f, 1.f };
	sf::Vector2f m_basePosition = { 0.f, 0.f };

	bool m_shakeActive = true;
	bool m_keepShake = false;

	float m_shakeStress = .0f;
	float m_shakeDrainSpeed = 2.f;
	float m_maxAmplitude = 1.f;
};