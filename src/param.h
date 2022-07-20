#ifndef PARAM_H
#define PARAM_H


#include "glm.hpp"
#include "rgba.h"


/*
 * This file contains the parameters and data structures that you
 * will be working with.
 * You are NOT supposed to modify this file.
 */


const float ka = 0.5;   // weight for ambient light
const float kd = 0.5;   // weight for diffuse light
const float ks = 0.5;   // weight for specular light
const float kr = 0.2;   // weight for mirror reflection

const float c1 = 1;     // attenuation coefficient 1
const float c2 = 0.05;  // attenuation coefficient 2
const float c3 = 0.06;  // attenuation coefficient 3


struct Material
{
    glm::vec4 diffuse;   // diffuse color of surface/object material
    glm::vec4 ambient;   // ambient color of surface/object material
    glm::vec4 specular;  // specular color of surface/object material
    int shininess;       // shininess of surface/object material
};

struct LightInfo
{
    glm::vec4 color;     // point light color
    glm::vec3 source;    // point light source position
};

struct pixel_info
{
    glm::vec3 position;   // position of intersection point
    glm::vec3 normal;     // surface normal of intersection point
    glm::vec3 sight;      // direction from intersection point to camera
    Material material;    // material of surface at intersection point
    bool intersect=false; // whether intersect
};

#endif // PARAM_H
