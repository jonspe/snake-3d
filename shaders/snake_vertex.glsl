#define PI 3.1415926535897932384626433832795

attribute highp vec4 aVertex;
attribute highp vec3 aNormal;
attribute highp vec3 aTail;

uniform highp mat4 mvpMatrix;
uniform mediump float tailLength;

varying highp vec3 normal;
varying highp vec3 tail;


const float THICKNESS = 0.05f;
const float HEAD_LENGTH = 0.2f;
const float TAIL_END_LENGTH = 0.25f;


float calcThickness(float pos)
{
    if (pos < HEAD_LENGTH)
        return sin((pos/HEAD_LENGTH) * PI * 0.6f) * 0.06f;
    else if (pos > tailLength - TAIL_END_LENGTH)
        return 0.5 * THICKNESS * sin((1+pos/HEAD_LENGTH) * PI/2);
    return THICKNESS * (1-pos/tailLength*0.5);
}

void main(void)
{
    float thickness = calcThickness(aTail.x);
    vec4 newPos = vec4(aVertex.xyz + aNormal * thickness + vec3(0, 0, thickness/2), aVertex.w);
    gl_Position = mvpMatrix * newPos; // TODO: implement bulge from food
    normal = aNormal;
    tail = aTail;
}
