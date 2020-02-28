#include "playState.h"

PlayState::PlayState(SDL_Renderer* renderer) {
    m_Renderer = renderer;
    gameOver = false;
}

void PlayState::OnEnter() {
    jake.SetPosition(100, 100);
    jake.LoadTexture("duck", 16, 16, SPRITE_SCALE, true);
    jake.AddAnimation("idle", 3, 200, 0);
    jake.AddAnimation("yellow", 3, 200, 1);
    jake.SetAnimation("idle");
    jake.Init(&projectiles);

    // std::cout << "Score: " << jake.GetScore() << std::endl;
    TTF_Font* font = fontManager.GetFont("arial", 24);
    m_GameOverText.init(m_Renderer, font);
	m_RestartText.init(m_Renderer, font);
    scoreLabel.init(m_Renderer, font);
    scoreLabel.setPosition({ 25, 25, 0 , 0 });
	scoreLabel.createLabel("SCORE: 0", { 255, 255, 255, 255 }); 

	m_GameOverText.createLabel("GAME OVER", { 255, 255, 255, 255 });
	SDL_Rect* textPosition = m_GameOverText.getPosition();
	textPosition->x = (800 / 2) - (textPosition->w / 2);
	textPosition->y = (600 / 2) - (textPosition->h / 2) - 60;
	m_GameOverText.setPosition(*textPosition);
	m_GameOverText.setText("GAME OVER");

	m_RestartText.createLabel("PRESS 'R' TO RESTART", { 255, 255, 255, 255 });
	textPosition = m_RestartText.getPosition();
	textPosition->x = (800 / 2) - (textPosition->w / 2);
	textPosition->y = (600 / 2) - (textPosition->h / 2);
	m_RestartText.setPosition(*textPosition);
	m_RestartText.setText("PRESS 'R' TO RESTART");

    spawner = new EnemySpawner(5, &jake, &enemyProjectiles);

    currentKeyState = SDL_GetKeyboardState(&keyLength);
    prevKeyState = new uint8_t[keyLength];
    memcpy(prevKeyState, currentKeyState, keyLength);
}

void PlayState::OnExit() {

}

void PlayState::InputHandler(SDL_Event event) {
    if(!gameOver) {
        if(KeyPressed(SDL_SCANCODE_W)) {
            jake.MoveVertical(-1);
        }
        if(KeyPressed(SDL_SCANCODE_A)) {
            jake.MoveHorizontal(-1);
        }
        if(KeyPressed(SDL_SCANCODE_S)) {
            jake.MoveVertical(1);
        }
        if(KeyPressed(SDL_SCANCODE_D)) {
            jake.MoveHorizontal(1);
        }
        if(KeyPressed(SDL_SCANCODE_SPACE)) {
            jake.Shooting(true);
            jake.SetAnimation("yellow");
        }
        
        if(KeyReleased(SDL_SCANCODE_W)) {
            jake.MoveVertical(0);
        }
        if(KeyReleased(SDL_SCANCODE_A)) {
            jake.MoveHorizontal(0);
        }
        if(KeyReleased(SDL_SCANCODE_S)) {
            jake.MoveVertical(0);
        }
        if(KeyReleased(SDL_SCANCODE_D)) {
            jake.MoveHorizontal(0);
        }
        if(KeyReleased(SDL_SCANCODE_SPACE)) {
            jake.Shooting(false);
            jake.SetAnimation("idle");
        }
    }
    else {
        if(event.key.keysym.scancode == SDL_SCANCODE_R) {
			gameStateMachine.Restart(std::make_unique<PlayState>(m_Renderer));
		}
    }

    memcpy(prevKeyState, currentKeyState, keyLength);
}

void PlayState::Update(float deltaTime) {
    if(!gameOver) {
        spawner->Run(deltaTime, enemies);

        jake.Update(deltaTime);
        for(int i = 0; i < projectiles.size(); ++i) {
            projectiles[i].Update(deltaTime);
            if(projectiles[i].GetPosition().x > WINDOW_WIDTH) {
                projectiles.erase(projectiles.begin() + i);
            }
        }
        for(int i = 0; i < enemyProjectiles.size(); ++i) {
            enemyProjectiles[i].Update(deltaTime);
            if(enemyProjectiles[i].GetPosition().x > WINDOW_WIDTH) {
                enemyProjectiles.erase(enemyProjectiles.begin() + i);
            }
        }
        for(int i = 0; i < enemies.size(); ++i) {
            enemies[i]->Update(deltaTime);
            if(enemies[i]->GetPosition().x + enemies[i]->GetWidth() < 0) {
                enemies.erase(enemies.begin() + i);
            }
        }
        
        PlayerEnemyCollision();
        ProjectilePlayerCollision();
        ProjectileEnemyCollision();
        BulletCollision();
    }
}

void PlayState::Render(SDL_Renderer* renderer) {
    jake.Render(renderer);
    for(Bullet& projectile : projectiles) {
        projectile.Render(renderer);
    }
    for(Bullet& projectile : enemyProjectiles) {
        projectile.Render(renderer);
    }
    for(Enemy* enemy : enemies) {
        enemy->Render(renderer);
    }
    scoreLabel.draw(renderer);

    if(gameOver) {
		m_GameOverText.draw(m_Renderer);
		m_RestartText.draw(m_Renderer);
	}
}

void PlayState::PlayerEnemyCollision() {
    for(int i = 0; i < enemies.size(); ++i) {
        if(jake.GetCollider().AABBCollision(enemies[i]->GetCollider())) {
           // std::cout << "Player Enemy Collision!" << std::endl;
           gameOver = true;
        }
    }
}

void PlayState::ProjectileEnemyCollision() {
    for(int i = 0; i < projectiles.size(); ++i) {
        for(int j = 0; j < enemies.size(); ++j) {
            if(projectiles[i].GetCollider().AABBCollision(enemies[j]->GetCollider())) {
                jake.AddPoints(enemies[j]->GetRewardPoints());
                projectiles.erase(projectiles.begin() + i);
                if(enemies[j]->GetHeal() - jake.GetDamage() <= 0) {
                    enemies.erase(enemies.begin() + j);
                }
                else {
                    enemies[j]->UpdateHeal(-jake.GetDamage());
                }

                std::stringstream ss;
				ss << "SCORE: " << jake.GetScore();
				scoreLabel.setText(ss.str());
            }
        }
    }
}

void PlayState::ProjectilePlayerCollision() {
    for(int i = 0; i < enemyProjectiles.size(); ++i) {
        if(jake.GetCollider().AABBCollision(enemyProjectiles[i].GetCollider())) {
            gameOver = true;
        }
    }
}

void PlayState::BulletCollision() {
    for(int i = 0; i < projectiles.size(); ++i) {
        for(int j = 0; j < enemyProjectiles.size(); ++j) {
            if(projectiles[i].GetCollider().AABBCollision(enemyProjectiles[j].GetCollider())) {
                enemyProjectiles.erase(enemyProjectiles.begin() + j);
                projectiles.erase(projectiles.begin() + i);
            }
        }
    }
}

bool PlayState::KeyPressed(SDL_Scancode scanCode) {
    return !prevKeyState[scanCode] && currentKeyState[scanCode];
}

bool PlayState::KeyReleased(SDL_Scancode scanCode) {
    return prevKeyState[scanCode] && !currentKeyState[scanCode];
}