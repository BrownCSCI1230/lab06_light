#ifndef Canvas2D_H
#define Canvas2D_H

#include "glm/gtc/matrix_transform.hpp"

#include <vector>
#include <QWidget>
#include "param.h"
#include "ReflSampler.h"

/*
 * Header file for canvas2d.cpp
 * You are NOT supposed to modify this file.
 */


class Canvas2D : public QWidget
{
    Q_OBJECT
public:
    Canvas2D(QWidget* parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
    ~Canvas2D();
    void draw();
    void draw_load();
    void paintEvent(QPaintEvent *event);

protected:
    QImage *m_image;

    // a temporary function, will be replaced by loading data
    pixel_info getPixelInfo(glm::vec3 src, glm::vec3 dir);

private:
    QPoint m_marqueeStart, m_marqueeStop;
    const int width = 768;
    const int height = 512;
};

#endif // Canvas2D_H
