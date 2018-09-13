#ifndef ENTITY_H
#define ENTITY_H

#include "../core/gl_header.h"

#include "../core/mesh.h"

namespace Core {
    class Entity {
        public:
            Entity(const Core::Mesh& mesh, glm::vec3 pos, float scale = 1.0f);
            virtual ~Entity();
            //void draw() const { m_mesh.draw(); }
            glm::vec3 getPos() const { return m_pos; }
            float getScale() const { return m_scale; }
            void setPos(const glm::vec3& toSet) { m_pos = toSet; }
            void addPos(const glm::vec3& toAdd) { m_pos += toAdd; }
        private:
            const Core::Mesh& m_mesh;
            glm::vec3 m_pos;
            float m_scale;
    };
};

#endif