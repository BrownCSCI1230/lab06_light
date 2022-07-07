#include "utils.h"
#include <math.h>

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
//        float _t = a2;
        if(_t>0) return _t;
    }

    return -1;
}


Sampler::Sampler(QString path)
{
    background = QImage(path);
    h_ratio = background.size().height()/10.1f;
    w_ratio = background.size().width()/10.1f;
}

glm::vec4 Sampler::Qc2vec(QColor c)
{
    return glm::vec4(c.red()/255.f, c.green()/255.f, c.blue()/255.f, c.alpha()/255.f);
}

glm::vec4 Sampler::interpolate(float x, float y)
{
    float xs = std::floor(x);
    float ys = std::floor(y);

    glm::vec4 c00 = Qc2vec(background.pixelColor(xs,   ys));
    glm::vec4 c10 = Qc2vec(background.pixelColor(xs+1, ys));
    glm::vec4 c01 = Qc2vec(background.pixelColor(xs,   ys+1));
    glm::vec4 c11 = Qc2vec(background.pixelColor(xs+1, ys+1));

    return (c00*(xs+1-x) + c10*(x-xs))*(ys+1-y) +
           (c01*(xs+1-x) + c11*(x-xs))*(y-ys);
}

glm::vec4 Sampler::sample(glm::vec3 pos, glm::vec3 dir)
{
    if(dir.z<0.1) return glm::vec4(0,0,0,0);
    float dis = (5 - pos.z)/dir.z;

    float x = pos.x + dir.x*dis + 5;
    float y = -pos.y - dir.y*dis + 5;

    if(x<0 || x>10 || y<0 || y>10) return glm::vec4(0,0,0,0);
    return interpolate(x*w_ratio, y*h_ratio);
}

