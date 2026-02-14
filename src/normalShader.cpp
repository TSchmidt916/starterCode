#include "normalShader.h"
#include "hitRecord.h"
#include "light.h"

vec3 normalShader::ray_color(const hitRecord& rec, const light& pointLight) const {
    // Map normal components from [-1, 1] to [0, 1] for RGB color
    return 0.5f * (rec.normal + vec3(1.0f, 1.0f, 1.0f));
}