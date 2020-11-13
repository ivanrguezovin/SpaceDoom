#include "Tile.h"

Tile::Tile(string filename, float x, float y, float width, float height, Game* game)
	: Actor(filename, x, y, width, height, game) {
}

Tile::Tile(string filename, float x, float y, float vy, float width, float height, Game* game)
	: Actor(filename, x, y, width, height, game) {
	this->vy = vy;
	if (vy != 0) {
		tileAux = new Tile(filename, x, y + HEIGHT, width, height, game);
	}
}

void Tile::update() {
	if (vy != 0) {
		y = y + vy;
	}
}

void Tile::draw(float scrollY) {
	Actor::draw(); // llamar al metodo del hijo

	if (tileAux != NULL) {
		tileAux->draw();
	}
}

bool Tile::destroyByProjectile() {
	return false;
}

bool Tile::isTurret() {
	return false;
}

ProjectileTurret* Tile::shoot() {
	return NULL;
}