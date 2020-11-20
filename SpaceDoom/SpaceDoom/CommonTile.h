#pragma once
#include "Tile.h"

class CommonTile : public Tile
{
public:
	CommonTile(string filename, float x, float y, float width, float height, Game* game);
};

