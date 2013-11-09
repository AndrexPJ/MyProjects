#include "octTree.h"

//----------------------------------------
octTree::octTree(void)
{
	this->size = 0;
	this->vox = new Voxel(0,0,0);
	this->Branchs = new octTree*[8];
	for(int i =0;i<8;i++)
		this->Branchs[i] = NULL;
	this->sX = 100;
	this->sY = 100;
	this->sZ = 100;
	this->minSize =0.5;
}
octTree::octTree(float x,float y,float z,float sX,float sY,float sZ)
{
	this->size = 0;
	this->vox = new Voxel( x, y, z);
	this->Branchs = new octTree*[8];
	for(int i =0;i<8;i++)
		this->Branchs[i] = NULL;
	this->sX = sX;
	this->sY = sY;
	this->sZ = sZ;
	this->minSize =0.5;
}
bool octTree::insert(Voxel *vox)
{
	if(vox->size <= 0) return false;

	if((this->sX <= this->minSize) || (this->sY <= this->minSize) || (this->sZ <= this->minSize))
	{
		this->vox = new Voxel(vox);
		return true;
	}
	int N = this->getBranchN(vox,this->vox);
	if(this->Branchs[N] == NULL)
	{
		int Xs,Ys,Zs;
		switch(N)
		{
		case 0:
			{
				Xs = 1;
				Ys = 1;
				Zs = 1;
				break;
			}
		case 1:
			{
				Xs = 1;
				Ys = 1;
				Zs = -1;
				break;
			}
		case 2:
			{
				Xs = 1;
				Ys = -1;
				Zs = 1;
				break;
			}
		case 3:
			{
				Xs = 1;
				Ys = -1;
				Zs = -1;
				break;
			}
		case 4:
			{
				Xs = -1;
				Ys = 1;
				Zs = 1;
				break;
			}
		case 5:
			{
				Xs = -1;
				Ys = 1;
				Zs = -1;
				break;
			}
		case 6:
			{
				Xs = -1;
				Ys = -1;
				Zs = 1;
				break;
			}
		case 7:
			{
				Xs = -1;
				Ys = -1;
				Zs = -1;
				break;
			}
		}

		float nX,nY,nZ;
		nX = this->vox->x + Xs * this->sX/2;
		nY = this->vox->y + Ys * this->sY/2;
		nZ = this->vox->z + Zs * this->sZ/2;
		this->Branchs[N] = new octTree(nX,nY,nZ,this->sX/2,this->sY/2,this->sZ/2);
		return this->Branchs[N]->insert(vox);

	}
	else
	{
	  return this->Branchs[N]->insert(vox);
	}
}
bool octTree::isElem(Voxel *vox)
{
	if((this->sX <= this->minSize) || (this->sY <= this->minSize) || (this->sZ <= this->minSize))
	{
	
		if(*(this->vox) == *vox) return true;
		else return false;
	}
	int N = this->getBranchN(vox,this->vox);

	if(this->Branchs[N])
	{
		return this->Branchs[N]->isElem(vox);
	}
	else return false;
}
bool octTree::isElem(float x,float y,float z)
{
	if((this->sX <= this->minSize) || (this->sY <= this->minSize) || (this->sZ <= this->minSize))
	{
		if(this->vox->x == x && this->vox->y == y && this->vox->z == z) return true;
		else return false;
	}
	int N = this->getBranchN(x,y,z,this->vox);

	if(this->Branchs[N])
	{
		return this->Branchs[N]->isElem(x,y,z);
	}
	else return false;
}
void octTree::show(void)
{
	this->show2(0);
}
void octTree::show2(int depth)
{
	
	for(int i = 7;i>=4;i--)
	{
		if(this->Branchs[i]) this->Branchs[i]->show2(depth+1);
	}
	if(vox->size) {
	std::cout<<std::endl;
	std::cout<<" "<<depth<<" ";
	std::cout<<"["<<this->vox->x<<" "<<this->vox->y<<" "<<this->vox->z<<"]";
	std::cout<<std::endl;
	}
	for(int i = 3;i>=0;i--)
	{
		if(this->Branchs[i]) this->Branchs[i]->show2(depth+1);
	}
}
bool octTree::remove(float x,float y,float z) // bool - возвращаемое значение служебное!!!
{
	// надо ловить утечку памяти
	if(this->vox->size)
	{
		bool c = true;
		for(int i = 0;i<8;i++)
		{
			if(this->Branchs[i])
			{
				c = false;
				break;
			}
		}
		delete this->vox;
		return c;
	}
	int N = this->getBranchN(x,y,z,this->vox);
	if(this->Branchs[N])
	{
		bool ch = this->Branchs[N]->remove(x,y,z);
		if(ch)
		{
			this->Branchs[N] = NULL;
			bool c = true;
			for(int i = 0;i<8;i++)
			{
				if(this->Branchs[i])
				{
				c = false;
				break;
				}
			}
			return c;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}
int octTree::getBranchN(Voxel *vox,Voxel *root)
{
	bool fx = (vox->x>=root->x);
	bool fy = (vox->y>=root->y);
	bool fz = (vox->z>=root->z);
	if(fx)
	{
		if(fy)
		{
			if(fz)
			{
				return 0;
			}
			else
			{
				return 1;
			}
		}
		else
		{
			if(fz)
			{
				return 2;
			}
			else
			{
				return 3;
			}
		}
	}
	else
	{
		if(fy)
		{
			if(fz)
			{
				return 4;
			}
			else
			{
				return 5;
			}
		}
		else
		{
			if(fz)
			{
				return 6;
			}
			else
			{
				return 7;
			}
		}

	}
}
int octTree::getBranchN(float x,float y,float z,Voxel *root)
{
	bool fx = (x>=root->x);
	bool fy = (y>=root->y);
	bool fz = (z>=root->z);
	if(fx)
	{
		if(fy)
		{
			if(fz)
			{
				return 0;
			}
			else
			{
				return 1;
			}
		}
		else
		{
			if(fz)
			{
				return 2;
			}
			else
			{
				return 3;
			}
		}
	}
	else
	{
		if(fy)
		{
			if(fz)
			{
				return 4;
			}
			else
			{
				return 5;
			}
		}
		else
		{
			if(fz)
			{
				return 6;
			}
			else
			{
				return 7;
			}
		}

	}
}
void octTree::drawVoxels(float x0, float y0, float z0, float eye_x, float eye_y, float eye_z)
{
	if(this->vox->size > 0)
	{
		glColor3f(1,0.1,1);
		glVoxelFromValue(this->vox->x,this->vox->y,this->vox->z,2.0,this->vox->faces);
	}
	for(int i =0;i<8;i++)
	{
		if(this->Branchs[i]) this->Branchs[i]->drawVoxels(x0,y0,z0,eye_x,eye_y,eye_z);
	}
}
octTree::~octTree(void)
{
	delete this->vox;
	for(int i =0;i<8;i++)
	{
		if(this->Branchs[i]) this->Branchs[i]->~octTree();
	}
}
//----------------------------------------

//----------------------------------------
VoxelMap::VoxelMap(void)
{
	this->height = 512;
	this->width = 512;
	this->cX = 0;
	this->cY = 0;
}
VoxelMap::VoxelMap(float width,float height)
{
	this->cX = 0;
	this->cY = 0;
	this->height = height;
	this->width = width;
}
bool VoxelMap::insert(Voxel *vox)
{
	float tx = vox->x;
	float tz = vox->z;
	int sX,sZ;
	
	if(tx >= 0) sX = 0.5;
	else sX = -0.5;

	if(tz >= 0) sZ = 0.5;
	else sZ = -0.5;

	int indX = int(tx /(2 * this->width) + sX);
	int indZ = int(tz /(2 * this->height) + sZ);
	
	if(this->map2d[indX][indZ] == NULL)
	{
		this->map2d[indX][indZ] =  new octTree(indX * 2 * this->width, 0 ,indZ * 2 * this->height,this->width,this->height,this->height);
		return this->map2d[indX][indZ]->insert(vox);
	}
	else
	{
		return this->map2d[indX][indZ]->insert(vox);
	}
	
}
bool VoxelMap::isElem(Voxel *vox)
{
	float tx = vox->x;
	float tz = vox->z;
	int sX,sZ;
	
	if(tx >= 0) sX = 0.5;
	else sX = -0.5;

	if(tz >= 0) sZ = 0.5;
	else sZ = -0.5;

	int indX = int(tx /(2 * this->width) + sX);
	int indZ = int(tz /(2 * this->height) + sZ);

	if(this->map2d[indX][indZ] == NULL) return false;
	return this->map2d[indX][indZ]->isElem(vox);
}
bool VoxelMap::isElem(float x,float y,float z)
{
	float tx = x;
	float tz = z;
	int sX,sZ;
	
	if(tx >= 0) sX = 0.5;
	else sX = -0.5;

	if(tz >= 0) sZ = 0.5;
	else sZ = -0.5;

	int indX = int(tx /(2 * this->width) + sX);
	int indZ = int(tz /(2 * this->height) + sZ);
	if(this->map2d[indX][indZ] == NULL) return false;
	return this->map2d[indX][indZ]->isElem(x,y,z);
}
void VoxelMap::remove(float x,float y,float z)
{
	int sX,sZ;
	
	if(x >= 0) sX = 0.5;
	else sX = -0.5;

	if(z >= 0) sZ = 0.5;
	else sZ = -0.5;

	int indX = int(x /(2 * this->width) + sX);
	int indZ = int(z /(2 * this->height) + sZ);
	if(this->map2d[indX][indZ] == NULL) return;
	this->map2d[indX][indZ]->remove(x,y,z);
}
void VoxelMap::remove(Voxel *vox)
{
	float x = vox->x;
	float y = vox->y;
	float z = vox->z;
	int sX,sZ;
	
	if(x >= 0) sX = 0.5;
	else sX = -0.5;

	if(z >= 0) sZ = 0.5;
	else sZ = -0.5;

	int indX = int(x /(2 * this->width) + sX);
	int indZ = int(z /(2 * this->height) + sZ);
	if(this->map2d[indX][indZ] == NULL) return;
	this->map2d[indX][indZ]->remove(x,y,z);
}
void VoxelMap::drawVoxels(float x0, float y0, float z0, float eye_x, float eye_y, float eye_z)
{
	int sX,sZ;
	
	if(x0 >= 0) sX = 0.5;
	else sX = -0.5;

	if(z0 >= 0) sZ = 0.5;
	else sZ = -0.5;

	int indX = int(x0 /(2 * this->width) + sX);
	int indZ = int(z0 /(2 * this->height) + sZ);
	if(this->map2d[indX][indZ])
	{
		glVoxelBegin();
			this->map2d[indX][indZ]->drawVoxels(x0,y0,z0,eye_x,eye_y,eye_z);
		glVoxelEnd();
	}
	else return;
}

//----------------------------------------
