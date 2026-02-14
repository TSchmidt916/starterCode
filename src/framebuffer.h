#pragma once

#include <vector>

#include "vec3.h"

class Framebuffer {
    public:
    Framebuffer();
    Framebuffer(int w, int h);

    int width() const { return m_width; }
    int height() const { return m_height; }

    void clearToColor(vec3 c);
    void clearToColor(vec3 c1, vec3 c2); // overload for gradient clear

    void setPixelColor(int i, int j, vec3 c);

    void exportPNG(std::string filename);

    private:
    int m_width, m_height;
    std::vector<vec3> fbStorage;
};