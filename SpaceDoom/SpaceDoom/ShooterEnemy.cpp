#include "ShooterEnemy.h"

ShooterEnemy::ShooterEnemy(string filename, float x, float y, Game* game)
	: Enemy(filename, x, y, game) {

	state = game->stateMoving;

	aDying = new Animation("res/closeEnemy_die.png", width, height,
		835, 65, 1, 13, false, game);

	aMoving = new Animation("res/closeEnemy_move.png", width, height,
		768, 128, 1, 6, true, game);

	vy = 0;
	vyIntelligence = 1;
	vy = vyIntelligence;

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

void ShooterEnemy::impacted() {
	if (state != game->stateDying) {
		state = game->stateDying;
	}
}


void ShooterEnemy::draw(float scrollY) {
	animation->draw(x, y - scrollY);
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