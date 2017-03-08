#version 330
in vec4 out_ShadowCoord;
layout(location = 0) out vec4 out_FragColor;

uniform sampler2D u_shadowMap;
uniform vec4 u_LightColor;
uniform float u_LightPower;
uniform vec4  gs_MaterialAmbient;
uniform vec4  gs_MaterialDiffuse;
uniform vec4  gs_MaterialSpecular;

void main(void)
{
    float visibility = 1.0;
    if ( texture2D( u_shadowMap, out_ShadowCoord.xy ).z  <  out_ShadowCoord.z)
    {
        visibility = 0.5;
    }
    vec4 color =
    gs_MaterialAmbient +
    // 拡散光：オブジェクトの色
    visibility * gs_MaterialDiffuse * u_LightColor * u_LightPower +
    // 鏡面光：鏡のように反射するハイライト
    visibility * gs_MaterialSpecular * u_LightColor * u_LightPower;
    out_FragColor=color;
}