#include "Tile.h"

Tile::Tile(string filename, float x, float y, Game* game)
	: Actor(filename, x, y, 40, 32, game) {
	
}

Tile::Tile(string filename, float x, float y, float vy, Game* game)
	: Actor(filename, x, y, 40, 32, game) {
	this->vy = vy;
	if (vy != 0) {
		tileAux = new Tile(filename, x, y + HEIGHT, game);
	}
}

void Tile::update() {
	if (vy != 0) {
		y = y + vy;
		/*
		if (y + height / 2 < 0) {
			y = HEIGHT + height / 2;
		}
		if (y - height / 2 > HEIGHT) {
			y = 0 - height / 2;
		}
		*/
	}
}

void Tile::draw(float scrollY) {
	Actor::draw(); // llamar al metodo del hijo

	if (tileAux != NULL) {
		tileAux->draw();
	}

}