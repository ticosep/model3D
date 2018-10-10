#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include "model.h"

#include <QWidget>
#include <QOpenGLWidget>
#include <QOpenGLExtraFunctions>


class openglwidget : public QOpenGLWidget , protected QOpenGLExtraFunctions
{
    Q_OBJECT

    public:
        std::shared_ptr<Model> model = nullptr;

        openglwidget(QWidget * parent = 0);

    protected:
        void initializeGL();
        void resizeGL(int width , int height);
        void paintGL();

    signals:
        void statusBarMessage(QString);


    public slots:
        void transFormX(int value);
        void transFormY(int value);
        void transFormZ(int value);
        void showFileOpenDialog();

};

#endif // OPENGLWIDGET_H
