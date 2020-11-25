#include "CommonTile.h"

CommonTile::CommonTile(string filename, float x, float y, float width, float height, Game* game)
	: Tile(filename, x, y, width, height, game) {
	animation = new Animation(filename, width, height,
		x, y, 1, 1, true, game);
}

void CommonTile::draw(float scrollX, float scrollY) {
	animation->draw(x - scrollX, y - scrollY);
}