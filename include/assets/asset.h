#ifndef SENGINE_ASSET_H
#define SENGINE_ASSET_H

#include <string>
#include <map>

#include "datatypes/asset_path.h"

class Asset {
public:
    virtual void Load(const std::string& filePath) = 0;
};

#endif //SENGINE_ASSET_H
