varying highp vec3 normal;
varying highp vec3 tail; // tail: x = pos, y = bulge, z = ? possibly change color by length
uniform lowp vec3 albedo;

const vec3 lightDir = vec3(.8, 0.4, .8);

void main(void)
{
   float lighting = step(.2, dot(normal, lightDir));
   gl_FragColor = vec4(.7*albedo + .3*albedo*lighting, 1.0);
}