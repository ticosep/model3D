#include "openglwidget.h"

openglwidget::openglwidget(QWidget *parent) : QOpenGLWidget(parent)
{
    projectionMatrix.setToIdentity();
    projectionMatrix.ortho( -1 , 1 , -1 , 1 , 0 , 2);
    viewMatrix.setToIdentity();
    viewMatrix.translate(0, 0, -1);
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
    glClearColor(0 ,0 ,0 ,1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if(!model)    return;

    GLuint shaderProgramID = model->shaderProgram[model->shaderIndex];
    glUseProgram(shaderProgramID);
    QVector4D ambientProduct = light.ambient * model->material.ambient;
    QVector4D diffuseProduct = light.diffuse * model->material.diffuse;
    QVector4D specularProduct = light.specular * model->material.specular;
    GLint locProjection = glGetUniformLocation(shaderProgramID, "projection");
    GLint locView = glGetUniformLocation(shaderProgramID,"view");
    GLint locLightPosition = glGetUniformLocation(shaderProgramID,"lightPosition");
    GLint locAmbientProduct = glGetUniformLocation(shaderProgramID,"ambientProduct");
    GLint locDiffuseProduct = glGetUniformLocation(shaderProgramID,"diffuseProduct");
    GLint locSpecularProduct = glGetUniformLocation(shaderProgramID,"specularProduct");
    glUniformMatrix4fv(locProjection,1 ,GL_FALSE, projectionMatrix.data());
    glUniformMatrix4fv(locView, 1, GL_FALSE , viewMatrix.data());
    glUniform4fv( locLightPosition , 1 ,&(light.position[0]));
    glUniform4fv( locAmbientProduct , 1 ,&(ambientProduct[0]));
    glUniform4fv( locDiffuseProduct , 1 , &(diffuseProduct[0]));
    glUniform4fv( locSpecularProduct , 1 ,&(specularProduct[0]));
    model->drawModel();



}

void openglwidget::transFormX(int value)
{

    model->xTransform = value;
    update();
}

void openglwidget::transFormY(int value)
{

    model->yTransform = value;
    update();
}

void openglwidget::transFormZ(int value)
{

    model->zTransform = value;
    update();
}

void openglwidget::showFileOpenDialog()
{
    QByteArray fileFormat = "off";
    QString fileName = QFileDialog::getOpenFileName(this,"Open File", QDir::homePath(),
    QString("\%1 Files (*.\%2)").arg(QString(fileFormat.toUpper()))
        .arg(QString(fileFormat)), 0
    #ifdef Q_OS_LINUX
        ,QFileDialog::DontUseNativeDialog
    #endif
        );
    int shaderIndex = 0;
    if (!fileName.isEmpty())
    {
        if (model) {
            shaderIndex = model->shaderIndex;
            model = std::make_shared<Model>(this);
            model->shaderIndex = shaderIndex;
            model->readOFFFile(fileName);
            emit statusBarMessage(QString("Vertices : \%1 , Faces : \%2")
            .arg(model->numVertices).arg(model->numFaces));
            emit enableComboShaders(true);
        }


    }
    update();
}

void openglwidget::changeShader(int shaderIndex)
{
    if(!model)
    return;
    model->shaderIndex = shaderIndex;
    update();
}
