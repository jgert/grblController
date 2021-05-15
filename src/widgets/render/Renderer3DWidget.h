//
// Created by Jakub Gert on 28/09/2020.
//

#ifndef GRBL_RENDERER3DWIDGET_H
#define GRBL_RENDERER3DWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QMatrix4x4>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include <QOpenGLDebugLogger>
#include <QSequentialAnimationGroup>
#include <QMouseEvent>
#include <QWheelEvent>

struct Vertex {
    QVector3D pos;
    QVector4D color;

    explicit Vertex(
            const QVector3D &pos,
            const QVector4D &color) : pos(pos), color(color) {
    }
};

struct Line {
    Vertex start;
    Vertex end;

    explicit Line(const Vertex &start, const Vertex &end) : start(start), end(end) {};
};

class Renderer3DWidget : public QOpenGLWidget, protected QOpenGLFunctions {
Q_OBJECT
private:
    QPointF mouseStartPosition;
    QMatrix4x4 matrixProjection;
    QMatrix4x4 matrixWorld;
    QMatrix4x4 matrixCamera;
    int matrixProjectionId;
    int matrixCameraId;
    int matrixWorldId;
    QVector<Line> lines;
    QVector<Vertex> points;

    QOpenGLVertexArrayObject *vao;
    QOpenGLBuffer *vbo;
    QOpenGLBuffer *vboPoints;
    QOpenGLShaderProgram *shader;
    QOpenGLBuffer *vboGrid;
    QVector3D cameraLookAtPosition;
    float angleYaw;
    float anglePitch;
    float zoom;

    void updateCamera();

    void createGrid();
    void createCoordinates();

protected:
    void initializeGL() override;

    void resizeGL(int w, int h) override;

    void paintGL() override;

    void mousePressEvent(QMouseEvent *event) override;

    void mouseMoveEvent(QMouseEvent *event) override;

    void wheelEvent(QWheelEvent *event) override;

public:
    explicit Renderer3DWidget(QWidget *parent = nullptr);

public slots:
    void setLines(const QVector<Line>& lines, const QVector<Vertex> &points);
};


#endif //GRBL_RENDERER3DWIDGET_H
