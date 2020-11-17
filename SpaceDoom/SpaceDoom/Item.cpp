#include "Item.h"

Item::Item(string filename, float x, float y, float width, float height, float vy, Game* game)
	: Actor(filename, x, y, width, height, game) {

	this->vy = vy;
	aMoving = new Animation(filename, width, height, 108, 40, 6, 1, true, game);
	animation = aMoving;
}

void Item::update() {
	animation->update();
}

void Item::draw(float scrollX, float scrollY) {
	animation->draw(x - scrollX, y - scrollY);
}

int Item::boosteo(int* points, int* shots, int* lifes, Text* textPoints, Text* textShots, Text* textLifes, int size) {
	return 5;
}
