#ifndef SENGINE_ASSET_H
#define SENGINE_ASSET_H

#include <string>
#include <map>

#include "datatypes/asset_path.h"

class Asset {
public:
    virtual void Load(std::string path) = 0;
    virtual void UnLoad() = 0;
};

#endif //SENGINE_ASSET_H
