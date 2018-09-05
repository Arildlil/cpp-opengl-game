#ifndef VERTEX_H
#define VERTEX_H

namespace Core {
    struct Vertex {
        float x, y, z;

        Vertex(float x, float y, float z)
            :x{x}, y{y}, z{z} {};
    };
};

#endif