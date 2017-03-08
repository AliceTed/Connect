#version 330
in vec4 out_position;
layout(location = 0) out vec4 out_FragColor;
uniform float u_depthOffset;

const float near = 0.1;
const float far  = 30.0;
const float linerDepth = 1.0 / (far - near);

vec4 convRGBA(float depth)
{
    float r = depth;
    float g = fract(r * 255.0);
    float b = fract(g * 255.0);
    float a = fract(b * 255.0);
    float coef = 1.0 / 255.0;
    r -= g * coef;
    g -= b * coef;
    b -= a * coef;
    return vec4(r, g, b, a);
}

float convCoord(float depth, float offset){
    float d = clamp(depth + offset, 0.0, 1.0);
    if(d > 0.6){
        d = 2.5 * (1.0 - d);
    }else if(d >= 0.4){
        d = 1.0;
    }else{
        d *= 2.5;
    }
    return d;
}
void main(void) 
{
	float liner = linerDepth * length(out_position);
    vec4  convColor = convRGBA(convCoord(liner, u_depthOffset));
	out_FragColor = convColor;
}
