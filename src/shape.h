#pragma once
#include "ray.h"

class shape {
    public:
    shape() {}
    virtual ~shape() {}

    virtual bool intersect(const ray& r, const float tmin, float &tmax) const = 0;
};