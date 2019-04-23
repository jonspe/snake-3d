uniform highp mat4 mvpMatrix;
uniform highp mat4 modelMatrix;
uniform highp vec3 eyeLightDir;

attribute highp vec4 aVertex;
attribute highp vec3 aNormal;
attribute highp vec2 aTexcoord;

varying highp vec3 vEyeNormal;
varying highp vec2 vTexcoord;


void main(void)
{
    vEyeNormal = normalize(modelMatrix * vec4(aNormal, 0.0));
    vTexcoord = aTexcoord;

    gl_Position = mvpMatrix * aVertex;
}
