// FlappyBird.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "Bird.h"
#include "Ground.h"
#include "Pipe.h"
#include "score.h"

using namespace sf;
using namespace std;

bool checkForCollision(float birdY, float pipeX, float pipeBot, float pipeWidth, Vector2f resolution)
{
	return(pipeX < resolution.x / 2 && pipeX + 138>resolution.x / 2 && (birdY+10 > pipeBot || birdY-20 < pipeBot - pipeWidth));
}

bool checkForScore(float birdX, float pipeX)
{
	return (abs(birdX - (pipeX+138/2)) < 3);
}

int main()
{
	// The game will always be in one of four states
	enum class State { PAUSED, GAME_OVER, PLAYING,FALLING};
	// Start with the PAUSED state
	State state = State::PAUSED;

	// Get the screen resolution and create an SFML window
	Vector2f resolution;
	resolution.x = 590;
	resolution.y = 790;

	//Window
	RenderWindow window(VideoMode(resolution.x, resolution.y,32),
		"Flappy Bird", Style::Default);
	bool acceptInput = true;

	// Here is our clock for timing everything
	Clock clock;
	Clock liftClock;

	// How long has the PLAYING state been active
	Time gameTime;

	//PLAYER HUD
	score score;
	Text log;
	Font font;
	font.loadFromFile("font/04B_19__.ttf");
	log.setFont(font);
	log.setFillColor(Color::White);
	log.setCharacterSize(70);
	log.setOutlineColor(Color::Black);
	log.setOutlineThickness(5);


	//Sound
	SoundBuffer scoreBuffer;
	Sound scoreSound;
	scoreBuffer.loadFromFile("Sound/sfx_point.wav");
	scoreSound.setBuffer(scoreBuffer);
	scoreSound.setVolume(30);

	SoundBuffer liftBuffer;
	Sound liftSound;
	liftBuffer.loadFromFile("Sound/sfx_wing.wav");
	liftSound.setBuffer(liftBuffer);
	liftSound.setVolume(20);

	SoundBuffer hitBuffer;
	Sound hitSound;
	hitBuffer.loadFromFile("Sound/sfx_hit.wav");
	hitSound.setBuffer(hitBuffer);
	hitSound.setVolume(20);

	SoundBuffer dieBuffer;
	Sound dieSound;
	dieBuffer.loadFromFile("Sound/sfx_die.wav");
	dieSound.setBuffer(dieBuffer);
	dieSound.setVolume(20);

	//Prepare the bird
	Bird bird;
	bird.spawn(resolution);

	//Prepare the ground
	Ground ground;

	//Prepare the pipes
	Pipe pipe1;
	Pipe pipe2;
	pipe2.setX(pipe2.getX() + 400);

	Texture textureBackground;
	textureBackground.loadFromFile("graphics/background.png");
	Sprite spriteBackground;
	spriteBackground.setTexture(textureBackground);
	spriteBackground.setPosition(0, 0);
	Texture textureBelowGround;
	textureBelowGround.loadFromFile("graphics/belowground.png");
	Sprite spriteBelowGround;
	spriteBelowGround.setTexture(textureBelowGround);
	spriteBelowGround.setPosition(0, 700);

	while (window.isOpen())
	{
		
		//Handling the events 
		Event event;
		while (window.pollEvent(event))
		{

			// "close requested" event: we close the window
			if (event.type == Event::Closed)
				window.close();
			//Reads the keyboard input
			if (event.type == Event::KeyPressed && acceptInput)
			{
				acceptInput = false;
				//Start or restart the game 
				if (event.key.code == Keyboard::Space &&
					state == State::GAME_OVER)
				{
					state = State::PAUSED;
					score.restart();
					//spawn new pipes
					pipe1.setNewY();
					pipe1.setX(200 + 590);
					pipe2.setNewY();
					pipe2.setX(200 + 590 + 400);
					pipe1.updateSprite();
					pipe2.updateSprite();
					if(pipe1.getScored())
						pipe1.changeScored();
					if(pipe2.getScored())
						pipe2.changeScored();
					//spawn new bird
					bird.spawn(resolution);
				}
				//Pause the game
				else if (event.key.code == Keyboard::P &&
					state == State::PLAYING)
					state = State::PAUSED;
				//Resume the game
				else if (event.key.code == Keyboard::Space &&
					state == State::PAUSED)
				{
					state = State::PLAYING;
					clock.restart();
					liftClock.restart();
					bird.lift();
					liftSound.play();
				}
				//Lift
				else if (event.key.code == Keyboard::Space &&
					state == State::PLAYING)
				{
					bird.lift();
					liftClock.restart();
					liftSound.play();
				}
				else if (event.key.code == Keyboard::Escape)
					window.close();
			}
			//Alows the next keyboard input to come
			if (event.type == Event::KeyReleased)
				acceptInput = true;
		}

		//Updating the state of the game
		if (state == State::PLAYING)
		{
			bird.update(clock.getElapsedTime().asSeconds());
			ground.update(clock.getElapsedTime().asSeconds());
			pipe1.update(clock.getElapsedTime().asSeconds());
			pipe2.update(clock.getElapsedTime().asSeconds());
			clock.restart();
			bird.setLastLiftTime(liftClock.getElapsedTime().asSeconds());

			//Check if the bird hit the ground
			if (bird.getY() > 680)
			{
				dieSound.play();
				state = State::GAME_OVER;
			}
			//Check if the bird hit a pipe
			if (checkForCollision(bird.getY(), pipe1.getX(), pipe1.getBotY(), pipe1.getWidth(), resolution) ||
				checkForCollision(bird.getY(), pipe2.getX(), pipe2.getBotY(), pipe2.getWidth(), resolution))
			{
				state = State::FALLING;
				hitSound.play();
			}
			//Check and update the score
			if (checkForScore(resolution.x/2, pipe1.getX()) && !pipe1.getScored())
			{
				score.update();
				scoreSound.play();
				pipe1.changeScored();
			}
			if (checkForScore(resolution.x / 2, pipe2.getX()) && !pipe2.getScored())
			{
				score.update();
				scoreSound.play();
				pipe2.changeScored();
			}
		}
		//Letting bird to fall after hitting a pipe
		if (state == State::FALLING)
		{
			log.setString("GAME OVER");
			log.setOrigin(log.getLocalBounds().width/2, log.getLocalBounds().height / 2);
			log.setPosition(resolution.x / 2, 300);

			bird.fall(clock.getElapsedTime().asSeconds());
			clock.restart();
			if (bird.getY() > 680)
			{
				dieSound.play();
				state = State::GAME_OVER;	
			}
		}
		if (state == State::PAUSED)
		{
			log.setString("PRESS SPACE");
			log.setOrigin(log.getLocalBounds().width / 2, log.getLocalBounds().height / 2);
			log.setPosition(resolution.x / 2, 300);
		}
		//Drawing
		window.draw(spriteBackground);
		window.draw(pipe1.getBotSprite());
		window.draw(pipe1.getTopSprite());
		window.draw(pipe2.getBotSprite());
		window.draw(pipe2.getTopSprite());
		window.draw(spriteBelowGround);
		window.draw(ground.getSprite());
		window.draw(bird.getSprite());
		window.draw(score.getText());
		if (state == State::FALLING || state==State::GAME_OVER || state==State::PAUSED)
			window.draw(log);
		//Displaying
		window.display();
	}
    return 0;
}

