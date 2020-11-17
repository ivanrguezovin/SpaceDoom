#include "Nuclear.h"

Nuclear::Nuclear(string filename, float x, float y, float width, float height, float vy, Game* game)
	: Item(filename, x, y, width, height, vy, game) {

	this->vy = vy;
	aMoving = new Animation(filename, width, height, 40, 42, 1, 1, true, game);
	animation = aMoving;
}

void Nuclear::update() {
	if (vy != 0) {
		y = y + vy;
	}
	animation->update();
}

void Nuclear::draw(float scrollX, float scrollY) {
	animation->draw(x - scrollX, y - scrollY);
}

int Nuclear::boosteo(int* points, int* shots, int* lifes, Text * textPoints, Text * textShots, Text * textLifes, int size) {
	*points = *points + size;
	textPoints->content = to_string(*points);
	return 3;
}
