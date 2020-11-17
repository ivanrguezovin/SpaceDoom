#pragma once
#include "Tile.h"

class CommonTile : public Tile
{
public:
	CommonTile(string filename, float x, float y, float vy, float width, float height, Game* game);
	void draw(float scrollX = 0, float scrollY = 0) override; // Va a sobrescribir
	void update() override;
};

