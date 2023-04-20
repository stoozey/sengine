#include "managers/sound_manager.hpp"

namespace managers {
    SoundManager::SoundManager() {
        reservedSoundId = 0;
    }

    SoundId SoundManager::GetAvailableSoundId() {
        while (SoundExists(reservedSoundId)) {
            reservedSoundId++;
        }

        return reservedSoundId;
    }

    bool SoundManager::SoundExists(SoundId soundId) {
        auto find = sounds.find(soundId);
        return (find != sounds.end());
    }
}