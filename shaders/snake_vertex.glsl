attribute highp vec4 aVertex;
attribute highp vec3 aNormal;
attribute highp vec3 aTail;
uniform highp mat4 mvpMatrix;
varying highp vec3 normal;
varying highp vec3 tail;

void main(void)
{
   gl_Position = mvpMatrix * aVertex; // TODO: implement bulge from food
   normal = aNormal;
   tail = aTail;
}
