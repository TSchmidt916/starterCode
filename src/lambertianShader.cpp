#include "lambertianShader.h"

vec3 lambertian::ray_color(const hitRecord& rec, const light& pointLight) const {
    vec3 light_dir = unit_vector(pointLight.position - rec.p);
    float diffuse = std::max(0.0f, dot(rec.normal, light_dir));

    float ambient = 0.3f;
    float lighting = ambient + (1 - ambient) * diffuse;
    
    return base_color * pointLight.color * lighting;
}