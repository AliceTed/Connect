#version 330
in vec2 out_TexCoord;
layout(location = 0) out vec4 out_FragColor;

uniform float u_blurAmount;
uniform sampler2D u_sceneColor;
uniform vec2 u_center={0.5,0.5};
uniform vec2 u_screenMult={1.0,1.0};
uniform float u_samples[10]={-0.08,-0.05,-0.03,-0.02,-0.01,0.01,0.02,0.03,0.05,0.08};
vec4 radialBlur(in vec2 uv,float amount,in vec2 screenMult,in vec2 offset)
{
	vec2 dir = screenMult * offset - uv; 
	vec4 sum = texture2D(u_sceneColor,uv);
	vec2 pos = vec2(0.0);
	for(int i = 0; i<10; i++)
	{
		pos = uv + dir * u_samples[i] * amount;
		pos=max(min(pos, screenMult * vec2(1.0,1.0)), vec2(0.0,0.0));
		sum += texture2D(u_sceneColor,pos);
	}
	sum *= 1.0/11.0;
	return sum;
};
void main(void)
{
	out_FragColor=radialBlur(out_TexCoord,u_blurAmount, u_screenMult, u_center);;
}
