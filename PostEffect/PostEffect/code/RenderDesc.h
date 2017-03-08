#pragma once

#include "LightDesc.h"
#include "ID.h"
struct RenderDesc
{
	RenderDesc()
		:meshID(MESH::SPHERE),
		color(1,1,1,1),
		light()
	{
		matrix.identity();
	}
	GSmatrix4 matrix;
	GScolor color;
	MESH meshID;
	LightDesc light;
};