#include "sphere.h"

bool sphere::intersect(const ray& r, const float tmin, float& tmax) const {
    vec3 oc = center - r.origin();
    float a = dot(r.direction(), r.direction());
    float b = -2.0f * dot(r.direction(), oc);
    float c = dot(oc, oc) - radius * radius;
    float discriminant = b * b - 4 * a * c;
    if (discriminant < 0) {
        return false;
    } else {
        float sqrt_disc = std::sqrt(discriminant);
        float root = (-b - sqrt_disc) / (2.0f * a);
        if (root < tmin || root > tmax) {
            root = (-b + sqrt_disc) / (2.0f * a);
            if (root < tmin || root > tmax) {
                return false;
            }
        }
        tmax = root;
        return true;
    }
}