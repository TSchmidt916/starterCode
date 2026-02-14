#pragma once
#include "shader.h"

class normalShader : public shader {
public:
    normalShader() : shader(vec3(1.0f, 1.0f, 1.0f)) {}
    
    vec3 ray_color(const hitRecord& rec, const light& pointLight) const override;
};