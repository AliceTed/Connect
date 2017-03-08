#version 330
layout(location = 0) in vec4 in_Position;

uniform mat4 u_matWorld;
uniform mat4 u_matView;
uniform mat4 u_matProjection;
void main(void)
{
	vec4 worldPosition = u_matWorld * in_Position;
	vec4 viewPosition  = u_matView  * worldPosition;
	gl_Position = u_matProjection * viewPosition;
}
