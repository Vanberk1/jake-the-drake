#pragma once

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 640;

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