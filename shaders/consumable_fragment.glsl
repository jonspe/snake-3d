uniform sampler2D texture;
uniform highp vec3 eyeLightDir;
uniform highp float ambient;

varying highp vec3 vEyeNormal;
varying highp vec2 vTexcoord;

void main(void)
{
   float diffuse = step(0, dot(eyeLightDir, vEyeNormal));

   vec4 color = texture2D(texture, vTexcoord);
   gl_FragColor = (ambient + diffuse*(1-ambient))*color;
}
