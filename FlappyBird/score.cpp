#include "stdafx.h"
#include "score.h"

score::score()
{
	m_number = 0;
	m_font;
	m_font.loadFromFile("font/04B_19__.ttf");
	m_text.setFont(m_font);
	m_text.setFillColor(Color::White);
	m_text.setCharacterSize(70);
	m_text.setOutlineColor(Color::Black);
	m_text.setOutlineThickness(5);
	m_text.setString(std::to_string(m_number));
	m_text.setPosition(590/2 - m_text.getLocalBounds().width/2, 60);
}

score::~score()
{
}

void score::update()
{
	m_number++;
	m_text.setString(std::to_string(m_number));
	m_text.setPosition(590 / 2 - m_text.getLocalBounds().width / 2, 60);
}

void score::restart()
{
	m_number = 0;
	m_text.setString(std::to_string(m_number));
	m_text.setPosition(590 / 2 - m_text.getLocalBounds().width / 2, 60);
}

Text score::getText()
{
	return m_text;
}