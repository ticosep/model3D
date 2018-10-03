#include "openglwidget.h"

openglwidget::openglwidget(QWidget *parent) : QOpenGLWidget(parent)
{

}
void openglwidget::initializeGL()
{
    initializeOpenGLFunctions();
    qDebug ("OpenGL version : %s", glGetString(GL_VERSION));
    qDebug ("GLSL %s", glGetString(GL_SHADING_LANGUAGE_VERSION));
    glEnable (GL_DEPTH_TEST);

}

void openglwidget::resizeGL( int w , int h )
{
    glViewport(0 ,0 ,w , h);
}
void openglwidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if(!model)
        return;
    model->drawModel();
}
