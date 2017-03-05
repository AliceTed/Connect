#version 330
in vec2 out_TexCoord;
layout(location = 0) out vec4 out_FragColor;
uniform sampler2D u_sceneColor;
uniform vec4 u_gaussFilter[7];
uniform vec2 u_scale;
void main(void)
{
    vec4 color = vec4(0.0);
	for (int i = 0; i < 7; ++i)
	{
		vec2 texcoord=out_TexCoord + u_gaussFilter[i].xy * u_scale;
		vec4 blur=texture2D(u_sceneColor,texcoord);
		color +=blur*u_gaussFilter[i].w;
	}
	out_FragColor = color;
}
