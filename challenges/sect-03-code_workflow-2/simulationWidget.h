#ifndef SIMULATIONWIDGET_H
#define SIMULATIONWIDGET_H

#include <QtOpenGL/QGLWidget>

#include "properties.h"

class QPoint;
class QAbstractButton;
class QFile;


class SimulationWidget : public QGLWidget 
{
    Q_OBJECT;
public:
    SimulationWidget(Properties *prop, QWidget *parent = 0);

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void normalizeAngle(int &angle);
    void paintAxis();
    void paintOutline();
    void paintLed(int x, int y, int z);
    void paintCube();

private:
    int zoom;
    int xRot;
    int yRot;
    int zRot;

    int length;
    int width;
    int height;

    double spacing;

    QString color;
    QString draw;
    QString guide;

    QString source;
    QString function;

    int sphRadius;
    float sphOriginX;
    float sphOriginY;
    float sphOriginZ;

    int *hist;
    bool histReady;

    QPoint lastPos;

public slots:
    void setZoom(int z);
    void setXRot(int a);
    void setYRot(int a);
    void setZRot(int a);

    void setLength(int l);
    void setWidth(int w);
    void setHeight(int h);

    void setSpacing(double s);

    void setColor(const QString &c);
    void setDraw(const QString &d);
    void setGuide(const QString &g);

    void setSource(QAbstractButton *b);
    void prepareSphere();
    void setFunction(const QString &f);
    void scanPtCloud(QFile *file);

signals:
    void xRotChanged(int angle);
    void yRotChanged(int angle);
    void zRotChanged(int angle);
};
#endif
