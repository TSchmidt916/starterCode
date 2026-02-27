#pragma once
#include "shader.h"

class mirrorShader : public shader {
public:
    mirrorShader() : shader(vec3(1.0f, 1.0f, 1.0f)) {}
    
    vec3 ray_color(const hitRecord& rec, const light& pointLight, const hittableList& world, const vec3& backgroundColor, int depth) const override;

    bool shadow_ray(const hitRecord& rec, const light& pointLight, const hittableList& world) const override {
        return false;
    }
};