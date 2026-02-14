#pragma once
#include "ray.h"
#include "hitRecord.h"

class shape {
    public:
    shape() {}
    virtual ~shape() {}

    virtual bool intersect(const ray& r, const float tmin, float &tmax, hitRecord& rec) const = 0;
};