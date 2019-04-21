attribute highp vec4 aVertex;
attribute highp vec3 aNormal;
attribute highp vec3 aTail;

uniform highp mat4 mvpMatrix;
uniform mediump float tailLength;

varying highp vec3 normal;
varying highp vec3 tail;


const float PI = 3.141592;

const float THICKNESS = 0.05;
const float HEAD_LENGTH = 0.2;
const float TAIL_END_LENGTH = 0.25;


float calcThickness(float pos)
{
    if (pos < HEAD_LENGTH)
    {
        return 1.2 * THICKNESS * sin((pos/HEAD_LENGTH) * PI * 0.6);
    }
    else if (pos > tailLength - TAIL_END_LENGTH)
    {
        float posTail = pos - tailLength + TAIL_END_LENGTH;
        return 0.5 * THICKNESS * (1.0-smoothstep(0.0, 1.0, posTail/TAIL_END_LENGTH));
    }

    float bodyLength = tailLength-TAIL_END_LENGTH-HEAD_LENGTH;
    return THICKNESS * (1.0 - 0.5 * (pos-HEAD_LENGTH)/bodyLength);
}

void main(void)
{
    // Take food in tail into account for thickness
    float thickness = calcThickness(aTail.x) * (1.0 + aTail.y*0.5);

    // Displace snake from center of line
    vec4 displacement = vec4(aNormal * thickness + vec3(0.0, 0.0, thickness/2.0), 0.0f);
    gl_Position = mvpMatrix * (aVertex + displacement);

    normal = aNormal;
    tail = aTail;
}
