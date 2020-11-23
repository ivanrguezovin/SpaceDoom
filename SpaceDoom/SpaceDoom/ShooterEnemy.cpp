#include "ShooterEnemy.h"

ShooterEnemy::ShooterEnemy(string filename, float x, float y, Game* game)
	: Enemy(filename, x, y, game) {

	state = game->stateMoving;

	aDying = new Animation("res/closeEnemy_die.png", width, height,
		835, 65, 1, 13, false, game);

	aMoving = new Animation("res/slime1_front.png", width, height,
		64, 16, 1, 4, true, game);

}

void ShooterEnemy::update() {
	if (shootTime > 0) {
		shootTime--;
	}
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

}

void ShooterEnemy::impacted() {
	if (state != game->stateDying) {
		state = game->stateDying;
	}
}


void ShooterEnemy::draw(float scrollX, float scrollY) {
	animation->draw(x - scrollX, y - scrollY);
}

ProjectileEnemy* ShooterEnemy::shoot() {
	if (shootTime == 0) {
		shootTime = shootCadence;
		ProjectileEnemy* projectile = new ProjectileEnemy(x, y, game);
		return projectile;
	}
	else {
		return NULL;
	}
}