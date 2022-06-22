#ifndef LIGHTMODEL_H
#define LIGHTMODEL_H

#include "glm.hpp"
#include "rgba.h"
#include "utils.h"

#include <vector>

// position, normal, material, lightinfo
RGBA phong(glm::vec3 p, glm::vec3 n, glm::vec3 c, Material m, std::vector<LightInfo> lights);


#endif // LIGHTMODEL_H
