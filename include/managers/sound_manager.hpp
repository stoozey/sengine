#ifndef SENGINE_TEST1_SOUND_MANAGER_HPP
#define SENGINE_TEST1_SOUND_MANAGER_HPP

#include <map>
#include <utility>

#include "managers/manager.hpp"
#include "assets/sound.hpp"

typedef unsigned short SoundId;

namespace managers {
    class SoundManager : public Manager {
    public:
        SoundManager();

        SoundId Play(std::weak_ptr<assets::Sound> sound);

    private:
        SoundId GetAvailableSoundId();

        bool SoundExists(SoundId soundId);

        SoundId reservedSoundId;
        std::map<SoundId, std::weak_ptr<assets::Sound>> sounds;
    };
}

#endif //SENGINE_TEST1_SOUND_MANAGER_HPP
