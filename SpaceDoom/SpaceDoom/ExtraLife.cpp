#include "ExtraLife.h"

ExtraLife::ExtraLife(string filename, float x, float y, float width, float height, Game* game)
	: Item(filename, x, y, width, height, game) {

	aMoving = new Animation(filename, width, height, 44, 36, 1, 1, true, game);
	animation = aMoving;
}

void ExtraLife::update() {
	animation->update();
}

void ExtraLife::draw(float scrollX, float scrollY) {
	animation->draw(x - scrollX, y - scrollY);
}

int ExtraLife::boosteo(int* points, int* shots, int* lifes, Text * textPoints, Text * textShots, Text * textLifes, int size) {
	*lifes = *lifes + 1;
	textLifes->content = to_string(*lifes);
	return 1;
}
