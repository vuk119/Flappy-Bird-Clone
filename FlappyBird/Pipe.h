#ifndef PIPE_H_
#define PIPE_H_

#include <SFML/Graphics.hpp>

using namespace sf;

class Pipe
{
	float m_X;
	float m_Xspeed =250;

	const float m_Width = 180;
	float m_BotPosition;

	Texture m_BotTexture;
	Texture m_TopTexture;

	Sprite m_BotSprite;
	Sprite m_TopSprite;

	bool m_Scored;

public:

	Pipe();
	~Pipe();

	Sprite getTopSprite();
	Sprite getBotSprite();
	void setNewY();
	void updateSprite();
	void changeScored();
	bool getScored();
	float getX();
	float getBotY();
	float getWidth();
	void setX(float x);
	void update(float timeElapsed);
};


#endif