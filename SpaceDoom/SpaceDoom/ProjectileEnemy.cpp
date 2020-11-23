#include "ProjectileEnemy.h"

ProjectileEnemy::ProjectileEnemy(float x, float y, Game* game) :
	Actor("res/asteroide.png", x, y, 40, 41, game) {
	this->vy = 5;
	aMoving = new Animation("res/asteroide.png", width, height,
		40, 41, 1, 1, true, game);
	animation = aMoving;
}
void ProjectileEnemy::update() {
	animation->update();
}

void ProjectileEnemy::draw(float scrollX, float scrollY) {
	animation->draw(x - scrollX, y - scrollY);
}