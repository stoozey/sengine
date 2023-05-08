#ifndef SENGINE_FONT_HPP
#define SENGINE_FONT_HPP

#include <map>
#include <ft2build.h>
#include FT_FREETYPE_H

#include "assets/asset.hpp"
#include "structs/assets/asset_info.hpp"
#include "structs/text_character.hpp"

namespace assets {
    class Font : public Asset {
    public:
        Font();

        void Save(const std::string &filePath) override;
        void Load(const std::string &filePath) override;
        void LoadFromFile(const std::string &filePath);
    private:
        void Generate();
        void GenerateFace(FT_Library ftLibrary, FT_Face *face);
        void GenerateCharacters(FT_Library ftLibrary, const FT_Face &face);

        std::map<char, structs::TextCharacter> characters;

        char *fontData;
        size_t fontDataSize;

        FT_UInt fontSize;
    };
}

#endif //SENGINE_FONT_HPP
