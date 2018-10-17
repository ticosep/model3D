#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include "model.h"

#include <QWidget>
#include <QOpenGLWidget>
#include <QOpenGLExtraFunctions>
#include <light.h>


class openglwidget : public QOpenGLWidget , protected QOpenGLExtraFunctions
{
    Q_OBJECT

    public:
        std::shared_ptr<Model> model = nullptr;
        Light light;
        QMatrix4x4 projectionMatrix;
        QMatrix4x4 viewMatrix;

        openglwidget(QWidget * parent = 0);


    protected:
        void initializeGL();
        void resizeGL(int width , int height);
        void paintGL();

    signals:
        void statusBarMessage(QString);
        void enableComboShaders(bool);

    public slots:
        void transFormX(int value);
        void transFormY(int value);
        void transFormZ(int value);
        void showFileOpenDialog();
        void changeShader(int);

};

#endif // OPENGLWIDGET_H
