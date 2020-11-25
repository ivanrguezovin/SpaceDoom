#pragma once
#include "Actor.h"
#include "ProjectileTurret.h"

class Tile : public Actor
{
public:
	Tile(string filename, float x, float y, float width, float height, Game* game);
	virtual void update();
	virtual bool destroyByProjectile();
	virtual ProjectileTurret* shoot();
	int shootCadence = 50;
	int shootTime = 0;
	virtual bool isTurret();
	virtual void draw(float scrollX = 0, float scrollY = 0) override;
	Animation* animation;
};

