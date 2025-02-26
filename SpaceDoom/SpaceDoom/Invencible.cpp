#include "Invencible.h"

Invencible::Invencible(string filename, float x, float y, float width, float height, Game* game)
	: Item(filename, x, y, width, height, game) {
	aMoving = new Animation(filename, width, height, 24, 24, 1, 1, true, game);
	animation = aMoving;
}

void Invencible::update() {
	animation->update();
}

void Invencible::draw(float scrollX, float scrollY) {
	animation->draw(x - scrollX, y - scrollY);
}

int Invencible::boosteo(int* points, int* shots, int* lifes, Text * textPoints, Text * textShots, Text * textLifes, int size) {
	return 4;
}
