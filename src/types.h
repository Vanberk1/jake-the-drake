#pragma once

const int SPRITE_SCALE = 3;
const int MAP_SCALE = 5;
const int w = 160;
const int h = 96;
const int WINDOW_WIDTH = w * MAP_SCALE;
const int WINDOW_HEIGHT = h * MAP_SCALE;

using EntityId = unsigned int;

enum ShootingType {
    NORMAL_SHOOT,
    DOUBLE_SHOOT,
    TRIPLE_SHOOT
};

enum ColliderTag {
    NONE,
    GUI,
    PLAYER,
    ALLEY,
    ENEMY,
    FRIENDLY_PROJECTILE,
    ENEMY_PROJECTILE,
    OBASTACLE,
    BUFF
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