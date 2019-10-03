#include "stdafx.h"
#include "Pipe.h"
#include <random>


Pipe::Pipe()
{
    m_BotPosition = rand() % 450 + 300;
	m_X = 200 + 590;

	m_TopTexture.loadFromFile("graphics/top_pipe.png");
	m_TopSprite.setTexture(m_TopTexture);
	m_TopSprite.setOrigin(0, 793);
	m_TopSprite.setPosition(m_X, m_BotPosition - m_Width);

	m_BotTexture.loadFromFile("graphics/bottom_pipe.png");
	m_BotSprite.setTexture(m_BotTexture);
	m_BotSprite.setOrigin(0, 0);
	m_BotSprite.setPosition(m_X, m_BotPosition);

	m_Scored = false;
}
Pipe::~Pipe()
{

}

void Pipe::update(float timeElapsed)
{
		m_X -= m_Xspeed * timeElapsed;
		if (m_X < -200)
		{
			m_BotPosition = rand() % 300 + 300;
			m_X = 590;
			m_Scored = false;
		}
		updateSprite();

}
void Pipe::updateSprite()
{
	m_BotSprite.setPosition(m_X, m_BotPosition);
	m_TopSprite.setPosition(m_X, m_BotPosition - m_Width);
}
void Pipe::setNewY()
{
	m_BotPosition = rand() % 300 + 300;
}
float Pipe::getX()
{
	return m_X;
}
float Pipe::getBotY()
{
	return m_BotPosition;
}
float Pipe::getWidth()
{
	return m_Width;
}
void Pipe::changeScored()
{
	m_Scored = !m_Scored;
}
bool Pipe::getScored()
{
	return m_Scored;
}
void Pipe::setX(float x)
{
	m_X = x;
}
Sprite Pipe::getBotSprite()
{
	return m_BotSprite;
}
Sprite Pipe::getTopSprite()
{
	return m_TopSprite;
}
