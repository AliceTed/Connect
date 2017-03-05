#version 330
in vec4 out_Position;
layout(location = 0) out vec4 out_FragColor;
void main(void)
{
    out_FragColor =out_Position;
}
