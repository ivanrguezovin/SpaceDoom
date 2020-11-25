#include "Turret.h"

Turret::Turret(string filename, float x, float y, float width, float height, Game* game)
	: Tile(filename, x, y, width, height, game) {
	animation = new Animation(filename, width, height,
		x, y, 1, 1, true, game);
}

void Turret::update() {
	if (shootTime > 0) {
		shootTime--;
	}
}

ProjectileTurret* Turret::shoot() {
	if (shootTime == 0) {
		shootTime = shootCadence;
		ProjectileTurret* projectile = new ProjectileTurret(x, y, game);
		return projectile;
	}
	else {
		return NULL;
	}
}

bool Turret::isTurret() {
	return true;
}

void Turret::draw(float scrollX, float scrollY) {
	animation->draw(x - scrollX, y - scrollY);
}