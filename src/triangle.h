#pragma once

#include "shape.h"

class triangle : public shape {
public:
    triangle() : vertex_a(0.0, 0.0, 0.0), vertex_b(1.0, 0.0, 0.0), vertex_c(0.0, 1.0, 0.0) {}
    triangle(const vec3& v0, const vec3& v1, const vec3& v2) : vertex_a(v0), vertex_b(v1), vertex_c(v2) {}

    virtual bool intersect(const ray& r, const float tmin, float& tmax) const override;

private:
    vec3 vertex_a, vertex_b, vertex_c;
};