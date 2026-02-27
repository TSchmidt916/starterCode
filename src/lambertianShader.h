#pragma once 
#include "shader.h"
#include "hitRecord.h"
#include "light.h"

class lambertian : public shader {
    public:
    lambertian(const vec3& color) : shader(color) {}

    vec3 ray_color(const hitRecord& rec, const light& pointLight, const hittableList& world, const vec3& backgroundColor, int depth) const override;

    bool shadow_ray(const hitRecord& rec, const light& pointLight, const hittableList& world) const override;
};