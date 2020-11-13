#pragma once
#include "Item.h"
class Coin : public Item
{
public:
	Coin(string filename, float x, float y, float width, float height, float vy, Game* game);
	void draw(float scrollY = 0) override;
	void update() override;
	int boosteo(int* points, int* shots, int* lifes, Text* textPoints, Text* textShots, Text* textLifes, int size) override;
};

