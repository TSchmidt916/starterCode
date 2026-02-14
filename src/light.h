#pragma once 
#include "vec3.h"

class light {
    public:
    vec3 position;
    vec3 color;

    light(const vec3& pos, const vec3& color) : position(pos), color(color) {}
};