#pragma once

#include "ray.h"

class camera {
    public:
    camera(int pixel_nx, int pixel_ny)  : pos(0,0,0), U(1,0,0), V(0,1,0), W(0,0,1), focal_length(1.0f), 
    imageplane_width(0.5f), imageplane_height(0.5f), nx(pixel_nx), ny(pixel_ny) {}

    virtual ~camera() {}

    virtual void generateRay(int i, int j, ray &R) = 0;

    protected:
    vec3 pos;
    vec3 U, V, W;
    float focal_length;
    float imageplane_width;
    float imageplane_height;
    int nx, ny;
    float l = -imageplane_width / 2.0f;
    float r = imageplane_width / 2.0f;
    float b = -imageplane_height / 2.0f;
    float t = imageplane_height / 2.0f;
};

