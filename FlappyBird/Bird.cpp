#include "stdafx.h"
#include "Bird.h"
#include <iostream>

Bird::Bird()
{
	m_Texture.loadFromFile("graphics/bird.png");
	m_Sprite.setTexture(m_Texture);
	m_Sprite.setOrigin(60, 60);

	m_Lift = false;
	m_LastLiftTime = 0;

}
Bird::~Bird()
{
}

void Bird::spawn(Vector2f resolution)
{
	m_X = resolution.x / 2;
	m_Y = resolution.y / 2;
	m_Sprite.setPosition(m_X, m_Y);
	m_Sprite.setRotation(0);
}
Sprite Bird::getSprite()
{
	return m_Sprite;
}
float Bird::getY()
{
	return m_Y;
}
void Bird::setLastLiftTime(float LT)
{
	m_LastLiftTime = LT;
}
void Bird::lift()
{
	m_Lift = true;
	m_NumberOfLifts = 350;
}
void Bird::update(float elapsedTime)
{
	//Check for the lift
	if (m_Lift)
	{
		//lift the bird
		m_Y -= m_LiftImpulse/350;
		m_NumberOfLifts--; 
		//adjust the rotation
		/*if(m_Sprite.getRotation()>330 || m_Sprite.getRotation()<100)
			m_Sprite.setRotation(m_Sprite.getRotation()-20);*/
		m_Sprite.setRotation(340);
		if(m_NumberOfLifts==0)
			m_Lift = false;
	}
	else
	{
		if (m_LastLiftTime > 0.3)
		{
			//rotate while falling
			if (m_Sprite.getRotation() < 90 || m_Sprite.getRotation() > 270)
				m_Sprite.setRotation(m_Sprite.getRotation() + m_RotationSpeed * elapsedTime);
		}
	
	}
	//Take gravity into account
	if (m_LastLiftTime>0.05)
	m_Y += m_Gravity * elapsedTime*(m_LastLiftTime-0.04)*3;
	
	//Check for the ceiling
	if (m_Y  < -100)
		m_Y = -100;

	//Add oscillations
	m_Y += (((float)rand()) / (float)RAND_MAX-0.5);

	//Update sprite position
	m_Sprite.setPosition(m_X, m_Y);

}

void Bird::fall(float elapsedTime)
{
	//rotate while falling
	if (m_Sprite.getRotation() < 90 || m_Sprite.getRotation() > 270)
		m_Sprite.setRotation(m_Sprite.getRotation() + m_RotationSpeed * elapsedTime);
	m_Y += m_Gravity * elapsedTime*2;
	m_Sprite.setPosition(m_X, m_Y);
}


