#include "Tile.h"

Tile::Tile(string filename, float x, float y, Game* game)
	: Actor(filename, x, y, 40, 40, game) {
	
}

Tile::Tile(string filename, float x, float y, float vy, Game* game)
	: Actor(filename, x, y, 40, 40, game) {
	this->vy = vy;
	if (vy != 0) {
		tileAux = new Tile(filename, x, y + HEIGHT, game);
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


ProjectileTurret* Tile::shoot() {
	return NULL;
}