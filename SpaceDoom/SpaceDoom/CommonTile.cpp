#include "CommonTile.h"

CommonTile::CommonTile(string filename, float x, float y, float vy, float width, float height, Game* game)
	: Tile(filename, x, y, vy, width, height, game) {
	this->vy = vy;
	if (vy != 0) {
		tileAux = new Tile(filename, x, y + HEIGHT, width, height, game);
	}
}

void CommonTile::update() {
	if (vy != 0) {
		y = y + vy;
	}
}

void CommonTile::draw(float scrollX, float scrollY) {
	Actor::draw(scrollX, scrollY); // llamar al metodo del hijo

	if (tileAux != NULL) {
		tileAux->draw();
	}
}