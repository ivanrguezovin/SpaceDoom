#pragma once
#include "Actor.h"
#include "ProjectileTurret.h"

class Tile : public Actor
{
public:
	Tile(string filename, float x, float y, Game* game);
	Tile(string filename, float x, float y, float vy, Game* game);
	virtual void draw(float scrollY = 0) override; // Va a sobrescribir
	virtual void update();
	Tile* tileAux = nullptr;
	virtual bool destroyByProjectile();
	virtual ProjectileTurret* shoot();
	int shootCadence = 50;
	int shootTime = 0;
};

