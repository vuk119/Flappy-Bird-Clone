#include "stdafx.h"
#include "rPipe.h"
#include <random>


rPipe::rPipe()
{
	m_Position = rand() % 450 + 300;
	m_X = 200 + 590;
	m_Angle = 0;

	m_Texture.loadFromFile("graphics/bottom_pipe.png");
	m_Sprite.setTexture(m_Texture);
	m_Sprite.setOrigin(0, 0);
	m_Sprite.setPosition(m_X, m_Position);

	m_Scored = false;
}
rPipe::~rPipe()
{

}

void rPipe::update(float timeElapsed)
{
	m_X -= m_Xspeed * timeElapsed;
	if (m_X < -200)
	{
		m_Position = rand() % 300 + 300;
		m_X = 590;
		m_Scored = false;
	}
	updateSprite();

}
void rPipe::updateSprite()
{
	m_Sprite.setPosition(m_X, m_Position);
	m_Sprite.setPosition(m_X, m_Position - m_Width);
}
void rPipe::setRotationAngle(int angle)
{
	m_Angle = angle;
	m_Sprite.setRotation(angle);
}
void rPipe::setNewY()
{
	m_Position = rand() % 300 + 300;
}
float rPipe::getX()
{
	return m_X;
}
float rPipe::getBotY()
{
	return m_Position;
}
float rPipe::getWidth()
{
	return m_Width;
}
void rPipe::changeScored()
{
	m_Scored = !m_Scored;
}
bool rPipe::getScored()
{
	return m_Scored;
}
void rPipe::setX(float x)
{
	m_X = x;
}
Sprite rPipe::getSprite()
{
	return m_Sprite;
}