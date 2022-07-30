#include "lightmodel.h"
#include <math.h>

/*
 * This file contains the phong function you need to fill in.
 * Check detailed explanation about input arguments at lightmodel.cpp
 * This should be the ONLY file you modify.
 */


// calculates RGBA of a pixel with given infomation
RGBA phong(glm::vec3 p, glm::vec3 n, glm::vec3 s, Material m,
           std::vector<LightInfo> lights, Sampler refl_sampler)
{
    glm::vec4 illumination(1,1,1,1);

    // Task 3 - ambient light:
    // remembert to replace the initial value of illumination or set it to zero

    for (LightInfo l: lights)
    {
        // Task 6 - attenuation:

        // Task 4 - diffuse light:

        // Task 5 - specular light:
    }

    // Task 7 - reflection:
    /*
     * usage for reflection sampler:
     *          Sampler::sample(glm::vec3 start_position, glm::vec3 light_direction) -> glm::vec4
     *          Returns reflection intensity at a direction from start position
     */

    // Task 1 - illumination to rgba:
    // You can simply uncomment the lines below
    RGBA out(0,0,0,0);
    // out.r = glm::clamp(illumination.r, 0.f, 1.f)*255.f;
    // out.g = glm::clamp(illumination.g, 0.f, 1.f)*255.f;
    // out.b = glm::clamp(illumination.b, 0.f, 1.f)*255.f;
    // out.a = glm::clamp(illumination.a, 0.f, 1.f)*255.f;

    return out;
}
