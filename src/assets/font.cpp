//#include <fstream>
//#include <glm/glm.hpp>
//#include <ft2build.h>
//#include FT_FREETYPE_H
//
//#include "assets/font.hpp"
//#include "core/log.hpp"
//#include "structs/assets/asset_type.hpp"
//#include "utils/file_util.hpp"
//
//namespace assets {
//    Font::Font() : Asset(structs::AssetType::Font) {
//        fontSize = 64;
//
//        fontDataSize = 0;
//        fontData = nullptr;
//    }
//
//    void Font::LoadFromFile(const std::string &filePath) {
//        fontDataSize = utils::FileReadAllBytes(filePath, &fontData);
//        Generate();
//    }
//
//    void Font::Generate() {
//        FT_Library ftLibrary;
//        if (FT_Init_FreeType(&ftLibrary)) core::Log::Critical("Could not init FreeType Library");
//
//        FT_Face face;
//        GenerateFace(ftLibrary, &face);
//        GenerateCharacters(ftLibrary, face);
//
//        FT_Done_Face(face);
//        FT_Done_FreeType(ftLibrary);
//    }
//
//    void Font::GenerateFace(FT_Library ftLibrary, FT_Face *face) {
//        int result = FT_New_Memory_Face(ftLibrary, reinterpret_cast<FT_Byte *>(&fontData), static_cast<FT_Long>(fontDataSize), 0, face);
//        if (result == 0) return;
//
//        core::Log::Error("failed to load face for font {}", assetInfo.GetGuid().str());
//    }
//
//    void Font::GenerateCharacters(FT_Library ftLibrary, const FT_Face &face) {
//        characters.clear();
//
//        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
//        FT_Set_Pixel_Sizes(face, 0, fontSize);
//        for (unsigned char c = 0; c < 128; c++) {
//            // load character glyph
//            if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
//                core::Log::Warn("failed to load glyph {} for font {}", c, assetInfo.GetGuid().str());
//                continue;
//            }
//
//            // generate texture
//            GLuint texture;
//            glGenTextures(1, &texture);
//            glBindTexture(GL_TEXTURE_2D, texture);
//            glTexImage2D(
//                    GL_TEXTURE_2D,
//                    0,
//                    GL_RED,
//                    face->glyph->bitmap.width,
//                    face->glyph->bitmap.rows,
//                    0,
//                    GL_RED,
//                    GL_UNSIGNED_BYTE,
//                    face->glyph->bitmap.buffer
//            );
//
//            // set texture options
//            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
//            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
//            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//
//            // now store character for later use
//            structs::TextCharacter character{
//                    texture,
//                    face->glyph->advance.x,
//                    glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
//                    glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top)
//            };
//
//            characters.insert(std::pair<char, structs::TextCharacter>(c, character));
//        }
//    }
//}