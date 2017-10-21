#ifndef ENGINE_H
#define ENGINE_H

#include <iostream>
#include <string>
#include <SFML/graphics.hpp>
#include <cstdlib>

using namespace std;
using namespace sf;

class Engine {
private:
	int paddleWidth;
	int paddleHeight;
	Color leftPaddleColor;
	Color rightPaddleColor;
	int paddingTop;
	int windowHeight;
	int windowWidth;
	int leftPaddle_Y;
	int rightPaddle_Y;
	int ballSide;
	int ball_X;
	int ball_Y;
	float ballSpeed;
	float paddleSpeed;
	int directionX;
	int directionY;
	int scoreLeft;
	int scoreRight;
	Font font;
	
public:
	Engine(int x, int y);
	void moveLeftPaddle();
	void moveRightPaddle();
	void drawBall(RenderWindow &w);
	void drawLeftPaddle(RenderWindow &w);
	void drawRightPaddle(RenderWindow &w);
	void update(RenderWindow &w);
	void moveBall();
	void poweredBy(RenderWindow &w);
	// get set functions
	void setLeftPaddle_Y(int x);
	int getLeftPaddle_Y();
	void setRightPaddle_Y(int x);
	int getRightPaddle_Y();
	void setBall_X(int x);
	int getBall_X();
	void setBall_Y(int x);
	int getBall_Y();
	void gameInfo(RenderWindow &w);
};

#endif // ENGINE_H
