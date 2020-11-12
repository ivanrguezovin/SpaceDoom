#pragma once
#include "Enemy.h"

class ShooterEnemy : public Enemy
{
public:
	ShooterEnemy(string filename, float x, float y, Game* game);
	void draw(float scrollY = 0) override; // Va a sobrescribir
	void update() override;
	void impacted() override; // Recibe impacto y pone animación de morir
	ProjectileEnemy* shoot() override;
};

