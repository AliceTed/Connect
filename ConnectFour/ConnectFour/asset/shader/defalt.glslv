#version 330
layout(location = 0) in vec4 in_Position;
layout(location = 8) in vec2 in_TexCoord;
out vec2 out_TexCoord;

void main(void)
{
	gl_Position =in_Position;
	out_TexCoord=in_TexCoord;
}
