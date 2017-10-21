#include "Engine.h"

using namespace std;
using namespace sf;

const float WINDOW_HEIGHT = 480.0;
const float WINDOW_WIDTH = 640.0;

int main()
{
	string windowTitle = "Modernized Pong :)";
	RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), windowTitle);
	window.setFramerateLimit(140);

	Engine game(WINDOW_HEIGHT, WINDOW_WIDTH);
	bool flag = true;
	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}

		if (flag) {
			while (true) {
				window.clear(Color(79, 57, 57));
				game.poweredBy(window);
				window.display();
				if (Keyboard::isKeyPressed(Keyboard::Space)) break;
			}
			flag = false;
		}
		window.clear(Color(79, 57, 57));
		game.gameInfo(window);
		game.update(window);
		game.moveLeftPaddle();
		game.moveRightPaddle();
		game.drawLeftPaddle(window);
		game.drawRightPaddle(window);
		game.moveBall();
		game.drawBall(window);

		window.display();
	}
	return 0;
}
