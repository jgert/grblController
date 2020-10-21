//
// Created by Jakub Gert on 28/09/2020.
//

#include <QOpenGLFunctions>
#include <QPropertyAnimation>
#include "Renderer3DWidget.h"

void Renderer3DWidget::initializeGL() {
    initializeOpenGLFunctions();

    vao = new QOpenGLVertexArrayObject(this);
    vao->create();
    vao->bind();

    shader = new QOpenGLShaderProgram();
    shader->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/vshader.glsl");
    shader->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/fshader.glsl");
    shader->link();

    matrixProjectionId = shader->uniformLocation("mProjection");
    matrixCameraId = shader->uniformLocation("mCamera");
    matrixWorldId = shader->uniformLocation("mWorld");

    vbo = new QOpenGLBuffer(QOpenGLBuffer::Type::VertexBuffer);
    vbo->create();
    vbo->bind();
    vbo->allocate(lines.constData(), lines.count() * sizeof(Line));

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) offsetof(Vertex, color));

    vbo->release();

    matrixWorld.setToIdentity();
}

void Renderer3DWidget::resizeGL(int, int) {
    updateCamera();
}

void Renderer3DWidget::paintGL() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    vbo->bind();
    shader->bind();

    shader->setUniformValue(matrixCameraId, matrixCamera);
    shader->setUniformValue(matrixProjectionId, matrixProjection);
    shader->setUniformValue(matrixWorldId, matrixWorld);

    glDrawArrays(GL_LINES, 0, lines.count() * 2);
    shader->release();
    vbo->release();
}

Renderer3DWidget::Renderer3DWidget(QWidget *parent) :
        QOpenGLWidget(parent),
        QOpenGLFunctions(),
        angleYaw(0.0),
        anglePitch(0.0),
        zoom(1.0) {

    for (int x = -5; x <= 5; x++) {
        Vertex v1(QVector3D(x, -5, 0), QVector4D(0.5, 0.5, 0.5, 0.5));
        Vertex v2(QVector3D(x, 5, 0), QVector4D(0.5, 0.5, 0.5, 0.5));
        lines.append(Line(v1, v2));
    }
    for (int y = -5; y <= 5; y++) {
        Vertex v1(QVector3D(-5, y, 0), QVector4D(0.5, 0.5, 0.5, 0.5));
        Vertex v2(QVector3D(5, y, 0), QVector4D(0.5, 0.5, 0.5, 0.5));
        lines.append(Line(v1, v2));
    }

    lines.append(
            Line(
                    Vertex(QVector3D(0.0, 0.0, 0.0), QVector4D(1.0, 0.0, 0.0, 1.0)),
                    Vertex(QVector3D(1.0, 0.0, 0.0), QVector4D(0.0, 0.0, 0.0, 1.0))
            ));

    lines.append(
            Line(
                    Vertex(QVector3D(0.0, 0.0, 0.0), QVector4D(0.0, 1.0, 0.0, 1.0)),
                    Vertex(QVector3D(0.0, 1.0, 0.0), QVector4D(0.0, 0.0, 0.0, 0.0))
            ));

    lines.append(
            Line(
                    Vertex(QVector3D(0.0, 0.0, 0.0), QVector4D(0.0, 0.0, 1.0, 1.0)),
                    Vertex(QVector3D(0.0, 0.0, 1.0), QVector4D(0.0, 0.0, 0.0, 0.0))
            ));
}

void Renderer3DWidget::mousePressEvent(QMouseEvent *event) {
    QWidget::mousePressEvent(event);
    mouseStartPosition = event->localPos();
}

void Renderer3DWidget::mouseMoveEvent(QMouseEvent *event) {
    QWidget::mouseMoveEvent(event);
    QPointF delta = event->localPos() - mouseStartPosition;

    const auto buttons = event->buttons();
    if (buttons & Qt::MouseButton::LeftButton) {

        auto up = matrixCamera.row(1).toVector3D();
        auto right = matrixCamera.row(0).toVector3D();

        auto d = -delta.y() * up + delta.x() * right;
        d *= zoom;
        d /= float(0.5 * frameSize().width());

        cameraLookAtPosition += QVector3D(d.x(), d.y(), d.z());

        updateCamera();

    } else if (buttons & Qt::MouseButton::RightButton) {
        anglePitch += delta.y();
        angleYaw += delta.x();

        updateCamera();
    }
    mouseStartPosition = event->localPos();
    updateCamera();
}

void Renderer3DWidget::wheelEvent(QWheelEvent *event) {
    QWidget::wheelEvent(event);

    auto delta = float(event->angleDelta().y());
    zoom = fmax(0.1f, zoom - delta * 0.01f);
    updateCamera();
}

void Renderer3DWidget::updateCamera() {
    auto w = rect().width();
    auto h = rect().height();
    auto aspect = float(h) / float(w);

    matrixProjection.setToIdentity();
    matrixProjection.ortho(
            -zoom, zoom, -aspect * zoom, aspect * zoom,
            -100, 100.0);

    QMatrix4x4 matrixRotation;
    matrixRotation.setToIdentity();
    matrixRotation.rotate(anglePitch, QVector3D(1, 0, 0));
    matrixRotation.rotate(angleYaw, QVector3D(0, 0, 1));

    QMatrix4x4 matrixTransform;
    matrixTransform.setToIdentity();
    matrixTransform.translate(cameraLookAtPosition);

    matrixCamera.setToIdentity();
    matrixCamera *= matrixRotation;
    matrixCamera *= matrixTransform;

    update();
}
