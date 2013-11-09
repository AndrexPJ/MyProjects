#include "stdafx.h"
#include "Noise.h"
float Noise::Basic_Noise(int x, int y, int z)
{
	int n = x + y * 57 + z * 7;
    n = (n<<10) ^ n;
    return (( (n * (n * n * 15731 + 789221) + 1376312589) & 0x7fffffff) / 1073741824.0)/2;  
}
float Noise::Smoothed_Noise(int x, int y, int z)
{
	/*float corners = (Basic_Noise(x-1, y-1,z-1)+Basic_Noise(x+1, y-1,z-1)+Basic_Noise(x-1, y+1,z-1)+Basic_Noise(x+1, y+1,z-1)+Basic_Noise(x-1, y-1,z+1)+Basic_Noise(x+1, y-1,z+1)+Basic_Noise(x-1, y+1,z+1)+Basic_Noise(x+1, y+1,z+1)) / 32;
	float sides   = (Basic_Noise(x-1, y, z-1)+Basic_Noise(x+1, y, z-1)+Basic_Noise(x, y-1, z-1)+Basic_Noise(x, y+1, z-1)+ Basic_Noise(x-1, y, z+1)+Basic_Noise(x+1, y, z+1)+Basic_Noise(x, y-1, z+1)+Basic_Noise(x, y+1, z+1)+Basic_Noise(x-1, y-1, z)+Basic_Noise(x+1, y-1, z)+Basic_Noise(x+1, y+1, z)+Basic_Noise(x-1, y+1, z)) /  48;
	float centers  = (Basic_Noise(x, y, z-1)+Basic_Noise(x, y, z+1)+Basic_Noise(x, y-1, z)+Basic_Noise(x, y+1, z)+Basic_Noise(x-1, y, z)+Basic_Noise(x+1, y, z))/ 24;
	float point = Basic_Noise(x, y, z)/4;*/
	float centers  = (Basic_Noise(x, y, z-1)+Basic_Noise(x, y, z+1)+Basic_Noise(x, y-1, z)+Basic_Noise(x, y+1, z)+Basic_Noise(x-1, y, z)+Basic_Noise(x+1, y, z))/ 12;
	float point = Basic_Noise(x, y, z)/2;
	//return corners + sides + centers + point;
	return centers + point;
}
float Noise::Interpolate(float a, float b, float x)
{
	float ft = float(x * M_PI);
	float f = (1 - cos(ft))/2;
	return  a*(1-f) + b*f;
}
float Noise::Interpolated_Noise(float x, float y, float z)
{
	int integer_X    = int(x);
	float fractional_X = x - integer_X;
	int integer_Y    = int(y);
	float fractional_Y = y - integer_Y;
	int integer_Z    = int(z);
	float fractional_Z = y - integer_Z;
	float v1 = Smoothed_Noise(integer_X,     integer_Y, integer_Z);
	float v2 = Smoothed_Noise(integer_X + 1, integer_Y, integer_Z);
	float v3 = Smoothed_Noise(integer_X,     integer_Y + 1, integer_Z);
	float v4 = Smoothed_Noise(integer_X + 1, integer_Y + 1, integer_Z);
	float v5 = Smoothed_Noise(integer_X,     integer_Y, integer_Z + 1);
	float v6 = Smoothed_Noise(integer_X + 1, integer_Y, integer_Z + 1);
	float v7 = Smoothed_Noise(integer_X,     integer_Y + 1, integer_Z + 1);
	float v8 = Smoothed_Noise(integer_X + 1, integer_Y + 1, integer_Z + 1);
	float i1 = Interpolate(v1 , v2 , fractional_X);
	float i2 = Interpolate(v3 , v4 , fractional_X);
	float i3 = Interpolate(v5 , v6 , fractional_X);
	float i4 = Interpolate(v7 , v8 , fractional_X);
	float j1 = Interpolate(i1 , i2 , fractional_Y);
	float j2 = Interpolate(i3 , i4 , fractional_Y);
	float rez = Interpolate(j1 , j2 , fractional_Z);
	return rez;
}
float Noise::Perlin_Noise(float x, float y, float z)
{
	float frequency, amplitude;
	float total = 0;
	int p = 1;
	int n = 1;
	for(int i = 0; i < n; i++)
	{
		frequency = float(2 ^ i);
		amplitude = float(p ^ i);
		total = total + Interpolated_Noise(x * frequency/100, y * frequency/100, z * frequency/100) * amplitude;
	}
	return total;
}
float Noise::density(float x, float y, float z)
{
				if(z == 0) return 1;
				else return Perlin_Noise(x, y, z) - z/100;
}
Noise::Noise(int size)
{
}

Noise::~Noise(void)
{
}
