varying highp vec3 normal;

const vec3 lightDir = vec3(0.8, 0.4, 0.8);
const vec3 albedo = vec3(0.8, 0.6, 0.1);

void main(void)
{
   float lightMult = step(0.2, dot(normal, lightDir));
   
   gl_FragColor = vec4(0.7*albedo + 0.3*albedo*lightMult, 1.0);
}
