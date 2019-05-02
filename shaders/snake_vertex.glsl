uniform highp mat4 mvpMatrix;
uniform highp mat4 modelMatrix;
uniform highp vec3 eyeLightDir;
uniform mediump float tailLength;
uniform mediump float tailThickness;

attribute highp vec4 aVertex;
attribute highp vec3 aNormal;
attribute highp vec3 aTail;

varying highp vec3 vEyeNormal;
varying highp vec3 vTail;


const float PI = 3.141592;

// replace later with some customization struct thing
const float HEAD_LENGTH = 0.14;
const float TAIL_END_LENGTH = 0.25;


float calcThickness(float pos)
{
    if (pos < HEAD_LENGTH)
    {
        return 1.2 * tailThickness * sin((pos/HEAD_LENGTH) * PI * 0.6);
    }
    else if (pos > tailLength - TAIL_END_LENGTH)
    {
        float posTail = pos - tailLength + TAIL_END_LENGTH;
        return 0.5 * tailThickness * (1.0-smoothstep(0.0, 1.0, posTail/TAIL_END_LENGTH));
    }

    float bodyLength = tailLength-TAIL_END_LENGTH-HEAD_LENGTH;
    return tailThickness * (1.0 - 0.5 * (pos-HEAD_LENGTH)/bodyLength);
}

void main(void)
{
    // Take food in tail into account for thickness
    float thickness = calcThickness(aTail.x) * (1.0 + aTail.y*0.5);

    // Displace snake from center of line
    vec4 displacement = vec4(aNormal * thickness + vec3(0.0, thickness, 0.0), 0.0);
    gl_Position = mvpMatrix * (aVertex + displacement);

    vEyeNormal = normalize((modelMatrix * vec4(aNormal, 0.0)).xyz);
    vTail = aTail;
}
