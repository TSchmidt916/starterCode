#pragma once
#include "ISceneLoader.h"
#include "SceneContainer.h"

#include <iostream>
#include <memory>
#include <string>

class SceneLoader : public ISceneLoader {
private:
    SceneContainer &m_targetScene;

public:
    int numShaders;
    int numTextures;

    SceneLoader(SceneContainer &sceneToPopulate)
        : m_targetScene(sceneToPopulate), numShaders(0), numTextures(0) {}

    // ── Reserve hints ────────────────────────────────────────────────────
    void reserveCameras(size_t count)  override { m_targetScene.cameras.reserve(count); }
    void reserveLights(size_t count)   override { m_targetScene.lights.reserve(count);  }
    void reserveShapes(size_t count)   override { m_targetScene.shapes.reserve(count);  }
    void reserveShaders(size_t count)  override {
        numShaders = static_cast<int>(count);
        m_targetScene.shaders.reserve(count);
    }
    void reserveTextures(size_t count) override { numTextures = static_cast<int>(count); }

    // ── Scene params ─────────────────────────────────────────────────────
    void setSceneParams(const SceneParams &sparams) override {
        std::cout << "Setting scene params." << std::endl;
    }

    // ── CAMERA ───────────────────────────────────────────────────────────
    void addCamera(const std::string &name, const std::string &type,
                   const ISceneLoader::vec &pos,
                   const ISceneLoader::vec &viewDir,
                   float focalLength, float imagePlaneWidth) override
    {
        std::cout << "Creating camera: " << name << ", type: " << type << std::endl;

        auto cam             = std::make_shared<Camera>();
        cam->name            = name;
        cam->type            = type;
        cam->position        = { pos.x,     pos.y,     pos.z     };
        cam->viewDir         = { viewDir.x,  viewDir.y,  viewDir.z };
        cam->focalLength     = focalLength;
        cam->imagePlaneWidth = imagePlaneWidth;

        m_targetScene.cameras.push_back(cam);
    }

    // ── LIGHTS ───────────────────────────────────────────────────────────
    void addPointLight(const ISceneLoader::vec &pos,
                       const ISceneLoader::vec &intensity) override
    {
        std::cout << "Creating point light at ("
                  << pos.x << ", " << pos.y << ", " << pos.z << ")" << std::endl;

        auto light       = std::make_shared<PointLight>();
        light->position  = { pos.x,       pos.y,       pos.z       };
        light->intensity = { intensity.x,  intensity.y,  intensity.z };

        m_targetScene.lights.push_back(light);
    }

    void addAreaLight(const ISceneLoader::vec &pos,
                      const ISceneLoader::vec &color,
                      const ISceneLoader::vec &normal,
                      float width, float length) override
    {
        std::cout << "Creating area light." << std::endl;

        auto light      = std::make_shared<AreaLight>();
        light->position = { pos.x,    pos.y,    pos.z    };
        light->color    = { color.x,  color.y,  color.z  };
        light->normal   = { normal.x, normal.y, normal.z };
        light->width    = width;
        light->length   = length;

        m_targetScene.lights.push_back(light);
    }

    // ── SHADERS ──────────────────────────────────────────────────────────
    // ShaderDesc fields (from ISceneLoader.h):
    //   sd.name, sd.type
    //   sd.diffuse.data.x/y/z   sd.diffuse.textureName   sd.diffuse.hasTexture
    //   sd.specular.data.x/y/z
    //   sd.phongExp, sd.mirrorCoef, sd.roughness
    //   sd.attenuationCoef.x/y/z
    //   sd.refractiveIndex
    void addShader(const ISceneLoader::ShaderDesc &sd) override {
        std::cout << "Creating shader: name=" << sd.name
                  << ", type=" << sd.type << std::endl;

        auto shader       = std::make_shared<Shader>();
        shader->name      = sd.name;
        shader->type      = sd.type;

        // ShaderProperty uses .data for the vec, not a direct array
        shader->diffuse   = { sd.diffuse.data.x,  sd.diffuse.data.y,  sd.diffuse.data.z  };
        shader->specular  = { sd.specular.data.x, sd.specular.data.y, sd.specular.data.z };
        shader->ambient   = { sd.emission.data.x, sd.emission.data.y, sd.emission.data.z };

        shader->shininess = sd.phongExp;
        shader->ior       = sd.refractiveIndex;
        shader->mirrorCoef = sd.mirrorCoef;
        shader->roughness  = sd.roughness;

        m_targetScene.shaders[sd.name] = shader;
    }

    // ── SHAPES ───────────────────────────────────────────────────────────
    // ShapeDesc fields (from ISceneLoader.h):
    //   sd.type, sd.name
    //   sd.shaderNameReference   ← NOT sd.shader
    //   sd.center, sd.radius     (sphere)
    //   sd.v0, sd.v1, sd.v2      (triangle)
    //   sd.minPt, sd.maxPt       (box)
    //   sd.hasXForm, sd.localXForm
    void addShape(const ISceneLoader::ShapeDesc &sd) override {
        std::cout << "Creating shape: type=" << sd.type
                  << ", shader=" << sd.shaderNameReference << std::endl;

        // Look up material — key fix: use shaderNameReference, not sd.shader
        auto shader = m_targetScene.findShader(sd.shaderNameReference);
        if (!shader) {
            std::cerr << "  WARNING: shader '" << sd.shaderNameReference
                      << "' not found for shape '" << sd.name << "'\n";
        }

        if (sd.type == "sphere") {
            auto sphere    = std::make_shared<Sphere>();
            sphere->center = { sd.center.x, sd.center.y, sd.center.z };
            sphere->radius = sd.radius;
            sphere->shader = shader;
            m_targetScene.shapes.push_back(sphere);
        }
        else if (sd.type == "triangle") {
            auto tri    = std::make_shared<Triangle>();
            tri->v0     = { sd.v0.x, sd.v0.y, sd.v0.z };
            tri->v1     = { sd.v1.x, sd.v1.y, sd.v1.z };
            tri->v2     = { sd.v2.x, sd.v2.y, sd.v2.z };
            tri->shader = shader;
            m_targetScene.shapes.push_back(tri);
        }
        else if (sd.type == "plane") {
            auto plane    = std::make_shared<Plane>();
            plane->point  = { sd.center.x, sd.center.y, sd.center.z };
            plane->normal = { sd.v0.x,     sd.v0.y,     sd.v0.z     };
            plane->shader = shader;
            m_targetScene.shapes.push_back(plane);
        }
        else if (sd.type == "box") {
            auto box    = std::make_shared<Box>();
            box->minPt  = { sd.minPt.x, sd.minPt.y, sd.minPt.z };
            box->maxPt  = { sd.maxPt.x, sd.maxPt.y, sd.maxPt.z };
            box->shader = shader;
            m_targetScene.shapes.push_back(box);
        }
        else {
            std::cerr << "  WARNING: unknown shape type '" << sd.type << "' — skipped.\n";
        }
    }

    // ── TEXTURES ─────────────────────────────────────────────────────────
    void addTexture(const std::string &type, const std::string &name,
                    const std::string &sourceFile) override
    {
        std::cout << "Creating texture: type=" << type
                  << ", name=" << name
                  << ", sourceFile=" << sourceFile << std::endl;
    }
};