#include "DestroyableTile.h"

DestroyableTile::DestroyableTile(string filename, float x, float y, float vy, float width, float height, Game* game)
	: Tile(filename, x, y, vy, width, height, game) {
	this->vy = vy;
	if (vy != 0) {
		tileAux = new Tile(filename, x, y + HEIGHT, width, height, game);
	}
}

void DestroyableTile::update() {
	if (vy != 0) {
		y = y + vy;
	}
}

void DestroyableTile::draw(float scrollY) {
	Actor::draw(); // llamar al metodo del hijo

	if (tileAux != NULL) {
		tileAux->draw();
	}
}

bool DestroyableTile::destroyByProjectile() {
	return true;
}