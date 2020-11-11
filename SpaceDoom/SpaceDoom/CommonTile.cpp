#include "CommonTile.h"

CommonTile::CommonTile(string filename, float x, float y, float vy, Game* game)
	: Tile(filename, x, y, vy, game) {
	this->vy = vy;
	if (vy != 0) {
		tileAux = new Tile(filename, x, y + HEIGHT, game);
	}
}

void CommonTile::update() {
	if (vy != 0) {
		y = y + vy;
	}
}

void CommonTile::draw(float scrollY) {
	Actor::draw(); // llamar al metodo del hijo

	if (tileAux != NULL) {
		tileAux->draw();
	}
}