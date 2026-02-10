#pragma once
#include "shape.h"

class sphere : public shape {
    public:
    sphere() : center(vec3(0.0f, 0.0f, 0.0f)), radius(1.0f) {}
    sphere(const vec3& cen, float r) : center(cen), radius(r) {}
    virtual ~sphere() {}

    virtual bool intersect(const ray& r, const float tmin, float& tmax) const override;

    private:
    vec3 center;
    float radius;
};