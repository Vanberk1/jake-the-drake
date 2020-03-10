#include "playState.h"

PlayState::PlayState(SDL_Renderer* renderer) {
    m_Renderer = renderer;
    m_IsPaused = false;
    m_GameOver = false;
}

void PlayState::OnEnter() {
    background.Init("background", -70, 160, 96);

    jake.SetPosition(100, 100);
    jake.LoadTexture("duck", 16, 16, SPRITE_SCALE, true);
    jake.AddAnimation("idle", 3, 200, 0);
    jake.AddAnimation("yellow", 3, 200, 1);
    jake.AddAnimation("shoot", 3, 100, 2);
    jake.SetAnimation("idle");
    jake.Init(&projectiles);
    jake.SetHealth(3);

    // std::cout << "Score: " << jake.GetScore() << std::endl;
    TTF_Font* font = fontManager.GetFont("arial", 24);
    m_PauseText.init(m_Renderer, font);
    m_GameOverText.init(m_Renderer, font);
	m_RestartText.init(m_Renderer, font);
    m_ScoreLabel.init(m_Renderer, font);
    m_ScoreLabel.setPosition({ 550, 25, 0, 0 });
	m_ScoreLabel.createLabel("SCORE: 0", { 255, 255, 255, 255 }); 
    m_HealthText.init(m_Renderer, font);
    m_HealthText.setPosition({ 25, 25, 0, 0 });
    std::stringstream ss;
    ss << jake.GetActualHealth() << "/" << jake.GetMaxHealth();
	m_HealthText.createLabel(ss.str(), { 255, 255, 255, 255 }); 

    m_PauseText.createLabel("PAUSE!", { 255, 255, 255, 255 });
    SDL_Rect* textPosition = m_PauseText.getPosition();
	textPosition->x = (WINDOW_WIDTH / 2) - (textPosition->w / 2);
	textPosition->y = (WINDOW_HEIGHT / 2) - (textPosition->h / 2);
	m_RestartText.setPosition(*textPosition);
	m_RestartText.setText("PAUSE!");

	m_GameOverText.createLabel("GAME OVER", { 255, 255, 255, 255 });
	textPosition = m_GameOverText.getPosition();
	textPosition->x = (WINDOW_WIDTH / 2) - (textPosition->w / 2);
	textPosition->y = (WINDOW_HEIGHT / 2) - (textPosition->h / 2) - 60;
	m_GameOverText.setPosition(*textPosition);
	m_GameOverText.setText("GAME OVER");

	m_RestartText.createLabel("PRESS 'R' TO RESTART", { 255, 255, 255, 255 });
	textPosition = m_RestartText.getPosition();
	textPosition->x = (WINDOW_WIDTH / 2) - (textPosition->w / 2);
	textPosition->y = (WINDOW_HEIGHT / 2) - (textPosition->h / 2);
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
    if(!m_GameOver) {
        if(KeyPressed(SDL_SCANCODE_ESCAPE)) {
            m_IsPaused = m_IsPaused ? false : true;
            std::cout << (m_IsPaused ? "Pause!" : "Unpause!") << std::endl;
        }
        if(!m_IsPaused) {
            if(KeyPressed(SDL_SCANCODE_W)) {
                // std::cout << "W Pressed" << std::endl;
                jake.MoveVertical(-1);
            }
            if(KeyPressed(SDL_SCANCODE_A)) {
                // std::cout << "A Pressed" << std::endl;
                jake.MoveHorizontal(-1);
            }
            if(KeyPressed(SDL_SCANCODE_S)) {
                // std::cout << "S Pressed" << std::endl;
                jake.MoveVertical(1);
            }
            if(KeyPressed(SDL_SCANCODE_D)) {
                // std::cout << "D Pressed" << std::endl;
                jake.MoveHorizontal(1);
            }
            if(KeyPressed(SDL_SCANCODE_SPACE)) {
                jake.Shooting(true);
                jake.SetAnimation("shoot");
            }
            
            if(KeyReleased(SDL_SCANCODE_W)) {
                if(IsKeyPressed(SDL_SCANCODE_S)) {
                    // std::cout << "W Released : S Still Press" << std::endl;
                    jake.MoveVertical(1);
                } else {
                    // std::cout << "W Released : S Not Press" << std::endl;
                    jake.MoveVertical(0);
                }
            }
            if(KeyReleased(SDL_SCANCODE_A)) {
                if(IsKeyPressed(SDL_SCANCODE_D)) {
                    // std::cout << "A Released : D Still Press" << std::endl;
                    jake.MoveHorizontal(1);
                }
                else {
                    // std::cout << "A Released : D Not Press" << std::endl;
                    jake.MoveHorizontal(0);
                }
            }
            if(KeyReleased(SDL_SCANCODE_S)) {
                if(IsKeyPressed(SDL_SCANCODE_W)) {
                    jake.MoveVertical(-1);
                    // std::cout << "S Released : W Still Press" << std::endl;
                } else {
                    // std::cout << "S Released : W Not Press" << std::endl;
                    jake.MoveVertical(0);
                }
            }
            if(KeyReleased(SDL_SCANCODE_D)) {
                if(IsKeyPressed(SDL_SCANCODE_A)) {
                    // std::cout << "A Released : D Still Press" << std::endl;
                    jake.MoveHorizontal(-1);
                }
                else {
                    // std::cout << "A Released : D Not Press" << std::endl;
                    jake.MoveHorizontal(0);
                }
            }
            if(KeyReleased(SDL_SCANCODE_SPACE)) {
                jake.Shooting(false);
                jake.SetAnimation("idle");
            }
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
    if(!m_GameOver && !m_IsPaused) {
        background.Update(deltaTime);
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
    background.Render(renderer);
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
    m_ScoreLabel.draw(renderer);
    // m_HealthText.draw(renderer);

    if(m_GameOver) {
		m_GameOverText.draw(m_Renderer);
		m_RestartText.draw(m_Renderer);
	}
    else {
        if(m_IsPaused) {
            m_PauseText.draw(m_Renderer);
        }
    }
}

void PlayState::PlayerEnemyCollision() {
    for(int i = 0; i < enemies.size(); ++i) {
        if(jake.GetCollider().AABBCollision(enemies[i]->GetCollider())) {
            enemies.erase(enemies.begin() + i);
            jake.PlayAnimation("yellow");
            jake.UpdateHealth(-1);
            std::stringstream ss;
            ss << jake.GetActualHealth() << "/" << jake.GetMaxHealth();
            m_HealthText.setText(ss.str());
            if(!jake.GetActualHealth()) {
                m_GameOver = true;
            }
        }
    }
}

void PlayState::ProjectileEnemyCollision() {
    for(int i = 0; i < projectiles.size(); ++i) {
        for(int j = 0; j < enemies.size(); ++j) {
            if(projectiles[i].GetCollider().AABBCollision(enemies[j]->GetCollider())) {
                projectiles.erase(projectiles.begin() + i);
                if(enemies[j]->GetHealth() - jake.GetDamage() <= 0) {
                    jake.AddPoints(enemies[j]->GetRewardPoints());
                    enemies.erase(enemies.begin() + j);
                }
                else {
                    enemies[j]->UpdateHealth(-jake.GetDamage());
                }

                std::stringstream ss;
				ss << "SCORE: " << jake.GetScore();
				m_ScoreLabel.setText(ss.str());
            }
        }
    }
}

void PlayState::ProjectilePlayerCollision() {
    for(int i = 0; i < enemyProjectiles.size(); ++i) {
        if(jake.GetCollider().AABBCollision(enemyProjectiles[i].GetCollider())) {
            enemyProjectiles.erase(enemyProjectiles.begin() + i);
            jake.PlayAnimation("yellow");
            jake.UpdateHealth(-1);
            // std::stringstream ss;
            // ss << jake.GetActualHealth() << "/" << jake.GetMaxHealth();
            // m_HealthText.setText(ss.str());
            if(!jake.GetActualHealth()) {
                m_GameOver = true;
            }
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

bool PlayState::IsKeyPressed
(SDL_Scancode scanCode) {
    return currentKeyState[scanCode];
}