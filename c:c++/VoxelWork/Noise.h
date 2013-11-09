#pragma once
#define _USE_MATH_DEFINES
#include "allHeaders.h"
class Noise
{
	float Basic_Noise(int x, int y, int z);
	float Smoothed_Noise(int x, int y, int z);
	float Interpolate(float a, float b, float x);
	float Interpolated_Noise(float x, float y, float z);
	float Perlin_Noise(float x, float y, float z);
public:
	float density(float x, float y, float z);
	Noise(int size);
	~Noise(void);
};

