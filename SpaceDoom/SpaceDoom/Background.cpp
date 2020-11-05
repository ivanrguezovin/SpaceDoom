#include "Background.h"

Background::Background(string filename, float x, float y, Game* game)
	: Actor(filename, x, y, WIDTH, HEIGHT, game) {

}

Background::Background(string filename, float x, float y, float vy, Game* game)
	: Actor(filename, x, y, WIDTH, HEIGHT, game) {

	this->vy= vy;
	if (vy != 0) {
		backgroundAux = new Background(filename, x, y + HEIGHT, game);
	}
}

void Background::update() {
	if (vy != 0) {
		y = y + vy;

		if (y + height / 2 < 0) {
			y = HEIGHT + height / 2;
		}
		if (y - height / 2 > HEIGHT) {
			y = 0 - height / 2;
		}

	}
}

void Background::draw(float scrollY) {
	Actor::draw(); // llamar al metodo del hijo

	if (backgroundAux != NULL) {
		// zona sin cubrir por la izquierda
		if (y - height / 2 > 0) {
			// pintar aux por la izquierda
			backgroundAux->y = y - height;
		}
		// zona sin cubrir por la derecha
		if (y + height / 2 < HEIGHT) {
			// pintar aux por la derecha
			backgroundAux->y = y + height;
		}
		backgroundAux->draw();
	}

}
