#ifndef LIGHTMODEL_H
#define LIGHTMODEL_H

#include "glm.hpp"
#include "rgba.h"
#include "param.h"
#include "utils.h"

#include <vector>

RGBA phong(
  glm::vec3 position,
  glm::vec3 normal,
  glm::vec3 directionToCamera,
  Material material,
  std::vector<LightInfo> lights,
  Sampler reflectionSampler);

#endif // LIGHTMODEL_H
