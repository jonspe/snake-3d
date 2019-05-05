/**
  TIE-02201 Ohjelmointi 2: Perusteet, K2019
  Assignment 12.4: Matopelin paluu
    3D Snake game made with OpenGL ES 2.0.
    See 'instructions.txt' for further information.

  resourcemanager.hh
    Defines a singleton class used for managing different types of resources.
    Handles textures, shaders, meshes and JSON files.

  @author Joona Perasto, 272725, joona.perasto@tuni.fi
*/


#ifndef RESOURCEMANAGER_HH
#define RESOURCEMANAGER_HH

#include <QOpenGLTexture>
#include <QOpenGLShader>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QMap>
#include <QDir>
#include <QPolygonF>

#include <QJsonObject>

struct MeshData {
    QVector<QVector3D> vertexData;
    QVector<QVector2D> texcoordData;
    QVector<QVector3D> normalData;
    QVector<GLuint> indexData;
};


typedef QVector<QPolygonF> PolyData;


class ResourceManager
{
public:
    ~ResourceManager();

    static ResourceManager& getInstance();

    QOpenGLTexture* loadTexture(const QString& textureFileName);
    QOpenGLShader* loadShader(const QString& shaderFileName);
    QOpenGLShaderProgram* loadProgram(const QString& programName);
    MeshData* loadMesh(const QString& meshName);
    PolyData* loadPolygons(const QString &meshName);

    QJsonObject getFoodData() const;

    QOpenGLShaderProgram* createProgram(const QString& programName,
                                        const QString& vertexFileName,
                                        const QString& fragFileName);

private:
    ResourceManager();

    QMap<QString, QOpenGLTexture*> textureMap_;
    QMap<QString, QOpenGLShader*> shaderMap_;
    QMap<QString, QOpenGLShaderProgram*> programMap_;
    QMap<QString, MeshData*> meshMap_;
    QMap<QString, PolyData*> polyMap_;

    QDir textureDirectory_;
    QDir shaderDirectory_;
    QDir meshDirectory_;

    QJsonObject foodData_;

public:
    ResourceManager(ResourceManager const&) = delete;
    void operator=(ResourceManager const&) = delete;
};

#endif // RESOURCEMANAGER_HH
