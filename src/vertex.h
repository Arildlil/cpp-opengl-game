#ifndef VERTEX_H
#define VERTEX_H

namespace Core {
    struct Vertex {
        float x, y, z;
        float nx, ny, nz;

        Vertex(float x, float y, float z, float nx, float ny, float nz)
            :x{x}, y{y}, z{z}, nx{nx}, ny{ny}, nz{nz} {};
    };
};

#endif