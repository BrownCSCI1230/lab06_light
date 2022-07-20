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
#include <string>
#include <iostream>
#include <fstream>
#include <QCoreApplication>
#include <Qfile>

#include "rgba.h"
#include "canvas2d.h"
#include "lightmodel.h"


/*
 * This file handles Qt interfaces that visualize our image.
 * Don't worry about their functions.
 * You are NOT supposed to modify this file.
 */

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

// render the image to show on canvas
void Canvas2D::draw_load()
{

    // define light sources
    std::vector<LightInfo> lights;
    lights.clear();
    lights.push_back(LightInfo{glm::vec4(0.99, 0.99, 0.99, 1), glm::vec3(2, 2, 2)});
    lights.push_back(LightInfo{glm::vec4(0.99, 0.99, 0.99, 1), glm::vec3(-4, 4, 4)});
    Sampler refl_sampler(QString(":/images/background.png"));

    // load intersection data
    std::string data_path = QCoreApplication::applicationDirPath().toStdString()+"intersections.dat";
    QFile::copy(QString(":/intersections.dat"), data_path.c_str());
    std::ifstream inFile(data_path, std::ios::in | std::ios::binary);
    pixel_info info;
    RGBA tmp(0,0,0,0);
    for(int i=0;i<width;i++)
        for(int j=0;j<height;j++)
        {
            inFile.read((char *)&info, sizeof(info));

            // get color with phong model
            if(info.intersect)
                tmp = phong(info.position, info.normal, info.sight, info.material, lights, refl_sampler);
            else
                tmp = RGBA(0,0,0,0);
            m_image->setPixel(i,j,tmp.convertQt());
        }
}

