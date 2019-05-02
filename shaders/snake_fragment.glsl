uniform mediump float tailLength;
uniform highp vec3 eyeLightDir;
uniform highp float ambient;

varying highp vec3 vEyeNormal;
varying highp vec3 vTail; // tail: x = pos, y = bulge, z = ? possibly change color by length


const vec3 baseColor = vec3(0.2, 0.7, 0.2);
const vec3 texColor = vec3(0.4, 1.0, 0.3);
const vec3 fadeColor = vec3(0.5, 0.3, 0.2);

void main(void)
{
   float diffuse = step(0, dot(eyeLightDir, vEyeNormal));

   float texFade = step(0.0, 0.4*sin(vTail.x*24.0 + cos(vTail.z*2.0)*4.0) + 0.7*sin(vTail.x*48.0));
   float lengthFade = 0.5*vTail.x/tailLength;

   vec3 tex = mix(baseColor, texColor, texFade);
   vec4 color = vec4(mix(tex, fadeColor, lengthFade), 0.0);

   gl_FragColor = (ambient + diffuse*(1-ambient)) * color;
}
