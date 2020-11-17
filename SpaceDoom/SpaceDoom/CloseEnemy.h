#pragma once
#include "Enemy.h"

class CloseEnemy : public Enemy
{
public:
	CloseEnemy(string filename, float x, float y, Game* game);
	void draw(float scrollX = 0, float scrollY = 0) override; // Va a sobrescribir
	void update() override;
	void impacted() override; // Recibe impacto y pone animación de morir
};

