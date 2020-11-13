#include "Turret.h"

Turret::Turret(string filename, float x, float y, float vy, float width, float height, Game* game)
	: Tile(filename, x, y, vy, width, height, game) {
	this->vy = vy;
	if (vy != 0) {
		tileAux = new Tile(filename, x, y + HEIGHT, width, height, game);
	}
}

void Turret::update() {
	if (vy != 0) {
		y = y + vy;
	}
	if (shootTime > 0) {
		shootTime--;
	}
}

void Turret::draw(float scrollY) {
	Actor::draw(); // llamar al metodo del hijo

	if (tileAux != NULL) {
		tileAux->draw();
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