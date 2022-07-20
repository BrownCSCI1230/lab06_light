#include "ReflSampler.h"
#include <math.h>


/*
 * The functions used for reflection.
 * We use a skybox-style reflection sampler so you don't
 * have to worry about recursive intersections here.
 * You are NOT supposed to modify this file.
 */


Sampler::Sampler(QString path)
{
    background = QImage(path);
    h_ratio = background.size().height()/10.1f;
    w_ratio = background.size().width()/10.1f;
}

// convert Qcolor to glm::vec4
glm::vec4 Sampler::Qc2vec(QColor c)
{
    return glm::vec4(c.red()/255.f, c.green()/255.f, c.blue()/255.f, c.alpha()/255.f);
}

// get interpolated color at given coordinates
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

// get reflection color of given light ray
glm::vec4 Sampler::sample(glm::vec3 pos, glm::vec3 dir)
{
    if(dir.z<0.1) return glm::vec4(0,0,0,0);
    float dis = (5 - pos.z)/dir.z;

    float x = pos.x + dir.x*dis + 5;
    float y = -pos.y - dir.y*dis + 5;

    if(x<0 || x>10 || y<0 || y>10) return glm::vec4(0,0,0,0);
    return interpolate(x*w_ratio, y*h_ratio);
}

