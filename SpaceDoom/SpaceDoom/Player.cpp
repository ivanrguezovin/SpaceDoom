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

	animation = aIdle;
	this->collisionWidth = width - 60;
	this->collisionHeight = height - 60;
	vy = -2;
}


void Player::update() {
	if (invencibleTime > 0) {
		invencibleTime--;
	}

	if (hit > 0) {
		hit--;
	}

	bool endAnimation = animation->update();


	// Acabo la animaci�n, no sabemos cual
	if (endAnimation) {
		// Estaba disparando
		if (state == game->stateShooting) {
			state = game->stateMoving;
		}
	}


	// Establecer orientaci�n
	if (vx > 0) {
		orientation = game->orientationRight;
	}
	if (vx < 0) {
		orientation = game->orientationLeft;
	}


	// Selecci�n de animaci�n basada en estados
	if (state == game->stateShooting) {
		animation = aShooting;
	}
	if (state == game->stateMoving) {
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
		aShooting->currentFrame = 0; //"Rebobinar" aniamci�n
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
	/*
	if (invencibleTime == 0) {
		animation->draw(x - scrollX, y - scrollY);
	}
	else {
		if (invencibleTime % 10 >= 0 && invencibleTime % 10 <= 5) {
			animation->draw(x - scrollX, y - scrollY);
		}
	*/
	animation->draw(x - scrollX, y - scrollY);
}

void Player::loseLife() {
	if (invencibleTime <= 0) {
		if (lifes > 0) {
			lifes--;
			hit = 150;
		}
	}
}
