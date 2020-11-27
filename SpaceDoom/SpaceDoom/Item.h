#pragma once
#include "Actor.h"
#include "Text.h"
#include "Animation.h"
#include "Audio.h"

class Item : public Actor
{
public:
	Item(string filename, float x, float y, float width, float height, Game* game);
	virtual void draw(float scrollX = 0, float scrollY = 0) override; // Va a sobrescribir
	virtual void update();
	virtual int boosteo(int* points, int* shots, int* lifes, Text* textPoints, Text* textShots, Text* textLifes, int size);
	Animation* aMoving;
	Animation* animation;
	Audio* audioItem;
};

