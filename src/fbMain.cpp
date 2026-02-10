#include "framebuffer.h"
#include "perspectiveCamera.h"
#include "sphere.h"
#include "triangle.h"

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

    Framebuffer fb4(800, 800);
    perspectiveCamera cam2(800, 800, vec3(0,0,0), vec3(0,0,-1), 1.0f, 2.0f, 2.0f);
    sphere sph(vec3(0,0,-2), 1.0f);
    for (int j = 0; j < 800; j++) {
        for (int i = 0; i < 800; i++) {
            ray R;
            float tmin = 0.001f;
            float tmax = std::numeric_limits<float>::infinity();
            cam2.generateRay(i, j, R);
            vec3 color;
            if (sph.intersect(R, tmin, tmax)) {
                color = vec3((R.direction().x() + 1.0f) / 2.0f, (R.direction().y() + 1.0f) / 2.0f, (R.direction().z() + 1.0f) / 2.0f);
            } else {
                color = vec3(0.5 , 0.0 , 1.0f);
            }
            fb4.setPixelColor(i, j, color);
        }
    }
    fb4.exportPNG("output_sphere.png");

    Framebuffer fb5(200, 200);
    perspectiveCamera cam3(200, 200, vec3(0,0,0), vec3(0,0,-1), 0.7f, 0.5f, 0.5f);
    sphere sph1(vec3(0,-1.25, -7), 0.3f);
    sphere sph2(vec3(0,0, -10), 3.0f);
    sphere sph3(vec3(0, 0, -15), 5.0f);
    for (int j = 0; j < 200; j++) {
        for (int i = 0; i < 200; i++) {
            ray R;
            float tmin = 0.001f;
            float tmax = std::numeric_limits<float>::infinity();
            cam3.generateRay(i, j, R);
            vec3 yellow = vec3(0.992, 0.863, 0.239);
            vec3 blue = vec3(0.149, 0.451, 0.698);
            vec3 background = vec3(0.5, 0.5, 0.5f);
            vec3 color = background;

            if (sph1.intersect(R, tmin, tmax)) {
                color = yellow;
            }
            if (sph2.intersect(R, tmin, tmax)) {
                color = blue;
            }
            if (sph3.intersect(R, tmin, tmax)) {
                color = yellow;
            }
            fb5.setPixelColor(i, j, color);
        }
    }
    fb5.exportPNG("output_multiple_spheres.png");

    Framebuffer fb6(200, 200);
    perspectiveCamera cam4(200, 200, vec3(0,0,0), vec3(0,0,-1), 1.0f, 0.5f, 0.5f);
    triangle tri1(vec3(-1.2, -0.2, -7), vec3(0.8, -0.5, -5), vec3(0.9, 0, -5));
    triangle tri2(vec3(0.773205, -0.93923, -7), vec3(0.0330127, 0.94282, -5), vec3(-0.45, 0.779423, -5));
    triangle tri3(vec3(0.426795, 1.13923, -7), vec3(-0.833013, -0.44282, -5), vec3(-0.45, -0.779423, -5));
    for (int j = 0; j < 200; j++) {
        for (int i = 0; i < 200; i++) {
            ray R;
            float tmin = 0.001f;
            float tmax = std::numeric_limits<float>::infinity();
            cam4.generateRay(i, j, R);
            vec3 red(1.0f, 0.0f, 0.0f);
            vec3 green(0.0f, 1.0f, 0.0f);
            vec3 blue(0.0f, 0.0f, 1.0f);
            vec3 background(0.5f, 0.5f, 0.5f);
            vec3 color = background;
            if (tri1.intersect(R, tmin, tmax)) {
                color = red;
            }
            if (tri2.intersect(R, tmin, tmax)) {
                color = green;
            }
            if (tri3.intersect(R, tmin, tmax)) {
                color = blue;
            }
            fb6.setPixelColor(i, j, color);
        }
    }
    fb6.exportPNG("output_triangles.png");

    Framebuffer fb7(200, 200);
    perspectiveCamera cam5(200, 200, vec3(0,0.2,3.5), vec3(0,0,-1), 1.0f, 0.5f, 0.5f);
    sphere sph4(vec3(0, 0, -2), 1.0f);
    //ears
    triangle tri4(vec3(-1, 0, -2), vec3(0, 1, -2), vec3(-0.9, 1.5, -2));
    triangle tri5(vec3(1, 0, -2), vec3(0, 1, -2), vec3(0.9, 1.5, -2));
    //eyes
    triangle tri6(vec3(-0.6, 0.05, -1), vec3(-0.3, 0.05, -1), vec3(-0.45, 0.3, -1));
    triangle tri7(vec3(0.6, 0.05, -1), vec3(0.3, 0.05, -1), vec3(0.45, 0.3, -1));
    //nose
    triangle tri8(vec3(0, 0.1, -1), vec3(-0.1, -0.1, -1), vec3(0.1, -0.1, -1));
    //mouth
    triangle tri9(vec3(-0.25, -0.25, -1), vec3(0.25, -0.25, -1), vec3(0, -0.35, -1));
    for (int j = 0; j < 200; j++) {
        for (int i = 0; i < 200; i++) {
            ray R;
            float tmin = 0.001f;
            float tmax = std::numeric_limits<float>::infinity();
            cam5.generateRay(i, j, R);
            vec3 white = vec3(1.0, 1.0, 1.0);
            vec3 black = vec3(0, 0, 0);
            vec3 background = vec3(0.5, 0.2, 0.5f);
            vec3 color = background;

            if (sph4.intersect(R, tmin, tmax) || tri4.intersect(R, tmin, tmax) || tri5.intersect(R, tmin, tmax)) {
                color = white;
            }
            if (tri6.intersect(R, tmin, tmax) || tri7.intersect(R, tmin, tmax) || tri8.intersect(R, tmin, tmax) || tri9.intersect(R, tmin, tmax)) {
                color = black;
            }
            fb5.setPixelColor(i, j, color);
        }
    }
    fb5.exportPNG("cat.png");

    return 0;
}