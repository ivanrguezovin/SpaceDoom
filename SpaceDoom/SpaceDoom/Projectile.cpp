#include "Projectile.h"

Projectile::Projectile(float x, float y, Game* game) :
	Actor("res/bullet.png", x, y, 23, 23, game) {
	vy = -9;
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
