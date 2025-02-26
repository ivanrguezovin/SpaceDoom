#pragma once

#include "Actor.h"
#include "Projectile.h" 
#include "Audio.h"
#include "Animation.h" // incluir animacion 

class Player : public Actor
{
public:
	Player(float x, float y, Game* game);
	Projectile* shoot();
	void update();
	void moveX(float axis);
	void draw(float scrollX = 0, float scrollY = 0) override; // Va a sobrescribir
	void loseLife();
	int lifes = 3;
	int orientation;
	int state;
	Animation* aIdle;
	Animation* aRunningRight;
	Animation* aRunningLeft;
	Animation* aShooting;
	Animation* aIdleInvencible;
	Animation* aRunningRightInvencible;
	Animation* aRunningLeftInvencible;
	Animation* aShootingInvencible;
	Animation* animation; // Referencia a la animacion mostrada
	int shootCadence = 30;
	int shootTime = 0;
	int bullets = 8;
	int invencibleTime = 0;
	int hit = 0;
	void erase();
};

