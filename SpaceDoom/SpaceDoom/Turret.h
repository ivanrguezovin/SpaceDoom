#pragma once
#include "Tile.h"
#include "ProjectileTurret.h"

class Turret : public Tile
{
public:
	Turret(string filename, float x, float y, float width, float height, Game* game);
	void update() override;
	ProjectileTurret* shoot() override;
	bool isTurret() override;
};