#pragma once
#include "BASICSHAPE_TYPE.h"
#include "Type.h"
struct BasicShapeRenderDesc
{
	BasicShapeRenderDesc()
		:type(BASICSHAPE_TYPE::SPHERE),
		mat(),
		color(1,1,1,1)
	{
		mat.identity();
	}

	BASICSHAPE_TYPE type;
	Matrix4 mat;
	Color4 color;
};