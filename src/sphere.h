#pragma once
#include "shape.h"

class sphere : public shape {
    public:
    sphere(const vec3& cen, float r) : center(cen), radius(r) {}
    virtual ~sphere() {}

    virtual bool intersect(const ray& r) const override {
        vec3 oc = center - r.origin();
        float a = dot(r.direction(), r.direction());
        float b = -2.0f * dot(r.direction(), oc);
        float c = dot(oc, oc) - radius * radius;
        float discriminant = b * b - 4 * a * c;
        return (discriminant >= 0);
    }

    private:
    vec3 center;
    float radius;
};