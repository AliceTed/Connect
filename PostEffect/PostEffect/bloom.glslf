#version 330
in vec2 out_TexCoord;
layout(location = 0) out vec4 out_FragColor;
uniform sampler2D u_sceneColor;
uniform vec2 u_direction;
uniform float u_weight[5]= float[] (0.227027, 0.1945946, 0.1216216, 0.054054, 0.016216);
void main(void)
 {
 	vec2 tex_offset = 1.0 / textureSize(u_sceneColor,0);
    vec3 result = texture2D(u_sceneColor, out_TexCoord).rgb * u_weight[0];
    for(int i = 1; i < 5; ++i)
    {   
       	vec2 offset=tex_offset*i *u_direction;
        result += texture2D(u_sceneColor, out_TexCoord+offset).rgb * u_weight[i];
        result += texture2D(u_sceneColor, out_TexCoord-offset).rgb * u_weight[i];
    }
    out_FragColor = vec4(result.rgb, 1.0);
}
