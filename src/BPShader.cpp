#include "BPShader.h"
#include "hitRecord.h"
#include "light.h"
#include <algorithm>

vec3 blinnPhong::ray_color(const hitRecord& rec, const light& pointLight) const {
    vec3 ambient = ka * base_color;
    
    vec3 light_dir = unit_vector(pointLight.position - rec.p);
    
    float diff = std::max(0.0f, dot(rec.normal, light_dir));
    vec3 diffuse = kd * diff * base_color * pointLight.color;
    
    vec3 view_dir = unit_vector(-rec.p);

    vec3 halfway = unit_vector(light_dir + view_dir);
    
    float spec = std::pow(std::max(0.0f, dot(rec.normal, halfway)), shininess);
    vec3 specular = ks * spec * pointLight.color;
    
    return ambient + diffuse + specular;
}