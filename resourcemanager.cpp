#include "resourcemanager.hh"

ResourceManager::ResourceManager()
{
    textureDirectory_.setPath(":/res/textures");
    shaderDirectory_.setPath(":/res/shaders");
}

QOpenGLTexture *ResourceManager::loadTexture(const QString &textureFileName)
{
    if (textureMap_.constFind(textureFileName) != textureMap_.constEnd())
        return textureMap_[textureFileName];

    QString path = textureDirectory_.filePath(textureFileName);
    QOpenGLTexture* texture = new QOpenGLTexture(QImage(path));

    return texture;
}

QOpenGLShader *ResourceManager::loadShader(const QString &shaderFileName)
{
    if (shaderMap_.contains(shaderFileName)){
        return shaderMap_[shaderFileName];
    }

    QOpenGLShader* shader = nullptr;
    if (shaderFileName.contains("vertex"))
        shader = new QOpenGLShader(QOpenGLShader::Vertex);
    else if (shaderFileName.contains("fragment"))
        shader = new QOpenGLShader(QOpenGLShader::Fragment);
    else
        return nullptr;

    QString path = shaderDirectory_.filePath(shaderFileName);

    shader->compileSourceFile(path);
    shaderMap_[shaderFileName] = shader;

    return shader;
}

QOpenGLShaderProgram *ResourceManager::loadProgram(const QString &programName)
{
    if (programMap_.contains(programName))
        return programMap_[programName];

    return nullptr;
}

QOpenGLShaderProgram *ResourceManager::createProgram(const QString &programName,
                                                     const QString &vertexFileName,
                                                     const QString &fragFileName)
{
    QOpenGLShader* vertexShader = loadShader(vertexFileName);
    QOpenGLShader* fragmentShader = loadShader(fragFileName);

    QOpenGLShaderProgram* program = new QOpenGLShaderProgram;
    program->addShader(vertexShader);
    program->addShader(fragmentShader);

    programMap_[programName] = program;

    return program;
}
