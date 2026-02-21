#include "lambertianShader.h"
#include <algorithm>

vec3 lambertian::ray_color(const hitRecord& rec, const light& pointLight, const hittableList& world, const vec3& backgroundColor, int depth) const {
    vec3 light_dir = unit_vector(pointLight.position - rec.p);
    float diffuse = std::max(0.0f, dot(rec.normal, light_dir));

    float ambient = 0.3f;
    float lighting = ambient + (1 - ambient) * diffuse;
    
    return clamp(base_color * pointLight.color * lighting, 0.0f, 1.0f);
}