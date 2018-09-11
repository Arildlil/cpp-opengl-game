#include "entity.h"

using namespace Core;

Entity::Entity(const Core::Mesh& mesh, glm::vec3 pos, float scale) 
    :m_mesh{mesh}, m_pos{pos}, m_scale{scale}
{

}

Entity::~Entity() {}