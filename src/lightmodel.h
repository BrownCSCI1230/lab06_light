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
RGBA phong(
  glm::vec3 position,
  glm::vec3 normal,
  glm::vec3 directionToCamera,
  Material material,
  std::vector<LightInfo> lights,
  Sampler reflectionSampler);

#endif // LIGHTMODEL_H
