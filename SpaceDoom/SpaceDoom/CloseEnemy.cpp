#include "CloseEnemy.h"

CloseEnemy::CloseEnemy(string filename, float x, float y, Game* game)
	: Enemy(filename, x, y, game) {

	state = game->stateMoving;

	aDying = new Animation("res/closeEnemy_die.png", width, height,
		835, 65, 1, 13, false, game);

	aMoving = new Animation("res/closeEnemy_move.png", width, height,
		768, 128, 1, 6, true, game);

	aHiting = new Animation("res/closeEnemy_hit.png", width, height,
		512, 128, 4, 4, false, game);
	animation = aMoving;

	vy = 0;
	vyIntelligence = 1;
	vy = vyIntelligence;

}

void CloseEnemy::update() {
	// Actualizar la animación
	bool endAnimation = animation->update();

	// Acabo la animación, no sabemos cual
	if (endAnimation) {
		// Estaba muriendo
		if (state == game->stateDying) {
			state = game->stateDead;
		}
		if (state == game->stateHiting) {
			state = game->stateMoving;
			animation = aMoving;
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

void CloseEnemy::impacted() {
	if (state != game->stateDying) {
		state = game->stateDying;
	}
}


void CloseEnemy::draw(float scrollY) {
	animation->draw(x, y - scrollY);
}