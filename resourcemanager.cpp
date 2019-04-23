#include "resourcemanager.hh"

#include <QRegularExpression>

namespace {
    MeshData* parseObjFile(const QString& path);
}

ResourceManager::ResourceManager()
{
    textureDirectory_.setPath(":/textures");
    shaderDirectory_.setPath(":/shaders");
    meshDirectory_.setPath(":/meshes");
}

QOpenGLTexture *ResourceManager::loadTexture(const QString &textureFileName)
{
    if (textureMap_.constFind(textureFileName) != textureMap_.constEnd())
        return textureMap_[textureFileName];

    QString path = textureDirectory_.filePath(textureFileName);
    QOpenGLTexture* texture = new QOpenGLTexture(QImage(path).mirrored(false, true));

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

MeshData* ResourceManager::loadMesh(const QString &meshName)
{
    if (meshMap_.contains(meshName))
        return meshMap_[meshName];

    QString path = meshDirectory_.filePath(meshName);
    MeshData* meshData = parseObjFile(path);

    if (meshData == nullptr)
    {
        qDebug() << "Error loading mesh " << meshName;
        return nullptr;
    }

    meshMap_[meshName] = meshData;

    qDebug() << "Mesh" << meshName << "loaded.";

    return meshData;
}

namespace {

MeshData* parseObjFile(const QString& path) {
    QFile meshFile(path);
    MeshData* meshData = new MeshData;

    if (meshFile.open(QIODevice::ReadOnly))
    {
        QRegularExpression vertexExp("v\\s(\\-?\\d+\\.\\d+)\\s(\\-?\\d+\\.\\d+)\\s(\\-?\\d+\\.\\d+)"); // 3d vertices
        QRegularExpression texcoordExp("vt\\s(\\-?\\d+\\.\\d+)\\s(\\-?\\d+\\.\\d+)"); // 2d texture coordinate uvs
        QRegularExpression normalExp("vn\\s(\\-?\\d+\\.\\d+)\\s(\\-?\\d+\\.\\d+)\\s(\\-?\\d+\\.\\d+)"); // 3d normals

        QRegularExpression faceExp("f\\s(\\d+/\\d+/\\d+)\\s(\\d+/\\d+/\\d+)\\s(\\d+/\\d+/\\d+)"); // mesh should be triangulated
        QRegularExpression faceVertExp("(\\d+)/(\\d+)/(\\d+)"); // mesh should have UVs and normals exported

        QVector<QVector3D> tempVertexData;
        QVector<QVector2D> tempTexcoordData;
        QVector<QVector3D> tempNormalData;
        uint indexCounter = 0;

        QTextStream in(&meshFile);

        while (!in.atEnd())
        {
            QString line = in.readLine();

            if (vertexExp.match(line).hasMatch())
            {
                QRegularExpressionMatch match = vertexExp.match(line);
                tempVertexData.append(QVector3D(
                    match.captured(1).toFloat(),
                    match.captured(2).toFloat(),
                    match.captured(3).toFloat()
                ));
            }
            else if (texcoordExp.match(line).hasMatch())
            {
                QRegularExpressionMatch match = texcoordExp.match(line);
                tempTexcoordData.append(QVector2D(
                    match.captured(1).toFloat(),
                    match.captured(2).toFloat()
                ));
            }
            else if (normalExp.match(line).hasMatch())
            {
                QRegularExpressionMatch match = normalExp.match(line);
                tempNormalData.append(QVector3D(
                    match.captured(1).toFloat(),
                    match.captured(2).toFloat(),
                    match.captured(3).toFloat()
                ));
            }
            else if (faceExp.match(line).hasMatch())
            {
                QRegularExpressionMatch match = faceExp.match(line);

                // Loop through all 3 vertices of triangle
                for (int index = 1; index <= 3; ++index)
                {
                    QRegularExpressionMatch vertMatch = faceVertExp.match(match.captured(index));

                    // 1st index is vertex position, 2nd index is uv, 3rd index is normal
                    // Triangles are formatted in .obj file like so, for example:
                    // f 4/2/3 6/2/1 9/2/4
                    int vertexIndex = vertMatch.captured(1).toInt() - 1;
                    int texcoordIndex = vertMatch.captured(2).toInt() - 1;
                    int normalIndex = vertMatch.captured(3).toInt() - 1;

                    meshData->vertexData.append(tempVertexData.at(vertexIndex));
                    meshData->texcoordData.append(tempTexcoordData.at(texcoordIndex));
                    meshData->normalData.append(tempNormalData.at(normalIndex));

                    // Temporary, uses duplicate vertices so shading is questionable
                    // TODO: Detect duplicate vertices and adjust indices accordingly
                    meshData->indexData.append(indexCounter++);
                }
            }
        }
        meshFile.close();
    }

    return meshData;
}

}
