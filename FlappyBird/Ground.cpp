#include "stdafx.h"
#include "Ground.h"


Ground::Ground()
{
	m_GroundTexture.loadFromFile("graphics/ground.png");
	m_GroundSprite.setTexture(m_GroundTexture);
	m_GroundSprite.setPosition(Vector2f(m_X, m_Y));
}

void Ground::update(float timeElapsed)
{
	
	m_X -= m_Xspeed * timeElapsed;
	if (0 - m_X >= m_MaxDisplacement)
		m_X = 0;

	m_GroundSprite.setPosition(Vector2f(m_X, m_Y));
}

Sprite Ground::getSprite()
{
	return m_GroundSprite;
}


Ground::~Ground()
{
}
