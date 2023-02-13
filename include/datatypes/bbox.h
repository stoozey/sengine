#ifndef SENGINE_BBOX_H
#define SENGINE_BBOX_H

#include <math.h>

struct BBox {
    float x1;
    float y1;
    float x2;
    float y2;

    float GetXMin() {
        return std::min(x1, x2);
    }

    float GetXMax() {
        return std::max(x1, x2);
    }

    float GetYMin() {
        return std::min(y1, y2);
    }

    float GetYMax() {
        return std::max(y1, y2);
    }

    float GetWidth() {
        return (GetXMax() - GetXMin());
    }

    float GetHeight() {
        return (GetYMax() - GetYMin());
    }
};

#endif //SENGINE_BBOX_H
