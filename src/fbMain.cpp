#include "framebuffer.h"

int main(int argc, char *argv[])
{
    Framebuffer fb1;
    fb1.clearToColor(vec3(0.5, 0.0, 1.0));
    fb1.exportPNG("output.png");

    Framebuffer fb2;
    fb2.clearToColor(vec3(1.0, 0.0, 0.0), vec3(0.0, 0.0, 1.0));
    fb2.exportPNG("output_gradient.png");

    return 0;
}