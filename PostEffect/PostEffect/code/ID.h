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
	GAUSSIAN_HIGH
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
	ABSOLUTE_WORLD_POSITION
};

template<class ID>
unsigned int Cast(ID _id)
{
	return static_cast<unsigned int>(_id);
}