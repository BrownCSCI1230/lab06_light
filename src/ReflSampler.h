#ifndef REFLSAMPLER_H
#define REFLSAMPLER_H

#include <QImage>
#include <QString>

#include "glm.hpp"
#include "rgba.h"


/*
 * Header file for ReflSampler.cpp
 * You are NOT supposed to modify this file.
 */

class Sampler
{
public:
    Sampler(QString path);
    ~Sampler(){}
    glm::vec4 sample(glm::vec3 pos, glm::vec3 dir);

private:
    QImage background;
    glm::vec4 interpolate(float x, float y);
    glm::vec4 Qc2vec(QColor c);
    float h_ratio;
    float w_ratio;
};

#endif // REFLSAMPLER_H
