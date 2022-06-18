#include "utils.h"

float inct_sphere(glm::vec3 pos, glm::vec3 dir)
{
    float B = glm::dot(pos, dir)/glm::dot(dir, dir);
    float C = (glm::dot(pos, pos)-0.25)/glm::dot(dir, dir);

    float tmp = B*B-C;
    if (tmp >= 0)
    {
        float a1 = -sqrt(tmp)-B;
        float a2 = sqrt(tmp)-B;
        float _t = a1>0 ? a1:a2;
        if(_t>0) return _t;
    }

    return -1;
}
