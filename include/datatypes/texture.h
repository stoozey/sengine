#ifndef SENGINE_TEST1_TEXTURE_H
#define SENGINE_TEST1_TEXTURE_H

#include <iostream>
#include <glad.h>

struct Texture {
//    Texture(GLenum textureTypeAidan, size_t textureDataSizeAidan, char *textureDataAidan) {
//        textureType = textureTypeAidan;
//        textureDataSize = textureDataSizeAidan;
//        textureData = textureDataAidan;
//    }

//    ~Texture() {
//        std::cout << "destroying" << std::endl;
//        delete textureData;
//    }

    GLenum textureType;
    size_t textureDataSize;
    char *textureData;
};

#endif //SENGINE_TEST1_TEXTURE_H
