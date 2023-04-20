#ifndef SENGINE_TEST1_SOUND_MANAGER_HPP
#define SENGINE_TEST1_SOUND_MANAGER_HPP

#include <map>
#include <utility>

#include "assets/sound.hpp"

typedef unsigned short SoundId;

namespace managers {
    class SoundManager {
    public:
        SoundManager();

        SoundId Play(std::shared_ptr<assets::Sound> sound);

    private:
        SoundId GetAvailableSoundId();

        bool SoundExists(SoundId soundId);

        SoundId reservedSoundId;
        std::map<SoundId, std::shared_ptr<assets::Sound>> sounds;
    };
}

#endif //SENGINE_TEST1_SOUND_MANAGER_HPP
