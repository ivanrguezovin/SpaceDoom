#include "ProjectileEnemy.h"

ProjectileEnemy::ProjectileEnemy(float x, float y, Game* game) :
	Actor("res/asteroide.png", x, y, 40, 41, game) {
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

void ProjectileEnemy::calculateSpeed(int level) {
	if (level == 0) {
		//Eje Y
		vy = 5;
	}
	else {
		//Eje Y
		vy = level + 5;
	}
}

void ProjectileEnemy::erase() {
	delete aMoving;
}