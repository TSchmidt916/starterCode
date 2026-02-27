#pragma once
#include "perspectiveCamera.h"
#include "light.h"

#include "framebuffer.h"
#include "hittableList.h"
#include "hitRecord.h"
#include <string>
#include <random>

class scene {
    public:
    scene(Framebuffer* fb, perspectiveCamera* cam, hittableList* list, light* l, std::string outputName, vec3 backgroundColor) : fb(fb), cam(cam), list(list), l(l), backgroundColor(backgroundColor), outputName(outputName) {}
    ~scene() {}

    float randomOffset() {
        static std::uniform_real_distribution<float> distribution(0.0f, 1.0f);
        static std::mt19937 generator;
        return distribution(generator);
    }

    vec3 getBackgroundColor() const {
        return backgroundColor;
    }

    void generateScene() {
        float rpp_NSquare = 4;

        for (int x = 0; x < fb->width(); x++) {
            for (int y = 0; y < fb->height(); y++) {
                
                vec3 color = vec3(0.0f, 0.0f, 0.0f);

                for (int p = 0; p < rpp_NSquare; p++) {
                    for (int q = 0; q < rpp_NSquare; q++) {

                        float tmin = 0.001f;
                        float tmax = std::numeric_limits<float>::infinity();

                        float pOffset = (p + randomOffset()) / rpp_NSquare;
                        float qOffset = (q + randomOffset()) / rpp_NSquare;
                        
                        ray R  = cam->generateRay( x + pOffset, y + qOffset, R);
                        hitRecord rec;
                        vec3 rayColor = backgroundColor;
                        if (list->intersect(R, tmin, tmax, rec)) {
                            rayColor = rec.mat_ptr->ray_color(rec, *l, *list, backgroundColor, 5);
                            bool shadow = rec.mat_ptr->shadow_ray(rec, *l, *list);
                            if (shadow == true) {
                                rayColor = vec3(0.0f, 0.0f, 0.0f);
                            }
                        }
                        color += rayColor;
                    }
                }
                color = color / (rpp_NSquare * rpp_NSquare);

                fb->setPixelColor(x, y, color);
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
    vec3 backgroundColor;
};