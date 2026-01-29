#include "framebuffer.h"
#include "perspectiveCamera.h"

int main(int argc, char *argv[])
{
    Framebuffer fb1;
    fb1.clearToColor(vec3(0.5, 0.0, 1.0));
    fb1.exportPNG("output.png");

    Framebuffer fb2;
    fb2.clearToColor(vec3(1.0, 0.0, 0.0), vec3(0.0, 0.0, 1.0));
    fb2.exportPNG("output_gradient.png");

    Framebuffer fb3(800, 800);
    perspectiveCamera cam1(800, 800);
    for (int j = 0; j < 800; j++) {
        for (int i = 0; i < 800; i++) {
            ray R;
            cam1.generateRay(i, j, R);
            vec3 color = vec3((R.direction().x() + 1.0f) / 2.0f, (R.direction().y() + 1.0f) / 2.0f, (R.direction().z() + 1.0f) / 2.0f);
            fb3.setPixelColor(i, j, color);
        }
    }

    fb3.exportPNG("output_camera.png");
    return 0;
}