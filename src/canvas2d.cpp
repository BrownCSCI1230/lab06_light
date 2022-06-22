/*
 * @FilePath: \lab06_light\src\canvas2d.cpp
 * @Author: AceSix
 * @Date: 2022-06-15 22:01:53
 * @LastEditors: AceSix
 * @LastEditTime: 2022-06-16 00:59:34
 * Copyright (C) 2022 Brown U. All rights reserved.
 */
#include <QPainter>
#include <QString>

#include "rgba.h"
#include "canvas2d.h"
#include "lightmodel.h"


Canvas2D::Canvas2D(QWidget* parent, Qt::WindowFlags f) : QWidget(parent, f)
{
    m_image = new QImage(width, height, QImage::Format_RGBX8888);
    memset(m_image->bits(), 0, width * height * sizeof(RGBA));
    for (int i = sizeof(RGBA)-1; (unsigned long) i < width * height * sizeof(RGBA); i+=sizeof(RGBA)) {
        m_image->bits()[i] = 0;
    }
    setFixedSize(width, height);
}


Canvas2D::~Canvas2D()
{
    free(m_image);
}



void Canvas2D::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawImage(QPoint(0, 0), *m_image);
}


pixel_info Canvas2D::getPixelInfo(glm::vec3 src, glm::vec3 dir)
{

    float t1 = inct_sphere(src, dir);
    float t2 = inct_sphere(src + glm::vec3(1.5,0,0), dir);
    float t3 = inct_sphere(src + glm::vec3(-1.5,0,0), dir);

    float t = t1;
    if (t<0 || (t2>0 && t2<t)) t = t2;
    if (t<0 || (t3>0 && t3<t)) t = t3;


    pixel_info info;
    info.lightInfo.color = glm::vec4(0.99, 0.99, 0.99, 1);
    info.lightInfo.source = glm::vec3(2.5, 1.5, 2);
    info.material.shininess = 10;
    info.intersect = t>0;

    if(t==t1) {
        info.position = src + dir*t;
        info.normal = glm::normalize(src + dir*t);
        info.material.ambient =  glm::vec4(0.10, 0.13, 0.45, 1);
        info.material.diffuse =  glm::vec4(0.35, 0.48, 0.75, 1);
        info.material.specular = glm::vec4(0.95, 0.95, 0.95, 1);
    } else if(t==t2)  {
        info.position = src + dir*t;
        info.normal = glm::normalize(src + dir*t + glm::vec3(1.5,0,0));
        info.material.ambient =  glm::vec4(0.10, 0.45, 0.13, 1);
        info.material.diffuse =  glm::vec4(0.35, 0.75, 0.48, 1);
        info.material.specular = glm::vec4(0.95, 0.95, 0.95, 1);
    } else if(t==t3)  {
        info.position = src + dir*t;
        info.normal = glm::normalize(src + dir*t + glm::vec3(-1.5,0,0));
        info.material.ambient =  glm::vec4(0.45, 0.10, 0.13, 1);
        info.material.diffuse =  glm::vec4(0.75, 0.35, 0.48, 1);
        info.material.specular = glm::vec4(0.95, 0.95, 0.95, 1);
    }

    return info;
}


void Canvas2D::draw()
{
    RGBA tmp(35,45,255,255);

    glm::vec3 camera = glm::vec3(0,0,5);

    for(int i=0;i<width;i++)
        for(int j=0;j<height;j++)
        {
            //
            glm::vec3 lightdir = glm::vec3((i+0.5-width/2)/height, -(j+0.5-height/2)/height, 3.6) - camera;
            lightdir = glm::normalize(lightdir);
            pixel_info info = getPixelInfo(camera, lightdir);
            if(info.intersect)
                tmp = phong(info.position, info.normal, camera, info.material, info.lightInfo);
            else
                tmp = RGBA(0,0,0,0);
            m_image->setPixel(i,j,tmp.convertQt());
        }

}