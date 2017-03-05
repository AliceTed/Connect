#version 330
layout(location = 0) in vec4 in_Position;
out vec4 out_Position;
uniform mat4 u_matWorld;
uniform mat4 u_matView;
uniform mat4 u_matProjection;
void main(void)
{
	vec4 worldPosition = u_matWorld * in_Position;
	vec4 viewPosition  = u_matView  * worldPosition;
	vec4 position= u_matProjection * viewPosition;
	out_Position=position;
	gl_Position =position;
}
