#ifndef UTILS_H
#define UTILS_H

#include <QImage>
#include <QString>

#include "glm.hpp"
#include "rgba.h"

const float ka = 0.5;
const float kd = 0.5;
const float ks = 0.5;
const float kr = 0.2;


const float c1 = 1;
const float c2 = 0.05;
const float c3 = 0.06;

struct Material
{
    glm::vec4 diffuse;
    glm::vec4 ambient;
    glm::vec4 specular;
    int shininess;
};

struct LightInfo
{
    glm::vec4 color;
    glm::vec3 source;
};

float inct_sphere(glm::vec3 pos, glm::vec3 dir);

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
