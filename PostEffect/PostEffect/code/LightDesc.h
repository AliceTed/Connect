#pragma once
#include <gslib.h>

struct LightDesc
{
	LightDesc()
		: ambient(1.0f, 1.0f, 1.0f, 1.0f),
		diffuse(1.0f, 1.0f, 1.0f, 1.0f),
		specular(1.0f, 1.0f, 1.0f, 1.0f),
		position(0.0f, 50.0f, 10.0f)
	{
	}
	GScolor ambient;
	GScolor diffuse;
	GScolor specular;
	GSvector3 position;
};