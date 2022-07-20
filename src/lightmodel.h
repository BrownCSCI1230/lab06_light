#ifndef LIGHTMODEL_H
#define LIGHTMODEL_H

#include "glm.hpp"
#include "rgba.h"
#include "param.h"
#include "ReflSampler.h"

#include <vector>

/*
 * Header file for lightmodel.cpp
 * It defines the phong function you need to fill in.
 * You are NOT supposed to modify this file.
 */

// position, normal, material, lightinfo
RGBA phong(glm::vec3 p, glm::vec3 n, glm::vec3 c, Material m, std::vector<LightInfo> lights, Sampler refl_sampler);


#endif // LIGHTMODEL_H
