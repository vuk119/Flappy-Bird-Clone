#ifndef RPIPE_H_
#define RPIPE_H_

#include <SFML/Graphics.hpp>

using namespace sf;

class rPipe
{

	float m_X;
	float m_Xspeed = 250;

	const float m_Width = 180;
	float m_Position;

	int m_Angle;

	Texture m_Texture;

	Sprite m_Sprite;

	bool m_Scored;

public:
	rPipe();
	~rPipe();

	Sprite getSprite();
	void setNewY();
	void updateSprite();
	void changeScored();
	bool getScored();
	float getX();
	float getBotY();
	float getWidth();
	void setX(float x);
	void update(float timeElapsed);
	void setRotationAngle(int angle);
};

#endif
