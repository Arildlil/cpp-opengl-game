#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>

namespace Core {
    struct Texture {
        unsigned int id;
        std::string type;
        std::string path;
    };
};

#endif