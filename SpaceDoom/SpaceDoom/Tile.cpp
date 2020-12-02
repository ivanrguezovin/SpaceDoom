#include "Tile.h"

Tile::Tile(string filename, float x, float y, float width, float height, Game* game)
	: Actor(filename, x, y, width, height, game) {
	animation = new Animation(filename, width, height,
		x, y, 1, 1, true, game);
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

void Tile::draw(float scrollX, float scrollY) {
	animation->draw(x - scrollX, y - scrollY);
}

void Tile :: erase() {
	delete animation;
}