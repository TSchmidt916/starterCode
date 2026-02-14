#include "triangle.h"

bool triangle::intersect(const ray&r, float tmin, float &tmax, hitRecord& rec) const {
    float a = vertex_a[0] - vertex_b[0];
    float b = vertex_a[1] - vertex_b[1];
    float c = vertex_a[2] - vertex_b[2];

    float d = vertex_a[0] - vertex_c[0];
    float e = vertex_a[1] - vertex_c[1];
    float f = vertex_a[2] - vertex_c[2];

    float g = r.direction()[0];
    float h = r.direction()[1];
    float i = r.direction()[2];

    float j = vertex_a[0] - r.origin()[0];
    float k = vertex_a[1] - r.origin()[1];
    float l = vertex_a[2] - r.origin()[2];

    float ei_minus_hf = e * i - h * f;
    float gf_minus_di = g * f - d * i;
    float dh_minus_eg = d * h - e * g;

    float M = a * ei_minus_hf + b * gf_minus_di + c * dh_minus_eg;

    float t = -1.0, gamma = -1.0, beta = -1.0; 

    if (M != 0.0) {
        t = -(f * (a * k - j * b) + e * (j * c - a * l) + d * (b * l - k * c)) / M;
        if (t < tmin || t > tmax)
            return false;

        gamma = (i * (a * k - j * b) + h * (j * c - a * l) + g * (b * l - k * c)) / M;
        if (gamma < 0.0 || gamma > 1.0)
            return false;

        beta = (j * ei_minus_hf + k * gf_minus_di + l * dh_minus_eg) / M;
        if (beta < 0.0 || beta > 1.0 - gamma)
            return false;
    }

    tmax = t;
    rec.t = t;
    rec.p = r.at(rec.t);
    vec3 u = vertex_b - vertex_a;
    vec3 v = vertex_c - vertex_a;
    vec3 outward_normal = unit_vector(cross(u, v));
    rec.set_face_normal(r, outward_normal);

    return true;
}