#ifndef MODEL_H
#define MODEL_H

#include <QtOpenGL>
#include <QOpenGLWidget>
#include <QOpenGLExtraFunctions>
#include <QTextStream>
#include <QFile>
#include <fstream>
#include <limits>
#include <iostream>
#include <memory>
#include <material.h>

class Model : public QOpenGLExtraFunctions
{
public:
    Model(QOpenGLWidget * _glWidget);
    ~Model();
    std::unique_ptr <QVector4D[]> vertices;
    std::unique_ptr <unsigned int []> indices;
    std::unique_ptr <QVector3D []> normals;

    QVector3D normal;

    QOpenGLWidget * glWidget;
    unsigned int numVertices;
    unsigned int numFaces;
    int xTransform = 0;
    int yTransform = 0;
    int zTransform = 0;
    GLuint vao = 0;
    GLuint vboVertices = 0;
    GLuint vboIndices = 0;
    std::vector<GLuint> shaderProgram;
    QMatrix4x4 modelMatrix;
    QVector3D midPoint;
    double invDiag;

    Material material;
    GLuint vboNormals = 0;
    int shaderIndex = 0;
    int numShaders = 0;


    void createVBOs();
    void createShaders();
    void destroyVBOs();
    void destroyShaders();
    void readOFFFile(const QString &fileName);
    void drawModel();
    void createNormals();


};

#endif // MODEL_H
