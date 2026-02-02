#pragma once

#include "camera.h"
#include "ray.h"

class perspectiveCamera : public camera
{
    public:
    perspectiveCamera(int pixel_nx, int pixel_ny) : camera(pixel_nx, pixel_ny) {}

    void generateRay(int i, int j, ray &R) override {
        float u, v;

        u = l + (r-l) * (i+0.5)/(float)nx;
        v = b + (t-b) * (j+0.5)/(float)ny;
        vec3 dir = u*U + v*V + focal_length*(-W);
        R = ray(pos, unit_vector(dir));
    }
};