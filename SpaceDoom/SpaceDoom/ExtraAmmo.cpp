#include "ExtraAmmo.h"

ExtraAmmo::ExtraAmmo(string filename, float x, float y, float width, float height, Game* game)
	: Item(filename, x, y, width, height, game) {
	audioItem = new Audio("res/ammo.wav", false);
	aMoving = new Animation(filename, width, height, 40, 40, 1, 1, true, game);
	animation = aMoving;
}

void ExtraAmmo::update() {
	animation->update();
}

void ExtraAmmo::draw(float scrollX, float scrollY) {
	animation->draw(x - scrollX, y - scrollY);
}

int ExtraAmmo::boosteo(int* points, int* shots, int* lifes, Text * textPoints, Text * textShots, Text * textLifes, int size) {
	*shots = *shots + 5;
	textShots->content = to_string(*shots);
	audioItem->play();
	return 2;
}
