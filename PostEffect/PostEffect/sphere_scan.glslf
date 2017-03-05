#version 330
in vec2 out_TexCoord;
in vec4 out_WorldPosition;
in vec2 out_ScreenPosition;
layout(location = 0) out vec4 out_FragColor;
uniform sampler2D u_sceneColor;
uniform sampler2D u_absWorldPosition;
uniform vec4 u_scanColor;
uniform vec4 u_spherePosition;
uniform vec2 u_screenSize;
uniform float u_sphereRadius;
uniform float u_scanWidht;
uniform float u_blurAmount;
uniform float u_samples[10]={-0.08,-0.05,-0.03,-0.02,-0.01,0.01,0.02,0.03,0.05,0.08};
float inRange(float _value,float _min,float _max)
{
	if(_value<_min)return 1.0;
	if(_value>_max)return 1.0;
	return _value/_max;
};
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
float inSide(in vec4 worldPos)
{
	vec4 v=worldPos-u_spherePosition;
	float p= sqrt(dot(v,v))-u_sphereRadius;    
	return clamp(p,0.0,1.0);
};

void main(void)
{
	vec4 absPos=out_WorldPosition;//texture2D(u_absWorldPosition,out_TexCoord);//
	vec2 center=vec2(0.5,0.5);// out_ScreenPosition/u_screenSize;
	vec2 screenMult=vec2(1.0,1.0);// ViewSize/ScreenResolution(kaizoudo?);
	vec4 radialColor=radialBlur(out_TexCoord,u_blurAmount, screenMult, center);
	vec4 baseColor=texture2D(u_sceneColor,out_TexCoord);
	vec4 color=mix(baseColor,radialColor,inSide(absPos));
	float dist=distance(absPos,u_spherePosition);
	dist-=u_sphereRadius;
	float alpha=1.0-inRange(dist,0.0,u_scanWidht);
	color=mix(color,u_scanColor,alpha);
	out_FragColor=color;
}
