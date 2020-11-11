#pragma once
#include "Tile.h"

class Turret : public Tile
{
public:
	Turret(string filename, float x, float y, float vy, Game* game);
	void draw(float scrollY = 0) override; // Va a sobrescribir
	void update() override;
};

