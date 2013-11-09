#pragma once
#include "allHeaders.h"
#include "Voxel.h"
#include <map.h>

class octTree
{
private:
	void show2(int depth);
public:
	float sX,sY,sZ,minSize;
	int size;
	Voxel *vox;
	octTree **Branchs;
	octTree(void);
	octTree(float x,float y,float z,float sX,float sY,float sZ);
	bool insert(Voxel *vox);
	bool isElem(Voxel *vox);
	bool isElem(float x,float y,float z);
	void show(void);
	bool remove(float x,float y,float z);
	int getBranchN(Voxel *vox,Voxel *root);
	int getBranchN(float x,float y,float z,Voxel *root);
	void drawVoxels(float x0, float y0, float z0, float eye_x, float eye_y, float eye_z);
	~octTree(void);
};

class VoxelMap
{
private:
	float width,height;
	int cX,cY;
	std::map<int, std::map<int,octTree *>> map2d;
public:
	VoxelMap(void);
	VoxelMap(float width,float height);
	bool insert(Voxel *vox);
	bool isElem(Voxel *vox);
	bool isElem(float x,float y,float z);
	void remove(float x,float y,float z);
	void remove(Voxel *vox);
	void drawVoxels(float x0, float y0, float z0, float eye_x, float eye_y, float eye_z);
};
