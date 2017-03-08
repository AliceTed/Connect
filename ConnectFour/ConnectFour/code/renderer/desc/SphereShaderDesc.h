#pragma once
/**
* @file SphereShaderDesc.h
* @brief スフィアシェーダ描画記述子
* @author 松尾裕也
* @date 2016/3/5
*/
#include <gslib.h>
#include "LightDesc.h"
struct SphereShaderDesc
{
	SphereShaderDesc()
		:meshID(0),
		color(1.0f, 1.0f, 1.0f, 1.0f),
		light(),
		isWave(false),
		time(0)
	{
		matrix.identity();
	}
	unsigned int meshID;
	GSmatrix4 matrix;
	GScolor color;
	LightDesc light;
	bool isWave;
	float time;
};