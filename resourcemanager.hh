#ifndef RESOURCEMANAGER_HH
#define RESOURCEMANAGER_HH

#include <QOpenGLTexture>
#include <QOpenGLShader>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QMap>
#include <QDir>


struct MeshData {
    QVector<QVector3D> vertexData;
    QVector<QVector2D> uvData;
    QVector<QVector3D> normalData;
    QVector<GLuint> indexData;
};

class ResourceManager
{
public:
    ResourceManager();

    QOpenGLTexture* loadTexture(const QString& textureFileName);
    QOpenGLShader* loadShader(const QString& shaderFileName);
    QOpenGLShaderProgram* loadProgram(const QString& programName);
    MeshData* loadMesh(const QString& meshName);

    QOpenGLShaderProgram* createProgram(const QString& programName,
                                        const QString& vertexFileName,
                                        const QString& fragFileName);
private:
    QMap<QString, QOpenGLTexture*> textureMap_;
    QMap<QString, QOpenGLShader*> shaderMap_;
    QMap<QString, MeshData*> meshMap_;
    QMap<QString, QOpenGLShaderProgram*> programMap_;

    QDir textureDirectory_;
    QDir shaderDirectory_;
    QDir meshDirectory_;
};

#endif // RESOURCEMANAGER_HH
