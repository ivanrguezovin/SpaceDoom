#include "Enemy.h"

Enemy::Enemy(float x, float y, Game* game)
	: Actor("res/closeEnemy.png", x, y, 121, 121, game) {

	state = game->stateMoving;

	aDying = new Animation("res/closeEnemy_hit.png", width, height,
		2400, 160, 1, 15, false, game);

	aMoving = new Animation("res/closeEnemy_move.png", width, height,
		2400, 160, 1, 15, true, game);
	animation = aMoving;

	vy = 0;
	vyIntelligence = 1;
	vy = vyIntelligence;

}

void Enemy::update() {
	// Actualizar la animación
	bool endAnimation = animation->update();

	// Acabo la animación, no sabemos cual
	if (endAnimation) {
		// Estaba muriendo
		if (state == game->stateDying) {
			state = game->stateDead;
		}
	}


	if (state == game->stateMoving) {
		animation = aMoving;
	}
	if (state == game->stateDying) {
		animation = aDying;
	}

	// Establecer velocidad
	if (state != game->stateDying) {
		// no está muerto y se ha quedado parado
		if (vy == 0) {
			vyIntelligence = vyIntelligence * 1;
			vy = vyIntelligence;
		}

	}
	else {
		vy = 0;
	}



}

void Enemy::impacted() {
	if (state != game->stateDying) {
		state = game->stateDying;
	}
}


void Enemy::draw(float scrollY) {
	animation->draw(x, y - scrollY);
}
