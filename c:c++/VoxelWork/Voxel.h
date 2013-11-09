//!!!!!! needs OpenGL lib !!!!!! #include <...> 

#include "allHeaders.h"
//-------------------------

//-------------------------


//---set voxel verges------
void glVoxelValueSet(char x);
void glVoxelValueSet(bool top,bool bottom,bool left,bool right,bool back,bool front);
//-------------------------

//---get voxel verges------
char glVoxelValue(void);
char glVoxelValue(bool top,bool bottom,bool left,bool right,bool back,bool front);
//-------------------------

//---paint voxel from val--
void glVoxel(float x,float y,float z,float size);
//-------------------------

void glVoxelBegin(void);
void glVoxelEnd(void);

//---paint full voxel------
void glVoxelFull(float x,float y,float z,float size);
//-------------------------

//---paint voxel from val--
void glVoxelFromValue(float x,float y,float z,float size,char value);
//-------------------------


class Voxel
{
public:
	float x,y,z;
	float size;
	float density;
	char faces;
	Voxel(void)
	{
		this->size = 0;
	}
	Voxel(float x,float y,float z)
	{
		this->size = 0;
		this->x = x;
		this->y = y;
		this->z = z;
	}
	Voxel(float x,float y,float z,float size)
	{
		this->size = size;
		this->x = x;
		this->y = y;
		this->z = z;
	}
	Voxel(Voxel *vox)
	{
		this->size = vox->size;
		this->x = vox->x;
		this->y = vox->y;
		this->z = vox->z;
	}
	bool operator==(Voxel &b)
	{
		return (this->x == b.x) && (this->y == b.y) && (this->z == b.z);
	}
	bool operator!=(Voxel &b)
	{
		return !(*this == b);
	}
};