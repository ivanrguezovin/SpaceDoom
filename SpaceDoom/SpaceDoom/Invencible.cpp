#include "Invencible.h"

Invencible::Invencible(string filename, float x, float y, float width, float height, float vy, Game* game)
	: Item(filename, x, y, width, height, vy, game) {

	this->vy = vy;
	aMoving = new Animation(filename, width, height, 24, 24, 1, 1, true, game);
	animation = aMoving;
}

void Invencible::update() {
	if (vy != 0) {
		y = y + vy;
	}
	animation->update();
}

void Invencible::draw(float scrollX, float scrollY) {
	animation->draw(x - scrollX, y - scrollY);
}

int Invencible::boosteo(int* points, int* shots, int* lifes, Text * textPoints, Text * textShots, Text * textLifes, int size) {
	return 4;
}
