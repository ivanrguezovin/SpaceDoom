#include "DestroyableTile.h"

DestroyableTile::DestroyableTile(string filename, float x, float y, float width, float height, Game* game)
	: Tile(filename, x, y, width, height, game) {
	
}


bool DestroyableTile::destroyByProjectile() {
	return true;
}