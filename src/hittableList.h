#pragma once

#include "shape.h"
#include <memory>
#include <vector>

class hittableList : public shape {
    public:
    std::vector<std::shared_ptr<shape>> objects;

    hittableList() {}
    hittableList(std::shared_ptr<shape> object) { add(object); }

    void clear() { objects.clear(); }

    void add(std::shared_ptr<shape> object) { objects.push_back(object); }

    virtual bool intersect(const ray& r, const float tmin, float& tmax, hitRecord& rec) const override {
        hitRecord temp_rec;
        bool hit_anything = false;
        float closest_so_far = tmax;

        for (const auto& object : objects) {
            if (object->intersect(r, tmin, closest_so_far, temp_rec)) {
                hit_anything = true;
                closest_so_far = temp_rec.t;
                rec = temp_rec;
            }
        }

        return hit_anything;
    }
};