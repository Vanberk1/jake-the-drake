#pragma once

#include "../lib/glm/glm.hpp"

class TransformComponent : public Component {
    glm::vec2 position;
    glm::vec2 rotation;
    glm::vec2 scale;
};