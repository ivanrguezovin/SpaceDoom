#include "ProjectileTurret.h"

ProjectileTurret::ProjectileTurret(float x, float y, Game* game) :
	Actor("res/bullet.png", x, y, 23, 23, game) {
	this->vy = -0.000000000000000000000005;
	aMoving = new Animation("res/bullet.png", width, height,
		23, 23, 1, 1, true, game);
	animation = aMoving;
}

void ProjectileTurret::update() {
	animation->update();
}

void ProjectileTurret::draw(float scrollX, float scrollY) {
	animation->draw(x - scrollX, y - scrollY);
}