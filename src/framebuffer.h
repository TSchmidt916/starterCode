#pragma once

#include <vector>

#include "vec3.h"
//pixel colors, clear function, export PNG

class Framebuffer {
    public:
    Framebuffer();

    Framebuffer(int w, int h);

    void clearToColor(vec3 c);
    void clearToColor(vec3 c1, vec3 c2); // overload for gradient clear

    void setPixelColor(int i, int j, vec3 c);

    void exportPNG(std::string filename);

    private:
    int width, height;
    std::vector<vec3> fbStorage;
};