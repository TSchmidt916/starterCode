#pragma once
#include <memory>
#include <vector>
#include <string>
#include <unordered_map>
#include <array>
#include <iostream>

// ─────────────────────────────────────────────
//  LIGHTS
// ─────────────────────────────────────────────
class Light {
public:
    std::string type;
    virtual ~Light() = default;
};

class PointLight : public Light {
public:
    std::array<float,3> position  = {0,0,0};
    std::array<float,3> intensity = {1,1,1};
    PointLight() { type = "Point Light"; }
};

class AreaLight : public Light {
public:
    std::array<float,3> position = {0,0,0};
    std::array<float,3> color    = {1,1,1};
    std::array<float,3> normal   = {0,1,0};
    float width  = 1.0f;
    float length = 1.0f;
    AreaLight() { type = "Area Light"; }
};

// ─────────────────────────────────────────────
//  SHADERS / MATERIALS
// ─────────────────────────────────────────────
class Shader {
public:
    std::string name;
    std::string type;                               // "Phong", "Lambert", "Mirror", ...
    std::array<float,3> diffuse   = {0.8f,0.8f,0.8f};
    std::array<float,3> specular  = {0.0f,0.0f,0.0f};
    std::array<float,3> ambient   = {0.0f,0.0f,0.0f};
    float shininess  = 32.0f;   // phongExp
    float ior        = 1.0f;    // refractiveIndex
    float mirrorCoef = 0.0f;
    float roughness  = 0.0f;
};

// ─────────────────────────────────────────────
//  SHAPES
// ─────────────────────────────────────────────
class Shape {
public:
    std::string type;
    std::string name;
    std::shared_ptr<Shader> shader;
    virtual ~Shape() = default;
};

class Sphere : public Shape {
public:
    std::array<float,3> center = {0,0,0};
    float radius = 1.0f;
    Sphere() { type = "sphere"; }
};

class Triangle : public Shape {
public:
    std::array<float,3> v0 = {0,0,0};
    std::array<float,3> v1 = {1,0,0};
    std::array<float,3> v2 = {0,1,0};
    Triangle() { type = "triangle"; }
};

class Plane : public Shape {
public:
    std::array<float,3> point  = {0,0,0};
    std::array<float,3> normal = {0,1,0};
    Plane() { type = "plane"; }
};

class Box : public Shape {
public:
    std::array<float,3> minPt = {-0.5f,-0.5f,-0.5f};
    std::array<float,3> maxPt = { 0.5f, 0.5f, 0.5f};
    Box() { type = "box"; }
};

// ─────────────────────────────────────────────
//  CAMERA
// ─────────────────────────────────────────────
class Camera {
public:
    std::string name;
    std::string type;
    std::array<float,3> position  = {0, 0, 5};
    std::array<float,3> viewDir   = {0, 0,-1};
    float focalLength     = 1.0f;
    float imagePlaneWidth = 1.0f;
};

// ─────────────────────────────────────────────
//  SCENE CONTAINER
// ─────────────────────────────────────────────
class SceneContainer {
    friend class SceneLoader;

private:
    std::vector<std::shared_ptr<Light>>   lights;
    std::vector<std::shared_ptr<Shape>>   shapes;
    std::vector<std::shared_ptr<Camera>>  cameras;

    // Keyed by shader name — populated by SceneLoader before shapes are added
    std::unordered_map<std::string, std::shared_ptr<Shader>> shaders;

public:
    SceneContainer() = default;

    // ── Accessors for your renderer ───────────────────────────────────────
    const std::vector<std::shared_ptr<Light>>&  getLights()  const { return lights;  }
    const std::vector<std::shared_ptr<Shape>>&  getShapes()  const { return shapes;  }
    const std::vector<std::shared_ptr<Camera>>& getCameras() const { return cameras; }

    std::shared_ptr<Camera> getCamera() const {
        return cameras.empty() ? nullptr : cameras[0];
    }

    std::shared_ptr<Shader> findShader(const std::string& name) const {
        auto it = shaders.find(name);
        return (it != shaders.end()) ? it->second : nullptr;
    }

    void debugPrint() const {
        std::cout << "=== Scene Summary ===\n"
                  << "  cameras : " << cameras.size() << "\n"
                  << "  lights  : " << lights.size()  << "\n"
                  << "  shapes  : " << shapes.size()  << "\n"
                  << "  shaders : " << shaders.size() << "\n";
    }
};