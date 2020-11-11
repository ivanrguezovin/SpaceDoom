#pragma once

#include "Actor.h"
#include "Animation.h" // incluir animacion 


class Projectile : public Actor
{
public:
	Projectile(float x, float y, Game* game);
	void update();
	Animation* aMoving;
	Animation* animation;
	void draw(float scrollY = 0) override;
};

