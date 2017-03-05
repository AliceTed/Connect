#version 330
in vec2 out_TexCoord;
layout(location = 0) out vec4 out_FragColor;
uniform sampler2D u_sceneColor;
uniform float u_minBright;

void main(void)
 {
 	vec4 base=texture2D(u_sceneColor, out_TexCoord);
 	vec3 texel = max(vec3(0.0), (base- u_minBright).rgb);
    out_FragColor = vec4(texel, 1.0);
}
