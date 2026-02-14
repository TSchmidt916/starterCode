#pragma once
#include "vec3.h"
#include "ray.h"
#include <memory>

class shader;

class hitRecord {
    public:
    point3 p;
    vec3 normal;
    float t;
    std::shared_ptr<shader> mat_ptr;

    void set_face_normal(const ray& r, const vec3& outward_normal) {
        bool front_face = dot(r.direction(), outward_normal) < 0;
        normal = front_face ? outward_normal : -outward_normal;
    }
};