#ifndef RESOURCEMANAGER_HH
#define RESOURCEMANAGER_HH

#include <QOpenGLTexture>
#include <QOpenGLShader>
#include <QOpenGLShaderProgram>
#include <QMap>
#include <QDir>

class ResourceManager
{
public:
    ResourceManager();

    QOpenGLTexture* loadTexture(const QString& textureFileName);
    QOpenGLShader* loadShader(const QString& shaderFileName);
    QOpenGLShaderProgram* loadProgram(const QString& programName);

    QOpenGLShaderProgram* createProgram(const QString& programName,
                                        const QString& vertexFileName,
                                        const QString& fragFileName);
private:
    QMap<QString, QOpenGLTexture*> textureMap_;
    QMap<QString, QOpenGLShader*> shaderMap_;
    QMap<QString, QOpenGLShaderProgram*> programMap_;

    QDir textureDirectory_;
    QDir shaderDirectory_;
};

#endif // RESOURCEMANAGER_HH
