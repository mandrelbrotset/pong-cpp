#include "engine.h"
#include <iostream>
#include <string>

Engine::Engine(int height, int width) {
	windowHeight = height;
	windowWidth = width;
	paddingTop = 0;
	paddleWidth = 30;
	paddleHeight = 90;
	leftPaddleColor = Color(20, 147, 46);
	rightPaddleColor = Color(244, 66, 66);
	leftPaddle_Y = rand() % (windowHeight - 90);
	rightPaddle_Y = rand() % (windowHeight - 90);
	ballSide = 20;
	srand(1);
	ball_X = rand() % (windowWidth - ballSide);
	ball_Y = rand() % (windowHeight + paddingTop - ballSide);
	ballSpeed = 1.5;
	paddleSpeed = 4.0;
	directionX = 1;
	directionY = 1;
	scoreLeft = 0;
	scoreRight = 0;
	if (!font.loadFromFile("Thintel.ttf"))
	{
		cout << "[ERROR] Couldn't load font file" << endl;
	}
}

void Engine::moveLeftPaddle() {
	if (Keyboard::isKeyPressed(Keyboard::W)) {
		this->setLeftPaddle_Y(getLeftPaddle_Y() - paddleSpeed);
	}
	if (Keyboard::isKeyPressed(Keyboard::S)) {
		this->setLeftPaddle_Y(getLeftPaddle_Y() + paddleSpeed);
	}
}

void Engine::moveRightPaddle() {
	if (Keyboard::isKeyPressed(Keyboard::Up)) {
		this->setRightPaddle_Y(getRightPaddle_Y() - paddleSpeed);
	}
	if (Keyboard::isKeyPressed(Keyboard::Down)) {
		this->setRightPaddle_Y(getRightPaddle_Y() + paddleSpeed);
	}
}

void Engine::drawBall(RenderWindow &w) {
	RectangleShape rect(Vector2f(ballSide, ballSide));
	rect.setPosition(ball_X, ball_Y);
	rect.setFillColor(Color(66, 173, 244));
	w.draw(rect);
}

void Engine::drawLeftPaddle(RenderWindow &w) {
	RectangleShape rect(Vector2f(paddleWidth, paddleHeight));
	rect.setPosition(0, leftPaddle_Y);
	rect.setFillColor(leftPaddleColor);
	w.draw(rect);
}

void Engine::drawRightPaddle(RenderWindow &w) {
	RectangleShape rect(Vector2f(paddleWidth, paddleHeight));
	rect.setPosition(windowWidth - paddleWidth, rightPaddle_Y);
	rect.setFillColor(rightPaddleColor);
	w.draw(rect);
}

void Engine::poweredBy(RenderWindow &w) {
	Texture texture;
	if (!texture.loadFromFile("sfml-logo.png")){
		cout << "Error loading SFML loo" << endl;
	}
	texture.setSmooth(true);
	Sprite sprite;
	sprite.setTexture(texture);
	sprite.setPosition((windowWidth / 2) - 125, 145);

	Text p;
	p.setFont(font);
	p.setString("Pong");
	p.setCharacterSize(80);
	p.setFillColor(rightPaddleColor);
	p.setStyle(Text::Bold);
	p.setPosition((windowWidth / 2) - 60, 2);
	
	Text x;
	x.setFont(font);
	x.setString("Powered by SFML");
	x.setCharacterSize(80);
	x.setFillColor(leftPaddleColor);
	x.setStyle(Text::Bold);
	x.setPosition((windowWidth / 2) - 150, 65);

	Text y;
	y.setFont(font);
	y.setString("Press Space to start");
	y.setCharacterSize(60);
	y.setFillColor(leftPaddleColor);
	y.setStyle(Text::Bold);
	y.setPosition((windowWidth / 2) - 145, windowHeight - 110);

	Text z;
	z.setFont(font);
	z.setString("by Sheriff Olaoye");
	z.setCharacterSize(40);
	z.setFillColor(rightPaddleColor);
	z.setStyle(Text::Bold);
	z.setPosition((windowWidth / 2) - 110, windowHeight - 60);

	w.draw(sprite);
	w.draw(x);
	w.draw(p);
	w.draw(y);
	w.draw(z);
}

void Engine::update(RenderWindow &w) {
	Vector2u size = w.getSize();
	windowWidth = size.x;
	windowHeight = size.y;
}

void Engine::moveBall() {
	// to always move the ball
	ball_X += ballSpeed * directionX;
	ball_Y += ballSpeed * directionY;

	// ball hits top border
	if (this->ball_Y <= paddingTop) {
		this->directionY = 1;
	}
	// ball hits bottom border
	if (this->ball_Y >= windowHeight) {
		this->directionY = -1;
	}
	// ball hits left border
	if (this->ball_X <= 0) {
		this->directionX = 1;
		scoreRight += 1;
	}
	// ball hits right border
	if (this->ball_X >= windowWidth) {
		this->directionX = -1;
		scoreLeft += 1;
	}
	// ball hits left paddle
	if (ball_X <= paddleWidth && ball_Y >= leftPaddle_Y && ball_Y <= leftPaddle_Y + paddleHeight) {
		directionX = 1;
	}
	// ball hits right paddle
	if (ball_X >= windowWidth - paddleWidth && ball_Y >= rightPaddle_Y && ball_Y <= rightPaddle_Y + paddleHeight) {
		directionX = -1;
	}

}

// GET/SET FUNCTIONS
void Engine::setLeftPaddle_Y(int x) {
	if (x >= windowHeight) {
		// FIX PADDLE VIBRATION BUG
		leftPaddle_Y = windowHeight - paddleHeight;
	}
	else if (x < 0) {
		leftPaddle_Y = 0;
	}
	else {
		leftPaddle_Y = x;
	}
};

int Engine::getLeftPaddle_Y() {
	return leftPaddle_Y;
}

void Engine::setRightPaddle_Y(int x) {
	if (x >= windowHeight) {
		// FIX PADDLE VIBRATION BUG
		rightPaddle_Y = windowHeight - paddleHeight;
	}
	else if (x < 0) {
		rightPaddle_Y = 0;
	}
	else {
		rightPaddle_Y = x;
	}
};

int Engine::getRightPaddle_Y() {
	return rightPaddle_Y;
}

int Engine::getBall_X() {
	return ball_X;
}

int Engine::getBall_Y() {
	return ball_Y;
}

void Engine::gameInfo(RenderWindow &w) {
	Text leftScore;
	leftScore.setFont(font);
	leftScore.setString(to_string(scoreLeft));
	leftScore.setCharacterSize(100);
	leftScore.setFillColor(leftPaddleColor);
	leftScore.setStyle(Text::Bold);
	leftScore.setPosition((windowWidth / 2) - 50, 5);
	w.draw(leftScore);

	Text rightScore;
	rightScore.setFont(font);
	rightScore.setString(to_string(scoreRight));
	rightScore.setCharacterSize(100);
	rightScore.setFillColor(rightPaddleColor);
	rightScore.setStyle(Text::Bold);
	rightScore.setPosition((windowWidth / 2) + 50, 5);
	w.draw(rightScore);

}
