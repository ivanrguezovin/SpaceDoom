#include "Coin.h"

Coin::Coin(string filename, float x, float y, float width, float height, float vy, Game* game)
	: Item(filename, x, y, width, height, vy, game) {

	this->vy = vy;
	aMoving = new Animation(filename, width, height, 40, 42, 1, 1, true, game);
	animation = aMoving;
}

void Coin::update() {
	if (vy != 0) {
		y = y + vy;
	}
	animation->update();
}

void Coin::draw(float scrollX, float scrollY) {
	animation->draw(x - scrollX, y - scrollY);
}

int Coin::boosteo(int* points, int* shots, int* lifes, Text * textPoints, Text * textShots, Text * textLifes, int size) {
	*points = *points + 5;
	textPoints->content = to_string(*points);
	return 0;
}