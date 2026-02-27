#include "mirrorShader.h"
#include "hitRecord.h"
#include "light.h"


vec3 mirrorShader::ray_color(const hitRecord& rec, const light& pointLight, const hittableList& world, const vec3& backgroundColor, int depth) const {
    if (depth <= 0) {
        return backgroundColor;
    }

    vec3 reflected_dir = rec.incoming_ray.direction() - 2 * dot(rec.incoming_ray.direction(), rec.normal) * rec.normal;
    ray reflected_ray(rec.p + 0.001f * rec.normal, unit_vector(reflected_dir));
    
    hitRecord reflected_rec;
    float max_distance = std::numeric_limits<float>::infinity();
    if (world.intersect(reflected_ray, 0.001f, max_distance, reflected_rec)) {
        return reflected_rec.mat_ptr->ray_color(reflected_rec, pointLight, world, backgroundColor, depth - 1);
    } else {
        return backgroundColor;
    }
}