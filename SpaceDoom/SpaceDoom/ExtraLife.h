#pragma once
#include "Item.h"

class ExtraLife : public Item
{
public:
	ExtraLife(string filename, float x, float y, float width, float height, Game* game);
	void draw(float scrollX = 0, float scrollY = 0) override;
	void update() override;
	int boosteo(int* points, int* shots, int* lifes, Text* textPoints, Text* textShots, Text* textLifes, int size) override;
};

