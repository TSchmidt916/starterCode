#pragma once
#include "shape.h"
#include "shader.h"

class sphere : public shape {
    public:
    sphere() : center(vec3(0.0f, 0.0f, 0.0f)), radius(1.0f) {}
    sphere(const vec3& cen, float r,  std::shared_ptr<shader> mat) : center(cen), radius(r), mat_ptr(mat) {}
    virtual ~sphere() {}

    virtual bool intersect(const ray& r, const float tmin, float& tmax, hitRecord& rec) const override;

    private:
    vec3 center;
    float radius;
    std::shared_ptr<shader> mat_ptr;
};