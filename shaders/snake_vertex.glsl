
attribute highp vec4 aVertex;
attribute highp vec3 aNormal;
attribute highp vec3 aTail;

uniform highp mat4 mvpMatrix;
uniform mediump float tailLength;

varying highp vec3 normal;
varying highp vec3 tail;


const float PI = 3.141592;

const float THICKNESS = 0.05f;
const float HEAD_LENGTH = 0.2f;
const float TAIL_END_LENGTH = 0.25f;


float calcThickness(float pos)
{
    if (pos < HEAD_LENGTH)
    {
        return 1.2 * THICKNESS * sin((pos/HEAD_LENGTH) * PI * 0.6f);
    }
    else if (pos > tailLength - TAIL_END_LENGTH)
    {
        float posTail = pos - tailLength + TAIL_END_LENGTH;
        return 0.5 * THICKNESS * (1-smoothstep(0, 1, posTail/TAIL_END_LENGTH));
    }

    float bodyLength = tailLength-TAIL_END_LENGTH-HEAD_LENGTH;
    return THICKNESS * (1 - 0.5 * (pos-HEAD_LENGTH)/bodyLength);
}

void main(void)
{
    float thickness = calcThickness(aTail.x);
    vec4 newPos = vec4(aVertex.xyz + aNormal * thickness + vec3(0, 0, thickness/2), aVertex.w);
    gl_Position = mvpMatrix * newPos; // TODO: implement bulge from food
    normal = aNormal;
    tail = aTail;
}
