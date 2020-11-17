#include "Enemy.h"

Enemy::Enemy(string filename, float x, float y, Game* game)
	: Actor(filename, x, y, 100, 100, game) {

	state = game->stateMoving;

	aDying = new Animation("res/closeEnemy_die.png", width, height,
		835, 65, 1, 13, false, game);

	aMoving = new Animation("res/closeEnemy_move.png", width, height,
		1024, 128, 1, 8, true, game);

	aHiting = new Animation("res/closeEnemy_hit.png", width, height,
		512, 128, 1, 4, false, game);
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
		if (state == game->stateHiting) {
			state == game->stateMoving;
		}
	}


	if (state == game->stateMoving) {
		animation = aMoving;
	}
	if (state == game->stateDying) {
		animation = aDying;
	}
	if (state == game->stateHiting) {
		animation = aHiting;
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


void Enemy::draw(float scrollX, float scrollY) {
	animation->draw(x - scrollX, y - scrollY);
}

ProjectileEnemy* Enemy::shoot() {
	return NULL;
}