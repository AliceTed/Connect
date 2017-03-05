#version 330
in vec2 out_TexCoord;
layout(location = 0) out vec4 out_FragColor;
uniform sampler2D u_sceneColor;
uniform sampler2D u_bloomColor;
uniform float u_toneScale;
void main(void)
 {
    vec4 texel=texture2D(u_sceneColor, out_TexCoord) * u_toneScale;
    texel += texture2D(u_bloomColor, out_TexCoord);
    out_FragColor =texel;
}
