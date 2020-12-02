#include "Projectile.h"

Projectile::Projectile(float x, float y, Game* game) :
	Actor("res/bullet.png", x, y, 23, 23, game) {
	aMoving = new Animation("res/bullet.png", width, height,
		23, 23, 1, 1, true, game);
	animation = aMoving;
}

void Projectile::update() {
	animation->update();
}

void Projectile::draw(float scrollX, float scrollY) {
	animation->draw(x - scrollX, y - scrollY);
}

void Projectile::calculateSpeed(int level) {
	if (level == 0) {
		//Eje Y
		vy = -9;
	}
	else {
		//Eje Y
		vy = (level * -1) - 9;
	}
}

void Projectile::erase() {
	delete aMoving;
}