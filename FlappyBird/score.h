#ifndef SCORE_H_
#define SCORE_H_

#include <SFML/Graphics.hpp>

using namespace sf;

class score
{
	int m_number;
	Text m_text;
	Font m_font;


public:
	score();
	void update();
	void restart();
	Text getText();
	~score();
};

#endif