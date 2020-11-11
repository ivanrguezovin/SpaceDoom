#pragma once
#include "Actor.h"
#include "Animation.h" // incluir animacion 


class ProjectileTurret : public Actor
{
public:
	ProjectileTurret(float x, float y, Game* game);
	void update();
	Animation* aMoving;
	Animation* animation;
	void draw(float scrollY = 0) override;
};

