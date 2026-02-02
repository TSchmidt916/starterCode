#pragma once

#include "ray.h"

class camera {
    public:
    camera(int pixel_nx, int pixel_ny)  : pos(10.0, 2.0, 13.0), dir(60, -8, 80), focal_length(0.8f), 
    imageplane_width(0.5f), imageplane_height(0.5f), nx(pixel_nx), ny(pixel_ny) {
        normalizeDir();
    }
    virtual ~camera() {}

    virtual void generateRay(int i, int j, ray &R) = 0;

    protected:
    vec3 pos, dir;
    vec3 U, V, W;
    vec3 up = vec3(0, 1, 0);
    float focal_length;
    int nx, ny;
    float imageplane_width;
    float imageplane_height;
    float l = -imageplane_width / 2.0f;
    float r = imageplane_width / 2.0f;
    float b = imageplane_height / 2.0f;
    float t = -imageplane_height / 2.0f;

    void normalizeDir() {
        W = unit_vector(-dir);
        U = unit_vector(cross(up, W));
        V = cross(W, U);
    }
};

