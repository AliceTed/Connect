#pragma once

enum class TEX
{
	ROCK,
	ROCK_NORM,

};

enum class MESH
{
	SPHERE,
	PLANE
};

enum class RENDER_TARGET
{
	BASE,
	DEPTHMAP,
	GAUSSIAN_ROW,
	GAUSSIAN_HIGH,
	SHADOWMAP,
	DOF,
	RADIAL_BLUR
};

enum class SHADER
{
	SPHERE,
	GAUSSIAN,
	DEPTHMAP,
	DOF,
	BRIGHT,
	BLOOM,
	BLOOM_SYNTHESIS,
	SPHERE_SCAN,
	ABSOLUTE_WORLD_POSITION,
	SHADOWMAP,
	SHADOW,
	RADIAL_BLUR
};

template<class ID>
unsigned int Cast(ID _id)
{
	return static_cast<unsigned int>(_id);
}