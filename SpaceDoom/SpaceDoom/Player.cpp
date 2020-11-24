#include "Player.h"

Player::Player(float x, float y, Game* game)
	: Actor("res/soldier_idle.png", x, y, 160, 160, game) {

	state = game->stateMoving;
	audioShoot = new Audio("res/efecto_disparo.wav", false);

	aShooting = new Animation("res/soldier_shoot.png",
		width, height, 2400, 160, 0.25, 15, false, game);
	aIdle = new Animation("res/soldier_move_forward.png", width, height,
		2400, 160, 0.5, 15, true, game);
	aRunningRight = new Animation("res/soldier_move_right.png", width, height,
		2400, 160, 0.5, 15, true, game);
	aRunningLeft = new Animation("res/soldier_move_left.png", width, height,
		2400, 160, 0.5, 15, true, game);

	aShootingInvencible = new Animation("res/soldier_shoot_invencible.png",
		width, height, 2400, 160, 0.25, 15, false, game);
	aIdleInvencible = new Animation("res/soldier_move_forward_invencible.png", width, height,
		2400, 160, 0.5, 15, true, game);
	aRunningRightInvencible = new Animation("res/soldier_move_right_invencible.png", width, height,
		2400, 160, 0.5, 15, true, game);
	aRunningLeftInvencible = new Animation("res/soldier_move_left_invencible.png", width, height,
		2400, 160, 0.5, 15, true, game);

	animation = aIdle;
	this->collisionWidth = width - 80;
	this->collisionHeight = height - 80;
	vy = -2;
}


void Player::update() {
	if (invencibleTime > 0) {
		invencibleTime--;
	}

	if (hit > 0) {
		hit--;
	}

	// Selección de animación basada en estados
	if (state == game->stateShooting && invencibleTime <= 0) {
		animation = aShooting;
	}
	else if (state == game->stateShooting && invencibleTime > 0) {
		animation = aShootingInvencible;
	}
	if (state == game->stateMoving && invencibleTime <= 0) {
		if (vx != 0) {
			if (orientation == game->orientationRight) {
				animation = aRunningRight;
			}
			if (orientation == game->orientationLeft) {
				animation = aRunningLeft;
			}
		}
		if (vx == 0) {
			animation = aIdle;
		}
	}
	else if (state == game->stateMoving && invencibleTime > 0) {
		if (vx != 0) {
			if (orientation == game->orientationRight) {
				animation = aRunningRightInvencible;
			}
			if (orientation == game->orientationLeft) {
				animation = aRunningLeftInvencible;
			}
		}
		if (vx == 0) {
			animation = aIdleInvencible;
		}
	}

	bool endAnimation = animation->update();


	// Acabo la animación, no sabemos cual
	if (endAnimation) {
		// Estaba disparando
		if (state == game->stateShooting) {
			state = game->stateMoving;
		}
	}


	// Establecer orientación
	if (vx > 0) {
		orientation = game->orientationRight;
	}
	if (vx < 0) {
		orientation = game->orientationLeft;
	}



	if (shootTime > 0) {
		shootTime--;
	}

}

void Player::moveX(float axis) {
	vx = axis * 3;
}

Projectile* Player::shoot() {

	if (shootTime == 0 && bullets > 0) {
		state = game->stateShooting;
		audioShoot->play();
		if (invencibleTime > 0) {
			aShootingInvencible->currentFrame = 0; //"Rebobinar" animación
		}
		else {
			aShooting->currentFrame = 0; //"Rebobinar" animación
		}
		shootTime = shootCadence;
		Projectile* projectile = new Projectile(x, y, game);
		bullets--;
		return projectile;
	}
	else {
		return NULL;
	}
}

void Player::draw(float scrollX, float scrollY) {
	//animation->draw(x - scrollX, y - scrollY);
	if (hit == 0) {
		animation->draw(x - scrollX, y - scrollY);
	}
	else {
		if (hit % 10 >= 0 && hit % 10 <= 5) {
			animation->draw(x - scrollX, y - scrollY);
		}
	}
}

void Player::loseLife() {
	if (invencibleTime <= 0) {
		if (lifes > 0) {
			lifes--;
			hit = 150;
		}
	}
}
