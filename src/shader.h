#pragma once
#include "ray.h"
#include "light.h"
#include "vec3.h"
#include "hittableList.h"

class hitRecord;

class shader {
    protected:
    vec3 base_color;

    public:
    shader(const vec3& color) :  base_color(color) {}

    virtual ~shader() = default;

    virtual vec3 ray_color(const hitRecord& rec, const light& pointLight, const hittableList& world, const vec3& backgroundColor, int depth) const = 0;

    vec3 getBaseColor() const {
        return base_color;
    }
};