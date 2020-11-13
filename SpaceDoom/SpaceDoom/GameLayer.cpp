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
	pad = new Pad(WIDTH * 0.15, HEIGHT * 0.60, game);
	buttonShoot = new Actor("res/boton_disparo.png", WIDTH * 0.75, HEIGHT * 0.83, 100, 100, game);

	space = new Space(1);
	scrollY = 0;
	scrollX = 0;
	tiles.clear();

	//audioBackground = new Audio("res/musica_ambiente.mp3", true);
	//audioBackground->play();

	points = 0;
	textPoints = new Text("Puntos", WIDTH * 0.92, HEIGHT * 0.04, game);
	textPoints->content = to_string(points);
	textLifes = new Text("Vidas", WIDTH * 0.15, HEIGHT * 0.94, game);
	textBullets = new Text("Balas", WIDTH * 0.79, HEIGHT * 0.04, game);


	background = new Background("res/fondo_2.png", WIDTH * 0.5, HEIGHT * 0.5, -1, game);
	backgroundPoints = new Actor("res/icono_puntos.png",
		WIDTH * 0.85, HEIGHT * 0.04, 24, 24, game);
	backgroundBullets = new Actor("res/bullet.png",
		WIDTH * 0.73, HEIGHT * 0.04, 61, 64, game);
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
			// Por carácter (en cada línea)
			for (int j = 0; !streamLine.eof(); j++) {
				streamLine >> character; // Leer character 
				cout << character;
				float x = 40 / 2 + j * 40; // x central
				float y = 32 + i * 32; // y suelo
				loadMapObject(character, x, y);
			}

			cout << character << endl;
		}
	}
	streamFile.close();
}

void GameLayer::loadMapObject(char character, float x, float y)
{
	switch (character) {
	case 'C': {
		CommonTile* cup = new CommonTile("res/meta.png", x, y, 1, 40, 40, game);
		cup->y = cup->y - cup->height / 2;
		goals.push_back(cup);
		space->addStaticActor(cup);
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
		CommonTile* tile = new CommonTile("res/tile.png", x, y, 1, 40, 40, game);
		tile->y = tile->y - tile->height / 2;
		tiles.push_back(tile);
		space->addStaticActor(tile);
		break;
	}
	case 'D': {
		DestroyableTile* tile = new DestroyableTile("res/destroyTile.png", x, y, 1, 40, 40, game);
		tile->y = tile->y - tile->height / 2;
		tiles.push_back(tile);
		space->addStaticActor(tile);
		break;
	}
	case 'T': {
		Turret* tile = new Turret("res/turret.png", x, y, 1, 85, 85, game);
		tile->y = tile->y - tile->height / 2;
		tiles.push_back(tile);
		space->addStaticActor(tile);
		break;
	}
	case 'A': {
		ExtraAmmo* item = new ExtraAmmo("res/extraAmmo.png", x, y, 40, 40, 1, game);
		item->y = item->y - item->height / 2;
		items.push_back(item);
		space->addStaticActor(item);
		break;
	}
	case 'L': {
		ExtraLife* item = new ExtraLife("res/corazon.png", x, y, 44, 36, 1, game);
		item->y = item->y - item->height / 2;
		items.push_back(item);
		space->addStaticActor(item);
		break;
	}/*
	case 'N': {
		Nuclear* item = new Nuclear("res/turret.png", x, y, 1, 40, 40, game);
		item->y = item->y - item->height / 2;
		items.push_back(item);
		space->addStaticActor(item);
		break;
	}case 'I': {
		Invencible* item = new Invencible("res/turret.png", x, y, 1, 40, 40, game);
		item->y = item->y - item->height / 2;
		items.push_back(item);
		space->addStaticActor(item);
		break;
	}*/
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
	//procesar controles
	//procesar controles
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
}

void GameLayer::update() {
	if (pause) {
		return;
	}

	// Nivel superado
	for (auto const& goal : goals) {
		if (goal->isOverlap(player)) {
			game->currentLevel++;
			if (game->currentLevel > game->finalLevel) {
				game->currentLevel = 0;
			}
			message = new Actor("res/mensaje_ganar.png", WIDTH * 0.5, HEIGHT * 0.5,
				WIDTH, HEIGHT, game);
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


	// Colisiones
	for (auto const& enemy : enemies) {
		if (player->isOverlap(enemy)) {
			enemy->state = game->stateHiting;
			player->loseLife();
			textLifes->content = to_string(player->lifes);
			if (player->lifes <= 0) {
				message = new Actor("res/mensaje_perder.png", WIDTH * 0.5, HEIGHT * 0.5,
					WIDTH, HEIGHT, game);
				pause = true;
				init();
				return;
			}
		}
	}

	for (auto const& tile : tiles) {
		if (player->isOverlapTile(tile)) {
			init();
			return;
		}
	}

	list<Enemy*> deleteEnemies;
	list<Tile*> deleteTiles;
	list<Projectile*> deleteProjectiles;
	list<Item*> deleteItems;
	list<ProjectileEnemy*> deleteProjectilesEnemy;
	list<ProjectileTurret*> deleteProjectilesTurret;

	for (auto const& item : items) {
		for (auto const& goal : goals) {
			if (item->isOverlapTile(goal)) {
				bool pInList = std::find(deleteItems.begin(),
					deleteItems.end(),
					item) != deleteItems.end();

				if (!pInList) {
					deleteItems.push_back(item);
				}
			}
		}
	}

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
				if (enemy->isInRender()) {
					numEnemigos += 1;
				}
			}
			pUp = item->boosteo(p, s, l, textPoints, textBullets, textLifes, numEnemigos);
			if (pUp == 3) { //Nuclear
				audioBoost = new Audio("res/efecto_explosion.wav", false);
				audioBoost->play();
				for (auto const& enemy : enemies) {
					if (enemy->isInRender()) {
						deleteEnemies.push_back(enemy);
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
				audioBoost = new Audio("res/ammo.wav", false);
				audioBoost->play();
			}
			else if (pUp == 4) { //Invencibilidad
				audioBoost = new Audio("res/ammo.wav", false);
				audioBoost->play();
			}
		}
	}

	for (auto const& projectile : projectiles) {
		if (projectile->isInRender(scrollY) == false || projectile->vy == 0) {
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
		if (projectile->isInRender(scrollY) == false || projectile->vy == 0) {

			bool pInList = std::find(deleteProjectilesEnemy.begin(),
				deleteProjectilesEnemy.end(),
				projectile) != deleteProjectilesEnemy.end();

			if (!pInList) {
				deleteProjectilesEnemy.push_back(projectile);
			}
		}
	}
	for (auto const& projectile : projectilesTurret) {
		if (projectile->isInRender(scrollY) == false || projectile->vy == 0) {

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
		/*
		for (auto const& projectile : projectilesTurret) {
			if (tile->isOverlap(projectile)) {
				bool pInList = std::find(deleteProjectilesTurret.begin(),
					deleteProjectilesTurret.end(),
					projectile) != deleteProjectilesTurret.end();

				if (!pInList) {
					deleteProjectilesTurret.push_back(projectile);
				}
			}
		}*/
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
		space->removeDynamicActor(delTile);
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
	// limite izquierda
	if (player->x > WIDTH * 0.3) {
		if (player->x - scrollX < WIDTH * 0.3) {
			scrollX = player->x - WIDTH * 0.3;
		}
	}

	// limite derecha
	if (player->x < mapWidth - WIDTH * 0.3) {
		if (player->x - scrollX > WIDTH * 0.7) {
			scrollX = player->x - WIDTH * 0.7;
		}
	}
}


void GameLayer::draw() {
	calculateScroll();

	background->draw();
	for (auto const& tile : tiles) {
		tile->draw(scrollY);
	}
	for (auto const& item : items) {
		item->draw(scrollY);
	}
	for (auto const& projectile : projectiles) {
		projectile->draw(scrollY);
	}
	for (auto const& projectile : projectilesEnemy) {
		projectile->draw(scrollY);
	}
	for (auto const& projectile : projectilesTurret) {
		projectile->draw(scrollY);
	}
	for (auto const& goal : goals) {
		goal->draw(scrollY);
	}
	player->draw(scrollY);
	for (auto const& enemy : enemies) {
		enemy->draw(scrollY);
	}

	backgroundPoints->draw();
	textPoints->draw();

	backgroundBullets->draw();
	textBullets->draw();

	backgroundLifes->draw();
	textLifes->draw();

	// HUD
	if (game->input == game->inputMouse) {
		buttonShoot->draw(); // NO TIENEN SCROLL, POSICION FIJA
		pad->draw(); // NO TIENEN SCROLL, POSICION FIJA
	}
	if (pause) {
		message->draw();
	}

	SDL_RenderPresent(game->renderer); // Renderiza
}

void GameLayer::gamePadToControls(SDL_Event event) {

	// Leer los botones
	bool buttonA = SDL_GameControllerGetButton(gamePad, SDL_CONTROLLER_BUTTON_A);
	bool buttonB = SDL_GameControllerGetButton(gamePad, SDL_CONTROLLER_BUTTON_B);
	// SDL_CONTROLLER_BUTTON_A, SDL_CONTROLLER_BUTTON_B
	// SDL_CONTROLLER_BUTTON_X, SDL_CONTROLLER_BUTTON_Y
	cout << "botones:" << buttonA << "," << buttonB << endl;
	int stickX = SDL_GameControllerGetAxis(gamePad, SDL_CONTROLLER_AXIS_LEFTX);
	cout << "stickX" << stickX << endl;

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

	if (buttonB) {
		controlMoveY = -1; // Saltar
	}
	else {
		controlMoveY = 0;
	}
}


void GameLayer::mouseToControls(SDL_Event event) {
	// Modificación de coordenadas por posible escalado
	float motionX = event.motion.x / game->scaleLower;
	float motionY = event.motion.y / game->scaleLower;
	// Cada vez que hacen click
	if (event.type == SDL_MOUSEBUTTONDOWN) {
		controlContinue = true;
		if (pad->containsPoint(motionX, motionY)) {
			pad->clicked = true;
			// CLICK TAMBIEN TE MUEVE
			controlMoveX = pad->getOrientationX(motionX);
		}
		if (buttonShoot->containsPoint(motionX, motionY)) {
			controlShoot = true;
		}

	}
	// Cada vez que se mueve
	if (event.type == SDL_MOUSEMOTION) {
		if (pad->clicked && pad->containsPoint(motionX, motionY)) {
			controlMoveX = pad->getOrientationX(motionX);
			// Rango de -20 a 20 es igual que 0
			if (controlMoveX > -20 && controlMoveX < 20) {
				controlMoveX = 0;
			}

		}
		else {
			pad->clicked = false; // han sacado el ratón del pad
			controlMoveX = 0;
		}
		if (buttonShoot->containsPoint(motionX, motionY) == false) {
			controlShoot = false;
		}

	}
	// Cada vez que levantan el click
	if (event.type == SDL_MOUSEBUTTONUP) {
		if (pad->containsPoint(motionX, motionY)) {
			pad->clicked = false;
			// LEVANTAR EL CLICK TAMBIEN TE PARA
			controlMoveX = 0;
		}

		if (buttonShoot->containsPoint(motionX, motionY)) {
			controlShoot = false;
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
