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
    ray incoming_ray;
    std::shared_ptr<shader> mat_ptr;
    vec3 base_color;

    void set_face_normal(const ray& r, const vec3& outward_normal) {
        incoming_ray = r;
        bool front_face = dot(r.direction(), outward_normal) < 0;
        normal = front_face ? outward_normal : -outward_normal;
    }
};