#pragma once
#include "perspectiveCamera.h"
#include "light.h"

#include "framebuffer.h"
#include "hittableList.h"
#include "hitRecord.h"
#include <string>

class scene {
    public:
    scene(Framebuffer* fb, perspectiveCamera* cam, hittableList* list, light* l, std::string outputName) : fb(fb), cam(cam), list(list), l(l), outputName(outputName) {}
    ~scene() {}

    void generateScene(vec3 backgroundColor) {
        for (int j = 0; j < fb->height(); j++) {
            for (int i = 0; i < fb->width(); i++) {
                ray R;
                cam->generateRay(i, j, R);
                vec3 color = backgroundColor;
                hitRecord rec;
                float tmax = std::numeric_limits<float>::infinity();
                float tmin = 0.001f;

                if (list->intersect(R, tmin, tmax, rec)) {
                    color = rec.mat_ptr->ray_color(rec, *l);
                }
                fb->setPixelColor(i, j, color);
            }
        }
        fb->exportPNG(outputName);
    }

    private:
    Framebuffer* fb;
    perspectiveCamera* cam;
    hittableList* list;
    light* l;
    std::string outputName;
};