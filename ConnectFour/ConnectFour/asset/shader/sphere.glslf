#version 330
in vec2 out_TexCoord;
in vec3 out_View;
in vec3 out_Light;

layout(location = 0) out vec4 out_FragColor;

uniform vec4 u_lightAmbient;
uniform vec4 u_lightDiffuse;
uniform vec4 u_lightSpecular;

uniform vec4  gs_MaterialAmbient;
uniform vec4  gs_MaterialDiffuse;
uniform vec4  gs_MaterialSpecular;
uniform vec4  gs_MaterialEmission;
uniform float gs_MaterialShininess;

uniform sampler2D u_baseMap;
uniform sampler2D u_normalMap;
uniform vec4 u_color;
void main(void) 
{
	vec3 N = normalize(texture2D(u_normalMap, out_TexCoord).xyz * 2.0 - 1.0);
	vec3 V = normalize(out_View);
	vec3 L = normalize(out_Light);
	vec3 H = normalize(L + V);
	float diffuse  = max(dot(N, L), 0);
	float specular = pow(max(dot(N, H), 0), gs_MaterialShininess);
	vec4 baseColor = texture2D(u_baseMap, out_TexCoord.xy)*u_color;
	vec4 color = gs_MaterialAmbient  * u_lightAmbient  * baseColor
			   + gs_MaterialDiffuse  * u_lightDiffuse  * diffuse  * baseColor
			   + gs_MaterialSpecular * u_lightSpecular * specular
	           + gs_MaterialEmission * baseColor;
	color.a = u_color.a;
	out_FragColor = color;
}
