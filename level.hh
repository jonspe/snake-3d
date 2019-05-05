/**
  TIE-02201 Ohjelmointi 2: Perusteet, K2019
  Assignment 12.4: Matopelin paluu
    3D Snake game made with OpenGL ES 2.0.
    See 'instructions.txt' for further information.

  level.hh
    Defines a class for the 3D level play area.

  @author Joona Perasto, 272725, joona.perasto@tuni.fi
*/


#ifndef LEVEL_HH
#define LEVEL_HH

#include <renderable.hh>

/*!
 * \brief Class used to render the level mesh.
 */
class Level : public Renderable
{
public:
    /*!
     * \brief Loads necessary resources for mesh rendering.
     */
    Level();
    ~Level() override;

    /*!
     * \brief Renders the level mesh.
     * \param gl
     */
    void render(QOpenGLFunctions *gl) override;

private:
    MeshData* mesh_;
    QOpenGLTexture* texture_;
};



#endif // LEVEL_HH
