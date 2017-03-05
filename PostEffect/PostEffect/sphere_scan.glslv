#version 330
layout(location = 0) in vec4 in_Position;
layout(location = 8) in vec2 in_TexCoord;
out vec2 out_TexCoord;
out vec4 out_WorldPosition;
out vec2 out_ScreenPosition;

uniform mat4 u_matView;
uniform mat4 u_matProjection;
uniform mat4 u_matScreen;
void main(void)
{
	out_WorldPosition=in_Position;
	vec4 screen=in_Position*u_matView*u_matProjection*u_matScreen;
	out_ScreenPosition=screen.xy;
	out_TexCoord=in_TexCoord;
	gl_Position =in_Position;
}
