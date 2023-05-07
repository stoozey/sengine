#ifndef SENGINE_TEST1_SOUND_HPP
#define SENGINE_TEST1_SOUND_HPP

#include "assets/asset.hpp"
#include "structs/assets/asset_info.hpp"

namespace assets {
    class Sound : public Asset {
    public:
        void Save(const std::string &filePath) override;
        void Load(const std::string &filePath) override;
    };
}

#endif //SENGINE_TEST1_SOUND_HPP
