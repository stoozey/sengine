#ifndef SENGINE_TEXT_CHARACTER_HPP
#define SENGINE_TEXT_CHARACTER_HPP

#include <glm/glm.hpp>
#include <ft2build.h>
#include FT_FREETYPE_H

namespace structs {
    struct TextCharacter {
        unsigned int textureId;
        FT_Pos advance;
        glm::ivec2 size;
        glm::ivec2 bearing;
    };
}

#endif //SENGINE_TEXT_CHARACTER_HPP
