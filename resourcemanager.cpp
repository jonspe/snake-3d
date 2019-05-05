/**
  TIE-02201 Ohjelmointi 2: Perusteet, K2019
  Assignment 12.4: Matopelin paluu
    3D Snake game made with OpenGL ES 2.0.
    See 'instructions.txt' for further information.

  resourcemanager.cpp
    Singleton class used for managing different types of resources.
    Handles textures, shaders, meshes and JSON files.

  @author Joona Perasto, 272725, joona.perasto@tuni.fi
*/


#include "resourcemanager.hh"

#include <QRegularExpression>
#include <QJsonDocument>
#include <QJsonObject>

namespace {
    MeshData* parseObjFile(const QString& path);
    PolyData* parseObjFilePolygons(const QString& path);
    QJsonObject parseJsonFile(const QString& path);
}

ResourceManager& ResourceManager::getInstance()
{
    static ResourceManager instance;
    return instance;
}

ResourceManager::ResourceManager()
{
    textureDirectory_.setPath(":/resources/textures");
    shaderDirectory_.setPath(":/resources/shaders");
    meshDirectory_.setPath(":/resources/meshes");

    foodData_ = parseJsonFile(":/resources/gamedata/fooditems.json");
}

ResourceManager::~ResourceManager()
{
    for (QOpenGLShader* shader : shaderMap_)
        delete shader;

    for (QOpenGLShaderProgram* program : programMap_)
        delete program;

    for (QOpenGLTexture* texture : textureMap_)
        delete texture;

    for (MeshData* mesh : meshMap_)
        delete mesh;
}

QJsonObject ResourceManager::getFoodData() const
{
    return foodData_;
}

QOpenGLTexture *ResourceManager::loadTexture(const QString &textureFileName)
{
    if (textureMap_.contains(textureFileName))
        return textureMap_[textureFileName];

    QString path = textureDirectory_.filePath(textureFileName);
    QOpenGLTexture* texture = new QOpenGLTexture(QImage(path).mirrored(false, true));

    textureMap_[textureFileName] = texture;

    qDebug() << "Texture" << textureFileName << "loaded.";

    return texture;
}

QOpenGLShader *ResourceManager::loadShader(const QString &shaderFileName)
{
    if (shaderMap_.contains(shaderFileName))
        return shaderMap_[shaderFileName];

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

    qDebug() << "Shader" << shaderFileName << "loaded.";

    return shader;
}

QOpenGLShaderProgram *ResourceManager::loadProgram(const QString &programName)
{
    if (programMap_.contains(programName))
        return programMap_[programName];

    qDebug() << "Shader program" << programName << "does not exist.";

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

    qDebug() << "Shader program" << programName << "created using" << vertexFileName << fragFileName;

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

PolyData* ResourceManager::loadPolygons(const QString &meshName)
{
    if (polyMap_.contains(meshName))
        return polyMap_[meshName];

    QString path = meshDirectory_.filePath(meshName);
    PolyData* polyData = parseObjFilePolygons(path);

    if (polyData == nullptr)
    {
        qDebug() << "Error loading polygons " << meshName;
        return nullptr;
    }

    polyMap_[meshName] = polyData;

    qDebug() << "Polygons" << meshName << "loaded.";

    return polyData;
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

            if (vertexExp.match(line).hasMatch()) // line defines a 3D vertex
            {
                QRegularExpressionMatch match = vertexExp.match(line);
                tempVertexData.append(QVector3D(
                    match.captured(1).toFloat(),
                    match.captured(2).toFloat(),
                    match.captured(3).toFloat()
                ));
            }
            else if (texcoordExp.match(line).hasMatch()) // line defines texture coordinates
            {
                QRegularExpressionMatch match = texcoordExp.match(line);
                tempTexcoordData.append(QVector2D(
                    match.captured(1).toFloat(),
                    match.captured(2).toFloat()
                ));
            }
            else if (normalExp.match(line).hasMatch()) // line defines vertex normal
            {
                QRegularExpressionMatch match = normalExp.match(line);
                tempNormalData.append(QVector3D(
                    match.captured(1).toFloat(),
                    match.captured(2).toFloat(),
                    match.captured(3).toFloat()
                ));
            }
            else if (faceExp.match(line).hasMatch()) // line defines a triangle
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

                    // Uses duplicate vertices so not the most efficient, but this will do
                    meshData->indexData.append(indexCounter++);
                }
            }
        }
        meshFile.close();
    } else {
        qWarning() << "Could not parse obj file at" << path;
    }

    return meshData;
}


PolyData* parseObjFilePolygons(const QString& path) {
    QFile objFile(path);
    PolyData* polyData = new PolyData;

    if (objFile.open(QIODevice::ReadOnly))
    {
        QRegularExpression vertexExp("^v\\s(\\-?\\d+\\.\\d+)\\s(\\-?\\d+\\.\\d+)\\s(\\-?\\d+\\.\\d+)"); // 3d vertices

        // Polygon with only vertex data format is like:
        // f 113 136 135 134 133 132 ...
        QRegularExpression faceExp("^f\\s"); // does line declare a face?
        QRegularExpression faceVertExp("(\\d+)"); // mesh should have UVs and normals exported

        QVector<QPointF> tempVertexData;

        QTextStream in(&objFile);

        while (!in.atEnd())
        {
            QString line = in.readLine();

            if (vertexExp.match(line).hasMatch())
            {
                QRegularExpressionMatch match = vertexExp.match(line);

                // only use x and z coordinate to form flat polygon, ignore height
                tempVertexData.append(QPointF(
                    match.captured(1).toDouble(),
                    match.captured(3).toDouble()
                ));
            }
            else if (faceExp.match(line).hasMatch())
            {
                QVector<QPointF> points;
                QRegularExpressionMatchIterator match = faceVertExp.globalMatch(line);

                // Iterate through polygon vertex indices (f 113 136 135 134 ...)
                while (match.hasNext())
                {
                    int vertexIndex = match.next().captured().toInt() - 1;
                    points.append(tempVertexData.at(vertexIndex));
                }

                polyData->append(QPolygonF(points));
            }
        }
        objFile.close();
    } else {
        qWarning() << "Could not parse obj file at" << path;
    }

    return polyData;
}


QJsonObject parseJsonFile(const QString& path)
{
    QFile jsonFile(path);
    QByteArray jsonByteArray;

    jsonFile.open(QIODevice::ReadOnly | QIODevice::Text);
    jsonByteArray = jsonFile.readAll();
    jsonFile.close();

    QJsonDocument document = QJsonDocument::fromJson(jsonByteArray);
    return document.object();
}

}
