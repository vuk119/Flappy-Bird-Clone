#ifndef GROUND_H_
#define GROUND_H_
#include <SFML/Graphics.hpp>

using namespace sf;


class Ground
{
	float m_X = 0;
	float m_Y = 695;
	float m_Xspeed = 250;
	const float m_MaxDisplacement = 550;

	Texture m_GroundTexture;
	Sprite m_GroundSprite;


public:
	Ground();
	void update(float timeElapsed);
	Sprite getSprite();
	~Ground();
};


#endif // !GROUND_H_