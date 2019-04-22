attribute highp vec4 aVertex;
attribute highp vec3 aNormal;

uniform highp mat4 mvpMatrix;

varying highp vec3 normal;


void main(void)
{
    gl_Position = mvpMatrix * aVertex;
    normal = aNormal;
}
