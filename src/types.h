#pragma once

const int SPRITE_SCALE = 3;

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

using EntityId = unsigned int;

enum ColliderTag {
    NONE,
    GUI,
    PLAYER,
    ALLEY,
    ENEMY,
    FRIENDLY_PROJECTILE,
    ENEMY_PROJECTILE,
    OBASTACLE
};

enum CollisionType {
    NO_COLLISION,
    PLAYER_ENEMY_COLLISION,
    PLAYER_PROJECTILE_COLLISION,
    ENEMY_PROJECTILE_COLLISION,
    PLAYER_VEGETATION_COLLISION,
    PLAYER_LEVEL_COMPLETE_COLLISION
};

enum ComponentType {
    TransformComponent,
    SpriteComponent,
    ColliderComponent,
    PlayerComponent
};

enum SystemType {
    RenderSystem,
    PhysicsSystem,
    CollisionSystem,
    ControlSystem
};