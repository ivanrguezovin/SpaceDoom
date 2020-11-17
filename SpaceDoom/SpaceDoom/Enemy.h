#pragma once

#include "Actor.h"
#include "Animation.h" 
#include "ProjectileEnemy.h" 

class Enemy : public Actor
{
public:
	Enemy(string filename, float x, float y, Game* game);
	virtual void draw(float scrollX = 0, float scrollY = 0) override; // Va a sobrescribir
	virtual void update();
	virtual void impacted(); // Recibe impacto y pone animación de morir
	float vyIntelligence;
	int state;
	Animation* aDying;
	Animation* aMoving;
	Animation* aHiting;
	Animation* animation; // Referencia a la animación mostrada
	virtual ProjectileEnemy* shoot();
	int shootCadence = 100;
	int shootTime = 0;
};

