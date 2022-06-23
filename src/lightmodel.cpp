#include "lightmodel.h"
#include <math.h>


RGBA phong(glm::vec3 p, glm::vec3 n, glm::vec3 c, Material m,
           std::vector<LightInfo> lights, Sampler refl_sampler)
{
    glm::vec4 illumination(1,1,1,1);

    // Task 1:
    illumination = m.ambient*ka;

    for (LightInfo l: lights)
    {
        // Task 2:
        glm::vec3 light_dir = p - l.source;
        light_dir = glm::normalize(light_dir);

        // Task 4:
        float distance = glm::length(p - l.source);
        float atten = std::min(1.f, 1.f/(c1 + c2*distance + c3*distance*distance));

        // Task 2, Task 4:
        float cos = -glm::dot(n, light_dir);
        cos = std::clamp(cos, 0.f, 1.f);
        illumination += l.color*m.diffuse*cos*kd*atten;

        // Task 3, Task 4:
        glm::vec3 eyesight = glm::normalize(c - p);
        glm::vec3 reflect = 2.f*cos*n + light_dir;
        float cos2 = glm::dot(eyesight, reflect);
        cos2 = std::clamp(cos2, 0.f, 1.f);
        glm::vec4 specular_term = l.color*m.specular*(float)pow(cos2, m.shininess);
        illumination += specular_term*ks*atten;
    }

    // Task 5:
    glm::vec3 eyesight = -glm::normalize(c - p);
    float cos_en = -glm::dot(eyesight, n);
    glm::vec3 reflect_eye = 2.f*cos_en*n + eyesight;
    illumination += kr*refl_sampler.sample(p, glm::normalize(reflect_eye));

    // Task 0:
    RGBA out(0,0,0,0);
    out.r = glm::clamp(illumination.r, 0.f, 1.f)*255.f;
    out.g = glm::clamp(illumination.g, 0.f, 1.f)*255.f;
    out.b = glm::clamp(illumination.b, 0.f, 1.f)*255.f;
    out.a = glm::clamp(illumination.a, 0.f, 1.f)*255.f;
    return out;
}
