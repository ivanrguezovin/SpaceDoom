#pragma once
#include "Tile.h"

class DestroyableTile : public Tile
{
public:
	DestroyableTile(string filename, float x, float y, float width, float height, Game* game);
	bool destroyByProjectile() override;
	void draw(float scrollX = 0, float scrollY = 0) override;
};

