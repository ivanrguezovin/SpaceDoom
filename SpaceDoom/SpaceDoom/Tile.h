#pragma once
#include "Actor.h"

class Tile : public Actor
{
public:
	Tile(string filename, float x, float y, Game* game);
	Tile(string filename, float x, float y, float vy, Game* game);
	void draw(float scrollY = 0) override; // Va a sobrescribir
	virtual void update();
	Tile* tileAux = nullptr;
	virtual bool destroyByProjectile();
};

