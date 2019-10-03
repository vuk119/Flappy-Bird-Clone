#ifndef BIRD_H_
#define BIRD_H_

#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>

using namespace sf;

class Bird
{
private:
	float m_X;
	float m_Y;
	
	Sprite m_Sprite;
	Texture m_Texture;
	
	bool type = 0; // 0 for normal bird and 1 for super bird

	const float m_Gravity = 350;
	const float m_LiftImpulse = 400;
	const float m_RotationSpeed = 200;

	bool m_Lift;
	int m_NumberOfLifts;
	float m_LastLiftTime;

public:
	Bird();
	~Bird();

	void spawn(Vector2f resolution);
	Sprite getSprite();
	float getY();
	void setLastLiftTime(float LT);
	void lift();
	void update(float elapsedTime);
	void fall(float elapsedTime);
	inline float MAX(float a, float b)
	{
		return (a > b) ? a : b;
	}
};

#endif