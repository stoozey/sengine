#ifndef SENGINE_ASSET_INFO_HPP
#define SENGINE_ASSET_INFO_HPP

#include <crossguid/guid.hpp>
#include <cstring>
#include <algorithm>

#include "enums/asset_type.hpp"
#include "core/log.hpp"

extern const size_t ASSET_INFO_BYTES;
extern const char *ASSET_INFO_SIGNATURE;
extern const unsigned short ASSET_INFO_VERSION;

typedef std::array<unsigned char, 16> AssetInfoGuid;

namespace structs {
    struct AssetInfo {
        enums::AssetType assetType;
        AssetInfoGuid guid;

        xg::Guid GetGuid() {
            return xg::Guid(guid);
        }

        void ToBytes(char *out) {
            char* currentPtr = &out[0];
            char *clearEnd = (currentPtr + ASSET_INFO_BYTES);
            std::fill(currentPtr, clearEnd, 0);

            std::strcpy(currentPtr, ASSET_INFO_SIGNATURE);
            currentPtr += std::strlen(ASSET_INFO_SIGNATURE);

            std::memcpy(currentPtr, &ASSET_INFO_VERSION, sizeof(ASSET_INFO_VERSION));
            currentPtr += sizeof(ASSET_INFO_VERSION);

            std::memcpy(currentPtr, reinterpret_cast<char *>(this), sizeof(AssetInfo));
        }

        static structs::AssetInfo FromBytes(char *bytes) {
            char *currentPtr = &bytes[0];
            size_t signatureSize = std::strlen(ASSET_INFO_SIGNATURE);
            char *signatureArray = new char[signatureSize];
            std::memcpy(&signatureArray[0], bytes, signatureSize);
            currentPtr += signatureSize;

            char *compSignature = new char[signatureSize + 1];
            std::memcpy(compSignature, signatureArray, signatureSize);
            compSignature[signatureSize] = '\0';
            if (std::strcmp(compSignature, ASSET_INFO_SIGNATURE) != 0) core::Log::Error(fmt::format("invalid file signature (got {}, expected {})", compSignature, ASSET_INFO_SIGNATURE));

            delete[] signatureArray;
            delete[] compSignature;

            size_t versionSize = sizeof(ASSET_INFO_VERSION);
            unsigned short version;
            std::memcpy(&version, currentPtr, versionSize);
            currentPtr += versionSize;

            enums::AssetType assetType;
            AssetInfoGuid guid;
            switch (version) {
                case 1: {
                    size_t assetTypeSize = sizeof(enums::AssetType);
                    std::memcpy(&assetType, currentPtr, assetTypeSize);
                    currentPtr += assetTypeSize;

                    size_t guidSize = sizeof(AssetInfoGuid);
                    std::memcpy(&guid, currentPtr, guidSize);
                    currentPtr += guidSize;
                    break;
                }

                default: {
                    core::Log::Error(fmt::format("unsupported AssetInfo version \"{}\"", version));
                }
            }

            return { assetType, guid };
        }
    };
}

#endif //SENGINE_ASSET_INFO_HPP
