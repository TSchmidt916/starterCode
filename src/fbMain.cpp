#include "framebuffer.h"
#include "perspectiveCamera.h"
#include "sphere.h"

int main(int argc, char *argv[])
{
    Framebuffer fb1;
    fb1.clearToColor(vec3(0.5, 0.0, 1.0));
    fb1.exportPNG("output.png");

    Framebuffer fb2;
    fb2.clearToColor(vec3(1.0, 0.0, 0.0), vec3(0.0, 0.0, 1.0));
    fb2.exportPNG("output_gradient.png");

    Framebuffer fb3(200, 200);
    perspectiveCamera cam1(200, 200);
    for (int j = 0; j < 200; j++) {
        for (int i = 0; i < 200; i++) {
            ray R;
            cam1.generateRay(i, j, R);
            vec3 color = vec3((R.direction().x() + 1.0f) / 2.0f, (R.direction().y() + 1.0f) / 2.0f, (R.direction().z() + 1.0f) / 2.0f);
            fb3.setPixelColor(i, j, color);
        }
    }

    fb3.exportPNG("output_camera.png");

    Framebuffer fb4(200, 200);
    perspectiveCamera cam2(200, 200, vec3(0,0,0), vec3(0,0,-1), 1.0f, 2.0f, 2.0f);
    sphere sph(vec3(0,0,-2), 1.0f);
    for (int j = 0; j < 200; j++) {
        for (int i = 0; i < 200; i++) {
            ray R;
            cam2.generateRay(i, j, R);
            vec3 color;
            if (sph.intersect(R)) {
                color = vec3((R.direction().x() + 1.0f) / 2.0f, (R.direction().y() + 1.0f) / 2.0f, (R.direction().z() + 1.0f) / 2.0f);
            } else {
                color = vec3(0,0,0); // Black for miss
            }
            fb4.setPixelColor(i, j, color);
        }
    }
    fb4.exportPNG("output_sphere.png");

    return 0;
}