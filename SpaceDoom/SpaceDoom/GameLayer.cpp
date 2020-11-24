#include "GameLayer.h"

GameLayer::GameLayer(Game* game)
	: Layer(game) {
	//llama al constructor del padre : Layer(renderer)
	pause = true;
	message = new Actor("res/mensaje_como_jugar.png", WIDTH * 0.5, HEIGHT * 0.5,
		WIDTH, HEIGHT, game);

	gamePad = SDL_GameControllerOpen(0);
	init();
}


void GameLayer::init() {
	buttonLeft = new Actor("res/boton_izqda.png", WIDTH * 0.1, HEIGHT * 0.85, 100, 100, game);
	buttonRight = new Actor("res/boton_dcha.png", WIDTH * 0.35, HEIGHT * 0.85, 100, 100, game);
	buttonShoot = new Actor("res/boton_disparo.png", WIDTH * 0.90, HEIGHT * 0.85, 100, 100, game);
	buttonPause = new Actor("res/boton_pausa.png", WIDTH * 0.08, HEIGHT * 0.05, 40, 40, game);

	space = new Space(1);
	scrollY = 0;
	scrollX = 0;
	tiles.clear();

	audioBackground = new Audio("res/musica_ambiente.mp3", true);
	//audioBackground->play();
	textFinalPoints = new Text("Last Score: ", WIDTH * 0.5, HEIGHT * 0.94, game);
	textFinalPoints->content = "Last Score: " + to_string(pf); pf = 0;
	pointsPreLevel = points;
	
	textPoints = new Text("Puntos", WIDTH * 0.92, HEIGHT * 0.04, game);
	textPoints->content = to_string(points);
	textLifes = new Text("Vidas", WIDTH * 0.15, HEIGHT * 0.94, game);
	textBullets = new Text("Balas", WIDTH * 0.79, HEIGHT * 0.04, game);

	background = new Background("res/fondo_2.png", WIDTH * 0.5, HEIGHT * 0.5, -1, game);
	backgroundPoints = new Actor("res/icono_recolectable.png",
		WIDTH * 0.85, HEIGHT * 0.04, 23, 23, game);
	backgroundBullets = new Actor("res/bullet.png",
		WIDTH * 0.73, HEIGHT * 0.04, 23, 23, game);
	backgroundLifes = new Actor("res/corazon.png",
		WIDTH * 0.08, HEIGHT * 0.95, 44, 36, game);

	enemies.clear(); // Vaciar por si reiniciamos el juego
	projectiles.clear(); // Vaciar por si reiniciamos el juego
	projectilesEnemy.clear(); // Vaciar por si reiniciamos el juego
	projectilesTurret.clear(); // Vaciar por si reiniciamos el juego
	goals.clear();
	items.clear();

	loadMap("res/" + to_string(game->currentLevel) + ".txt");
}

void GameLayer::loadMap(string name) {
	char character;
	string line;
	ifstream streamFile(name.c_str());
	if (!streamFile.is_open()) {
		cout << "Falla abrir el fichero de mapa" << endl;
		return;
	}
	else {
		// Por línea
		for (int i = 0; getline(streamFile, line); i++) {
			istringstream streamLine(line);
			mapWidth = line.length() * 40; // Ancho del mapa en pixels
			mapHeight = (i + 1) * 40; // Altura del mapa en pixels
			// Por carácter (en cada línea)
			for (int j = 0; !streamLine.eof(); j++) {
				streamLine >> character; // Leer character 
				//cout << character;
				float x = 40 / 2 + j * 40; // x central
				float y = 32 + i * 32; // y suelo
				loadMapObject(character, x, y);
			}

			//cout << character << endl;
		}
	}
	streamFile.close();
}

void GameLayer::loadMapObject(char character, float x, float y)
{
	switch (character) {
	case 'C': {
		Tile* cup = new Tile("res/meta.png", x, y, 40, 40, game);
		cup->y = cup->y - cup->height / 2;
		goals.push_back(cup);
		space->addDynamicActor(cup);
		break;
	}
	case 'E': {
		CloseEnemy* enemy = new CloseEnemy("res/closeEnemy.png",x, y, game);
		enemy->y = enemy->y - enemy->height / 2;
		enemies.push_back(enemy);
		space->addDynamicActor(enemy);
		break;
	}
	case 'S': {
		ShooterEnemy* enemy = new ShooterEnemy("res/closeEnemy.png", x, y, game);
		enemy->y = enemy->y - enemy->height / 2;
		enemies.push_back(enemy);
		space->addDynamicActor(enemy);
		break;
	}
	case '1': {
		player = new Player(x, y, game);
		player->y = player->y - player->height / 2;
		space->addDynamicActor(player);
		textBullets->content = to_string(player->bullets);
		textLifes->content = to_string(player->lifes);
		break;
	}
	case '#': {
		CommonTile* tile = new CommonTile("res/tile.png", x, y, 40, 40, game);
		tile->y = tile->y - tile->height / 2;
		tiles.push_back(tile);
		space->addStaticActor(tile);
		break;
	}
	case 'D': {
		DestroyableTile* tile = new DestroyableTile("res/destroyTile.png", x, y, 40, 40, game);
		tile->y = tile->y - tile->height / 2;
		tiles.push_back(tile);
		space->addStaticActor(tile);
		break;
	}
	case 'T': {
		Turret* tile = new Turret("res/turret.png", x, y, 85, 85, game);
		tile->y = tile->y - tile->height / 2;
		tiles.push_back(tile);
		space->addStaticActor(tile);
		break;
	}
	case 'A': {
		ExtraAmmo* item = new ExtraAmmo("res/extraAmmo.png", x, y, 40, 40, game);
		item->y = item->y - item->height / 2;
		items.push_back(item);
		space->addDynamicActor(item);
		break;
	}
	case 'L': {
		ExtraLife* item = new ExtraLife("res/corazon.png", x, y, 44, 36, game);
		item->y = item->y - item->height / 2;
		items.push_back(item);
		space->addDynamicActor(item);
		break;
	}
	case 'N': {
		Nuclear* item = new Nuclear("res/bomb.png", x, y, 40, 42, game);
		item->y = item->y - item->height / 2;
		items.push_back(item);
		space->addDynamicActor(item);
		break;
	}case 'I': {
		Invencible* item = new Invencible("res/icono_puntos.png", x, y, 40, 40, game);
		item->y = item->y - item->height / 2;
		items.push_back(item);
		space->addDynamicActor(item);
		break;
	}case 'M': {
		Coin* item = new Coin("res/moneda.png", x, y, 40, 40, game);
		item->y = item->y - item->height / 2;
		items.push_back(item);
		space->addDynamicActor(item);
		break;
	}
	}
}


void GameLayer::processControls() {
	// obtener controles
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_CONTROLLERDEVICEADDED) {
			gamePad = SDL_GameControllerOpen(0);
			if (gamePad == NULL) {
				cout << "error en GamePad" << endl;
			}
			else {
				cout << "GamePad conectado" << endl;
			}
		}

		// Cambio automático de input
		// PONER el GamePad
		if (event.type == SDL_CONTROLLERBUTTONDOWN || event.type == SDL_CONTROLLERAXISMOTION) {
			game->input = game->inputGamePad;
		}
		if (event.type == SDL_KEYDOWN) {
			game->input = game->inputKeyboard;
		}
		if (event.type == SDL_MOUSEBUTTONDOWN) {
			game->input = game->inputMouse;
		}
		// Procesar teclas
		if (game->input == game->inputKeyboard) {
			keysToControls(event);
		}
		if (game->input == game->inputMouse) {
			mouseToControls(event);
		}
		// Procesar Mando
		if (game->input == game->inputGamePad) {  // gamePAD
			gamePadToControls(event);
		}


	}
	
	// Disparar
	if (controlContinue) {
		pause = false;
		controlContinue = false;
	}
	if (controlShoot) {
		Projectile* newProjectile = player->shoot();
		if (newProjectile != NULL) {
			textBullets->content = to_string(player->bullets);
			space->addDynamicActor(newProjectile);
			projectiles.push_back(newProjectile);
		}

	}

	calculateSpeed(game->currentLevel);
}

void GameLayer::calculateSpeed(int level) {
	if (level == 0) {
		// Eje X
		if (controlMoveX > 0) {
			player->moveX(1);
		}
		else if (controlMoveX < 0) {
			player->moveX(-1);
		}
		else {
			player->moveX(0);
		}
		//Eje Y
		player->vy = -2;
	}
	else {
		// Eje X
		if (controlMoveX > 0) {
			player->moveX(level + 1);
		}
		else if (controlMoveX < 0) {
			player->moveX((level * -1) - 1);
		}
		else {
			player->moveX(0);
		}
		//Eje Y
		player->vy = (level*-1)-2;
	}
}

void GameLayer::update() {
	if (pause) {
		return;
	}

	if (player->invencibleTime > 0) {
		backgroundLifes = backgroundLifes = new Actor("res/corazonInvencible.png",
			WIDTH * 0.08, HEIGHT * 0.95, 44, 36, game);
	}
	else {
		backgroundLifes = new Actor("res/corazon.png",
			WIDTH * 0.08, HEIGHT * 0.95, 44, 36, game);
	}

	// Nivel superado
	for (auto const& goal : goals) {
		if (goal->isOverlap(player)) {
			game->currentLevel++;
			if (game->currentLevel > game->finalLevel) {
				pf = points + player->bullets + player->lifes;
				game->currentLevel = 0;
				points = 0;
				message = new Actor("res/mensaje_juego_completado.png", WIDTH * 0.5, HEIGHT * 0.5, 480, 320, game);
				pause = true;
				init();
				break;
			}
			message = new Actor("res/mensaje_ganar.png", WIDTH * 0.5, HEIGHT * 0.5, WIDTH, HEIGHT, game);
			pause = true;
			init();
			break;
		}
	}
	

	// Jugador se sale de los límites de la pantalla
	if (player->x > WIDTH + 20) {
		player->x = 0;
	}
	else if (player->x < -20) {
		player->x = WIDTH;
	}

	space->update();
	background->update();
	player->update();
	for (auto const& enemy : enemies) {
		enemy->update();
		ProjectileEnemy* penemigo = enemy->shoot();
		if (penemigo != NULL) {
			space->addDynamicActor(penemigo);
			projectilesEnemy.push_back(penemigo);
		}
	}
	for (auto const& projectile : projectiles) {
		projectile->calculateSpeed(game->currentLevel);
		projectile->update();
	}
	for (auto const& projectile : projectilesEnemy) {
		projectile->calculateSpeed(game->currentLevel);
		projectile->update();
	}
	for (auto const& projectile : projectilesTurret) {
		projectile->update();
	}
	for (auto const& item : items) {
		item->update();
	}
	for (auto const& tile : tiles) {
		tile->update();
		ProjectileTurret* pTurret = tile->shoot();
		if (pTurret != NULL) {
			space->addDynamicActor(pTurret);
			projectilesTurret.push_back(pTurret);
		}
	}
	for (auto const& tile : goals) {
		tile->update();
	}

	if (player->collisionUp == true) {
		message = new Actor("res/mensaje_perder.png", WIDTH * 0.5, HEIGHT * 0.5,
			WIDTH, HEIGHT, game);
		pause = true;
		points = pointsPreLevel;
		init();
		return;
	}

	// Colisiones
	for (auto const& enemy : enemies) {
		if (player->isOverlap(enemy) && player->hit <=0) {
			if (player->invencibleTime > 0) {
				enemy->impacted();
			}
			else {
				if (enemy->state != game->stateDying && enemy->state != game->stateDead) {
					enemy->state = game->stateHiting;
					player->loseLife();
					textLifes->content = to_string(player->lifes);
					if (player->lifes <= 0) {
						message = new Actor("res/mensaje_perder.png", WIDTH * 0.5, HEIGHT * 0.5,
							WIDTH, HEIGHT, game);
						pause = true;
						points = pointsPreLevel;
						init();
						return;
					}
				}
			}
		}
	}

	list<Enemy*> deleteEnemies;
	list<Tile*> deleteTiles;
	list<Projectile*> deleteProjectiles;
	list<Item*> deleteItems;
	list<ProjectileEnemy*> deleteProjectilesEnemy;
	list<ProjectileTurret*> deleteProjectilesTurret;

	for (auto const& item : items) {
		if (player->isOverlap(item)) {
			bool pInList = std::find(deleteItems.begin(),
				deleteItems.end(),
				item) != deleteItems.end();

			if (!pInList) {
				deleteItems.push_back(item);
			}
			int* p = &points;
			int* s = &(player->bullets);
			int* l = &(player->lifes);
			int pUp = 5;
			int numEnemigos = 0;
			for (auto const& enemy : enemies) {
				numEnemigos += 1;
			}
			for (auto const& tile : tiles) {
				numEnemigos += 1;
			}
			pUp = item->boosteo(p, s, l, textPoints, textBullets, textLifes, numEnemigos);
			if (pUp == 3) { //Nuclear
				audioBoost = new Audio("res/efecto_explosion.wav", false);
				audioBoost->play();
				for (auto const& enemy : enemies) {
					deleteEnemies.push_back(enemy);
				}
				for (auto const& tile : tiles) {
					if ((tile->destroyByProjectile() || tile->isTurret())) {
						deleteTiles.push_back(tile);
					}
				}
			}
			else if (pUp == 0) { //Coin
				audioBoost = new Audio("res/coin.wav", false);
				audioBoost->play();
			}
			else if (pUp == 2) {//ExtraAmmo
				audioBoost = new Audio("res/ammo.wav", false);
				audioBoost->play();
			}
			else if (pUp == 1) { //ExtraLife
				audioBoost = new Audio("res/life.wav", false);
				audioBoost->play();
			}
			else if (pUp == 4) { //Invencibilidad
				player->invencibleTime = 250;
				audioBoost = new Audio("res/invencible.wav", false);
				audioBoost->play();
			}
		}
	}

	for (auto const& projectile : projectiles) {
		if (projectile->vy == 0) {
			bool pInList = std::find(deleteProjectiles.begin(),
				deleteProjectiles.end(),
				projectile) != deleteProjectiles.end();

			if (!pInList) {
				deleteProjectiles.push_back(projectile);
			}
		}
		for (auto const& tile : goals) {
			if (projectile->isOverlap(tile)) {
				bool pInList = std::find(deleteProjectiles.begin(),
					deleteProjectiles.end(),
					projectile) != deleteProjectiles.end();

				if (!pInList) {
					deleteProjectiles.push_back(projectile);
				}
			}
		}
	}
	for (auto const& projectile : projectilesEnemy) {
		if (projectile->vy == 0) {

			bool pInList = std::find(deleteProjectilesEnemy.begin(),
				deleteProjectilesEnemy.end(),
				projectile) != deleteProjectilesEnemy.end();

			if (!pInList) {
				deleteProjectilesEnemy.push_back(projectile);
			}
		}
	}
	for (auto const& projectile : projectilesTurret) {
		if (projectile->vy == 0) {

			bool pInList = std::find(deleteProjectilesTurret.begin(),
				deleteProjectilesTurret.end(),
				projectile) != deleteProjectilesTurret.end();

			if (!pInList) {
				deleteProjectilesTurret.push_back(projectile);
			}
		}
	}


	for (auto const& enemy : enemies) {
		for (auto const& projectile : projectiles) {
			if (enemy->isOverlap(projectile)) {
				bool pInList = std::find(deleteProjectiles.begin(),
					deleteProjectiles.end(),
					projectile) != deleteProjectiles.end();

				if (!pInList) {
					deleteProjectiles.push_back(projectile);
				}
				enemy->impacted();
				points++;
				textPoints->content = to_string(points);
			}
		}
	}

	for (auto const& tile : tiles) {
		for (auto const& projectile : projectiles) {
			if (tile->isOverlap(projectile)) {
				bool pInList = std::find(deleteProjectiles.begin(),
					deleteProjectiles.end(),
					projectile) != deleteProjectiles.end();

				if (!pInList) {
					deleteProjectiles.push_back(projectile);
				}
				if (tile->destroyByProjectile()) {
					bool tInList = std::find(deleteTiles.begin(),
						deleteTiles.end(),
						tile) != deleteTiles.end();

					if (!tInList) {
						deleteTiles.push_back(tile);
					}
					points++;
					textPoints->content = to_string(points);
				}
			}
		}
		for (auto const& projectile : projectilesEnemy) {
			if (tile->isOverlap(projectile)) {
				bool pInList = std::find(deleteProjectilesEnemy.begin(),
					deleteProjectilesEnemy.end(),
					projectile) != deleteProjectilesEnemy.end();

				if (!pInList) {
					deleteProjectilesEnemy.push_back(projectile);
				}
			}
		}
	}

	for (auto const& projectile : projectilesEnemy) {
		if (player->isOverlap(projectile)) {
			bool pInList = std::find(deleteProjectilesEnemy.begin(),
				deleteProjectilesEnemy.end(),
				projectile) != deleteProjectilesEnemy.end();

			if (!pInList) {
				deleteProjectilesEnemy.push_back(projectile);
			}

			player->loseLife();
			textLifes->content = to_string(player->lifes);
			if (player->lifes <= 0) {
				message = new Actor("res/mensaje_perder.png", WIDTH * 0.5, HEIGHT * 0.5,
					WIDTH, HEIGHT, game);
				pause = true;
				points = pointsPreLevel;
				init();
				return;
			}

		}
	}

	for (auto const& projectile : projectilesTurret) {
		if (player->isOverlap(projectile)) {
			bool pInList = std::find(deleteProjectilesTurret.begin(),
				deleteProjectilesTurret.end(),
				projectile) != deleteProjectilesTurret.end();

			if (!pInList) {
				deleteProjectilesTurret.push_back(projectile);
			}

			player->loseLife();
			textLifes->content = to_string(player->lifes);
			if (player->lifes <= 0) {
				message = new Actor("res/mensaje_perder.png", WIDTH * 0.5, HEIGHT * 0.5,
					WIDTH, HEIGHT, game);
				pause = true;
				points = pointsPreLevel;
				init();
				return;
			}

		}
	}

	for (auto const& enemy : enemies) {
		if (enemy->state == game->stateDead) {
			bool eInList = std::find(deleteEnemies.begin(),
				deleteEnemies.end(),
				enemy) != deleteEnemies.end();

			if (!eInList) {
				deleteEnemies.push_back(enemy);
			}
		}
	}

	// Borrado de las listas de elementos eliminados

	for (auto const& delEnemy : deleteEnemies) {
		enemies.remove(delEnemy);
		space->removeDynamicActor(delEnemy);
	}
	deleteEnemies.clear();

	for (auto const& delItem : deleteItems) {
		items.remove(delItem);
		space->removeDynamicActor(delItem);
	}
	deleteItems.clear();

	for (auto const& delTile : deleteTiles) {
		tiles.remove(delTile);
		space->removeStaticActor(delTile);
	}
	deleteTiles.clear();

	for (auto const& delProjectile : deleteProjectiles) {
		projectiles.remove(delProjectile);
		space->removeDynamicActor(delProjectile);
		delete delProjectile;
	}
	deleteProjectiles.clear();

	for (auto const& delProjectile : deleteProjectilesEnemy) {
		projectilesEnemy.remove(delProjectile);
		space->removeDynamicActor(delProjectile);
		delete delProjectile;
	}
	deleteProjectilesEnemy.clear();

	for (auto const& delProjectile : deleteProjectilesTurret) {
		projectilesTurret.remove(delProjectile);
		space->removeDynamicActor(delProjectile);
		delete delProjectile;
	}
	deleteProjectilesTurret.clear();


	//cout << "update GameLayer" << endl;
}

void GameLayer::calculateScroll() {

	// limite arriba
	if (player->y > HEIGHT * 0.87) { //0.87
		if (player->y - scrollY < HEIGHT * 0.87) {
			scrollY = player->y - HEIGHT * 0.87;
		}
	}

	// limite abajo
	if (player->y < mapHeight - HEIGHT * 0.13) {
		if (player->y - scrollY > HEIGHT * 0.87) {
			scrollY = player->y - HEIGHT * 0.87;
		}
	}
}


void GameLayer::draw() {
	calculateScroll();

	background->draw();
	for (auto const& tile : tiles) {
		tile->draw(scrollX,scrollY);
	}
	for (auto const& item : items) {
		item->draw(scrollX, scrollY);
	}
	for (auto const& projectile : projectiles) {
		projectile->draw(scrollX, scrollY);
	}
	for (auto const& projectile : projectilesEnemy) {
		projectile->draw(scrollX, scrollY);
	}
	for (auto const& projectile : projectilesTurret) {
		projectile->draw(scrollX, scrollY);
	}
	for (auto const& goal : goals) {
		goal->draw(scrollX, scrollY);
	}
	player->draw(scrollX, scrollY);
	for (auto const& enemy : enemies) {
		enemy->draw(scrollX, scrollY);
	}

	backgroundPoints->draw();
	textPoints->draw();

	backgroundBullets->draw();
	textBullets->draw();

	backgroundLifes->draw();
	textLifes->draw();

	textFinalPoints->draw();

	buttonPause->draw();

	// HUD
	if (game->input == game->inputMouse) {
		buttonShoot->draw(); // NO TIENEN SCROLL, POSICION FIJA
		buttonLeft->draw(); // NO TIENEN SCROLL, POSICION FIJA
		buttonRight->draw(); // NO TIENEN SCROLL, POSICION FIJA
	}
	if (pause) {
		message->draw();
	}

	SDL_RenderPresent(game->renderer); // Renderiza
}

void GameLayer::gamePadToControls(SDL_Event event) {

	// Leer los botones
	bool buttonA = SDL_GameControllerGetButton(gamePad, SDL_CONTROLLER_BUTTON_A);
	bool buttonStart = SDL_GameControllerGetButton(gamePad, SDL_CONTROLLER_BUTTON_START);
	//cout << "botón:" << buttonA << ", " << buttonStart << endl;
	int stickX = SDL_GameControllerGetAxis(gamePad, SDL_CONTROLLER_AXIS_LEFTX);
	//cout << "stickX" << stickX << endl;

	// Retorna aproximadamente entre [-32800, 32800], el centro debería estar en 0
	// Si el mando tiene "holgura" el centro varia [-4000 , 4000]
	if (stickX > 4000) {
		controlMoveX = 1;
	}
	else if (stickX < -4000) {
		controlMoveX = -1;
	}
	else {
		controlMoveX = 0;
	}

	if (buttonA) {
		controlShoot = true;
	}
	else {
		controlShoot = false;
	}

	if (buttonStart) {
		pause = true;
		message = new Actor("res/mensaje_pausa.png", WIDTH * 0.5, HEIGHT * 0.5,
			WIDTH, HEIGHT, game);
	}
}


void GameLayer::mouseToControls(SDL_Event event) {
	// Modificación de coordenadas por posible escalado
	float motionX = event.motion.x / game->scaleLower;
	float motionY = event.motion.y / game->scaleLower;
	// Cada vez que hacen click
	if (event.type == SDL_MOUSEBUTTONDOWN) {
		controlContinue = true;
		if (buttonShoot->containsPoint(motionX, motionY)) {
			controlShoot = true;
		}
		if (buttonLeft->containsPoint(motionX, motionY)) {
			buttonLeft->clicked = true;
			controlMoveX = -1;
		}
		if (buttonRight->containsPoint(motionX, motionY)) {
			buttonRight->clicked = true;
			controlMoveX = 1;
		}
	}
	// Cada vez que se mueve
	if (event.type == SDL_MOUSEMOTION) {
		if (buttonRight->containsPoint(motionX, motionY) == false && buttonLeft->containsPoint(motionX, motionY) == false) {
			controlMoveX = 0;
		}
		if (buttonShoot->containsPoint(motionX, motionY) == false) {
			controlShoot = false;
		}
	}
	// Cada vez que levantan el click
	if (event.type == SDL_MOUSEBUTTONUP) {
		if (buttonLeft->containsPoint(motionX, motionY)) {
			buttonLeft->clicked = false;
			// LEVANTAR EL CLICK TAMBIEN TE PARA
			controlMoveX = 0;
		}
		if (buttonRight->containsPoint(motionX, motionY)) {
			buttonRight->clicked = false;
			// LEVANTAR EL CLICK TAMBIEN TE PARA
			controlMoveX = 0;
		}

		if (buttonShoot->containsPoint(motionX, motionY)) {
			controlShoot = false;
		}
		if (buttonPause->containsPoint(motionX, motionY)) {
			pause = true;
			message = new Actor("res/mensaje_pausa.png", WIDTH * 0.5, HEIGHT * 0.5,
				WIDTH, HEIGHT, game);
		}
	}
}


void GameLayer::keysToControls(SDL_Event event) {
	if (event.type == SDL_KEYDOWN) {
		int code = event.key.keysym.sym;
		// Pulsada
		switch (code) {
		case SDLK_ESCAPE:
			game->loopActive = false;
			break;
		case SDLK_1:
			game->scale();
			break;
		case SDLK_s: // pausa
			if (pause) {
				pause = false;
			}
			else {
				pause = true;
				message = new Actor("res/mensaje_pausa.png", WIDTH * 0.5, HEIGHT * 0.5,
					WIDTH, HEIGHT, game);
			}
			break;
		case SDLK_d: // derecha
			controlMoveX = 1;
			break;
		case SDLK_a: // izquierda
			controlMoveX = -1;
			break;
		case SDLK_SPACE: // dispara
			controlShoot = true;
			break;
		}


	}
	if (event.type == SDL_KEYUP) {
		int code = event.key.keysym.sym;
		// Levantada
		switch (code) {
		case SDLK_d: // derecha
			if (controlMoveX == 1) {
				controlMoveX = 0;
			}
			break;
		case SDLK_a: // izquierda
			if (controlMoveX == -1) {
				controlMoveX = 0;
			}
			break;
		case SDLK_SPACE: // dispara
			controlShoot = false;
			break;
		}

	}

}
