#version 330
layout(location = 0) in vec4 in_Position;
out vec4 out_ShadowCoord;

uniform mat4 u_matWorld;
uniform mat4 u_matView;
uniform mat4 u_matProjection;

uniform mat4 u_matDepthView;
uniform mat4 u_matDepthProjection;
uniform mat4 u_matBias;

void main(void)
{
	vec4 worldPosition = u_matWorld * in_Position;
	vec4 viewPosition  = u_matView  * worldPosition;
	gl_Position = u_matProjection * viewPosition;

	//vec4 depthView=u_matDepthView*worldPosition;
	//out_ShadowCoord=u_matBias*u_matDepthProjection*depthView;
}
