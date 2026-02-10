#include "triangle.h"

bool triangle::intersect(const ray&r, float tmin, float &tmax) const {
    double a = vertex_a[0] - vertex_b[0];
    double b = vertex_a[1] - vertex_b[1];
    double c = vertex_a[2] - vertex_b[2];

    double d = vertex_a[0] - vertex_c[0];
    double e = vertex_a[1] - vertex_c[1];
    double f = vertex_a[2] - vertex_c[2];

    double g = r.direction()[0];
    double h = r.direction()[1];
    double i = r.direction()[2];

    double j = vertex_a[0] - r.origin()[0];
    double k = vertex_a[1] - r.origin()[1];
    double l = vertex_a[2] - r.origin()[2];

    double ei_minus_hf = e * i - h * f;
    double gf_minus_di = g * f - d * i;
    double dh_minus_eg = d * h - e * g;

    double M = a * ei_minus_hf + b * gf_minus_di + c * dh_minus_eg;

    double t = -1.0, gamma = -1.0, beta = -1.0; 

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
    return true;
}