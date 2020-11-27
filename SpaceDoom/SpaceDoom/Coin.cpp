#include "Coin.h"

Coin::Coin(string filename, float x, float y, float width, float height, Game* game)
	: Item(filename, x, y, width, height, game) {
	audioItem = new Audio("res/coin.wav", false);
	aMoving = new Animation(filename, width, height, 40, 42, 1, 1, true, game);
	animation = aMoving;
}

void Coin::update() {
	animation->update();
}

void Coin::draw(float scrollX, float scrollY) {
	animation->draw(x - scrollX, y - scrollY);
}

int Coin::boosteo(int* points, int* shots, int* lifes, Text * textPoints, Text * textShots, Text * textLifes, int size) {
	*points = *points + 5;
	textPoints->content = to_string(*points);
	audioItem->play();
	return 0;
}