#version 330
in vec2 out_TexCoord;
layout(location = 0) out vec4 out_FragColor;
uniform sampler2D u_depth;
uniform sampler2D u_scene;
uniform sampler2D u_blur_row;
uniform sampler2D u_blur_high;
float restDepth(vec4 RGBA)
{
    const float rMask = 1.0;
    const float gMask = 1.0 / 255.0;
    const float bMask = 1.0 / (255.0 * 255.0);
    const float aMask = 1.0 / (255.0 * 255.0 * 255.0);
    float depth = dot(RGBA, vec4(rMask, gMask, bMask, aMask));
    return depth;
}
void main(void) 
{
	float d = restDepth(texture2D(u_depth, vec2(out_TexCoord.s, 1.0 - out_TexCoord.t)));
    float coef = 1.0 - d;
    float blur1Coef = coef * d;
    float blur2Coef = coef * coef;
    vec4 sceneColor = texture2D(u_scene, vec2(out_TexCoord.s, 1.0 - out_TexCoord.t));
    vec4 blur1Color = texture2D(u_blur_row, out_TexCoord);
    vec4 blur2Color = texture2D(u_blur_high, out_TexCoord);
    vec4 destColor  = sceneColor * d + blur1Color * blur1Coef + blur2Color * blur2Coef;
    out_FragColor =blur1Color * blur1Coef + blur2Color * blur2Coef;
}
