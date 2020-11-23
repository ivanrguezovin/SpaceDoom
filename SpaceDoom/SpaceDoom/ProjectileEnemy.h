#pragma once
#include "Actor.h"
#include "Animation.h" // incluir animacion 


class ProjectileEnemy : public Actor
{
public:
	ProjectileEnemy(float x, float y, Game* game);
	void update();
	Animation* aMoving;
	Animation* animation;
	void draw(float scrollX = 0, float scrollY = 0) override;
	void calculateSpeed(int level);
};

