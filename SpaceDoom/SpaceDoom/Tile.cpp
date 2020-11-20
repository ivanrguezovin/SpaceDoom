#include "Tile.h"

Tile::Tile(string filename, float x, float y, float width, float height, Game* game)
	: Actor(filename, x, y, width, height, game) {

}

void Tile::update() {
	if (shootTime > 0) {
		shootTime=shootTime;
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