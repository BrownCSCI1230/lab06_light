#ifndef UTILS_H
#define UTILS_H

#include <QImage>
#include <QString>

#include "glm.hpp"
#include "rgba.h"



//float inct_sphere(glm::vec3 pos, glm::vec3 dir);

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

#endif // UTILS_H
