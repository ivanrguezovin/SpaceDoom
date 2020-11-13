#pragma once
#include "Tile.h"

class DestroyableTile : public Tile
{
public:
	DestroyableTile(string filename, float x, float y, float vy, float width, float height, Game* game);
	void draw(float scrollY = 0) override; // Va a sobrescribir
	void update() override;
	bool destroyByProjectile() override;
};

