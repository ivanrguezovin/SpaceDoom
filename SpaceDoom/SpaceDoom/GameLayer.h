#pragma once

#include "Layer.h"
#include "Player.h"
#include "Background.h"
#include "Pad.h"
#include "Space.h"

#include "Enemy.h"
#include "CloseEnemy.h"
#include "ShooterEnemy.h"

#include "Item.h"
#include "ExtraLife.h"
#include "ExtraAmmo.h"
/*
#include "Invencible.h"
#include "Nuclear.h"
*/

#include "Projectile.h"
#include "ProjectileTurret.h"
#include "ProjectileEnemy.h"

#include "Audio.h"
#include "Text.h"

#include "Tile.h"
#include "Turret.h"
#include "CommonTile.h"
#include "DestroyableTile.h"

#include <fstream> // Leer ficheros
#include <sstream> // Leer líneas / String
#include <list>

class GameLayer : public Layer
{
public:
	GameLayer(Game* game);
	void init() override;
	void processControls() override;
	void update() override;
	void draw() override;
	void keysToControls(SDL_Event event);
	void mouseToControls(SDL_Event event); // USO DE MOUSE
	void gamePadToControls(SDL_Event event); // USO DE GAMEPAD
	void loadMap(string name);
	void loadMapObject(char character, float x, float y);
	void calculateScroll();
	Actor* message;
	bool pause;
	// Elementos de interfaz
	SDL_GameController* gamePad;
	Pad* pad;
	Actor* buttonShoot;

	Space* space;
	float scrollY;
	float scrollX;
	int mapWidth;
	list<Tile*> tiles;
	list<Tile*> goals;
	list<Item*> items;
	Audio* audioBoost;
	Audio* audioBackground;
	Text* textPoints;
	Text* textBullets;
	Text* textLifes;
	int points;
	Player* player;
	Background* background;
	Actor* backgroundPoints;
	Actor* backgroundBullets;
	Actor* backgroundLifes;
	list<Enemy*> enemies;
	list<Projectile*> projectiles;
	list<ProjectileEnemy*> projectilesEnemy;
	list<ProjectileTurret*> projectilesTurret;

	bool controlContinue = false;
	bool controlShoot = false;
	int controlMoveY = 0;
	int controlMoveX = 0;


};

