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


/*!
 * \brief Structure containing mesh data, which can easily be
 * passed through to OpenGL.
 */
struct MeshData {
    QVector<QVector3D> vertexData;
    QVector<QVector2D> texcoordData;
    QVector<QVector3D> normalData;
    QVector<GLuint> indexData;
};

/*!
 * \brief Datastructure for containing collider polygons.
 */
typedef QVector<QPolygonF> PolyData;


/*!
 * \brief Singleton class used for managing different types of resources.
 * Handles textures, shaders, meshes and JSON files.
 */
class ResourceManager
{
public:
    ~ResourceManager();

    /*!
     * \brief Gets the single instance of this singleton.
     * \return resourceManager
     */
    static ResourceManager& getInstance();

    /*!
     * \brief Loads texture from image file. If already loaded, get from map.
     * \param textureFileName
     * \return QOpenGLTexture*
     */
    QOpenGLTexture* loadTexture(const QString& textureFileName);

    /*!
     * \brief Loads shader from shader file. If already loaded, get from map.
     * \param shaderFileName
     * \return QOpenGLShader*
     */
    QOpenGLShader* loadShader(const QString& shaderFileName);

    /*!
     * \brief Gets the shader program 'programName' from map.
     * \param programName
     * \return QOpenGLShaderProgram*, nullptr if not created.
     */
    QOpenGLShaderProgram* loadProgram(const QString& programName);

    /*!
     * \brief Loads mesh from given .obj file. If already loaded, get from map.
     * \param meshName
     * \return MeshData*, nullptr if couldn't parse.
     */
    MeshData* loadMesh(const QString& meshName);

    /*!
     * \brief Loads the polygons from a specially formatted .obj file.
     * \param meshName
     * \return PolyData*, nullptr if couldn't parse.
     */
    PolyData* loadPolygons(const QString &meshName);

    /*!
     * \brief Gets the JSON data of FoodItems.
     * \return foodData
     */
    QJsonObject getFoodData() const;

    /*!
     * \brief Creates a shader program from a vertex shader and fragment shader
     * and compiles the sources.
     * \param programName
     * \param vertexFileName
     * \param fragFileName
     * \return QOpenGLShaderProgram*
     */
    QOpenGLShaderProgram* createProgram(const QString& programName,
                                        const QString& vertexFileName,
                                        const QString& fragFileName);

private:
    ResourceManager();

    /*!
     * \brief Datastructures for indexing all resources.
     */

    QMap<QString, QOpenGLTexture*> textureMap_;
    QMap<QString, QOpenGLShader*> shaderMap_;
    QMap<QString, QOpenGLShaderProgram*> programMap_;
    QMap<QString, MeshData*> meshMap_;
    QMap<QString, PolyData*> polyMap_;

    /*!
     * \brief Convenience directories for searching resources.
     */

    QDir textureDirectory_;
    QDir shaderDirectory_;
    QDir meshDirectory_;

    QJsonObject foodData_;

public:
    ResourceManager(ResourceManager const&) = delete;
    void operator=(ResourceManager const&) = delete;
};

#endif // RESOURCEMANAGER_HH
