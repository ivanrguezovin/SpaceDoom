#include "Projectile.h"

Projectile::Projectile(float x, float y, Game* game) :
	Actor("res/bullet.png", x, y, 61, 64, game) {
	vy = -9;
	aMoving = new Animation("res/bullet.png", width, height,
		61, 64, 1, 1, true, game);
	animation = aMoving;
}

void Projectile::update() {
	animation->update();
}

void Projectile::draw(float scrollX, float scrollY) {
	animation->draw(x - scrollX, y + scrollY);
}
