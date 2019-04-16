varying highp vec3 normal;
varying highp vec3 tail; // tail: x = pos, y = bulge, z = ? possibly change color by length
uniform mediump float tailLength;
uniform mediump vec3 diffuse;

const vec3 lightDir = vec3(0.8, 0.4, 0.8);
const vec3 baseColor = vec3(0.2, 0.7, 0.2);
const vec3 texColor = vec3(0.4, 1.0, 0.3);
const vec3 fadeColor = vec3(0.5, 0.3, 0.2);

void main(void)
{
   float lightMult = step(.2, dot(normal, lightDir));

   float texFade = step(0, .4*sin(tail.x*24 + cos(tail.z*2)*4) + .7*sin(tail.x*48));
   float lengthFade = 0.5*tail.x/tailLength;

   vec3 tex = mix(baseColor, texColor, texFade);
   vec3 albedo = mix(tex, fadeColor, lengthFade);

   gl_FragColor = vec4(.7*albedo + .3*albedo*lightMult, 1.0);
}
