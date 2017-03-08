#pragma once
#include <gslib.h>
#include "ID.h"
struct DepthRenderDesc
{
	DepthRenderDesc()
		:meshID(MESH::SPHERE),
		offset(0.25f)
	{
		matrix.identity();
	}
	GSmatrix4 matrix;
	MESH meshID;
	float offset;
};