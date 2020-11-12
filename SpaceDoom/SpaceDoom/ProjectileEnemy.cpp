#include "ProjectileEnemy.h"

ProjectileEnemy::ProjectileEnemy(float x, float y, Game* game) :
	Actor("res/bullet.png", x, y, 61, 64, game) {
	this->vy = 5;
	aMoving = new Animation("res/bullet.png", width, height,
		61, 64, 1, 1, true, game);
	animation = aMoving;
}
void ProjectileEnemy::update() {
	animation->update();
}

void ProjectileEnemy::draw(float scrollY) {
	animation->draw(x, y + scrollY);
}