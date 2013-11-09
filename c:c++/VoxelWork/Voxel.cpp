#include "allHeaders.h"

static char voxelValue = 63;
static bool isBegin = false;
static const GLint voxelCoords[24] = {-1, -1, 1,
                                       1, -1, 1,
                                       1,  1, 1,
                                      -1,  1, 1,
                                      -1, -1, -1,
                                      -1,  1, -1,
                                       1,  1, -1,
                                       1, -1, -1};
static const GLfloat normalCoords[6][3] =
{
    { 0.0, 0.0, 1.0},//front
    { 0.0, 0.0,-1.0},//back
    { 0.0, 1.0, 0.0},//top
    { 0.0,-1.0, 0.0},//bottom
    { 1.0, 0.0, 0.0},//rigth
    {-1.0, 0.0, 0.0} //left

};

static const GLubyte faceCoords[6][4] =
{
  {0,1,2,3}, //front
  {4,5,6,7}, //back
  {5,3,2,6}, //top
  {4,7,1,0}, //bottom
  {7,6,2,1}, //rigth
  {4,0,3,5}  //left
};


void glVoxelBegin(void)
{
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3,GL_INT,0,voxelCoords);
    isBegin = true;
}

void glVoxelEnd(void)
{
    glFlush();
    isBegin = false;
}

void glVoxelValueSet(char x)
{
    voxelValue = x;
}

void glVoxelValueSet(bool top, bool bottom, bool left, bool right, bool back, bool front)
{
    voxelValue = 0;
    voxelValue = front << 0 | right << 1 | bottom << 2 | back << 3 | left << 4 | top << 5 ;
}

char glVoxelValue(void)
{
    return voxelValue;
}

char glVoxelValue(bool top,bool bottom,bool left,bool right,bool back,bool front)
{
    char out = 0;
    return out = front << 0 | right << 1 | bottom << 2 | back << 3 | left << 4 | top << 5 ;
}


void glVoxel(float x, float  y, float z, float size)
{
    if(!isBegin) return;
    char mask = 32;
    glPushMatrix();
    glTranslatef(x, y, z);
    glScalef(size, size, size);
    for(int i=0;i<6;i++)
        {
            if(mask&voxelValue)
            {
            glNormal3fv(normalCoords[i]);
            glDrawElements (GL_QUADS, 4, GL_UNSIGNED_BYTE, faceCoords[i]);
            }
            mask>>=1;
        }
    glPopMatrix();
	
}

void glVoxelFull(float x, float  y, float z, float size)
{
    if(!isBegin) return;
    glPushMatrix();
    glTranslatef(x, y, z);
    glScalef(size, size, size);
    for(int i=0;i<6;i++)
    {
        glNormal3fv(normalCoords[i]);
        glDrawElements (GL_QUADS, 4, GL_UNSIGNED_BYTE, faceCoords[i]);
    }
    glPopMatrix();
}

void glVoxelFromValue(float x, float  y, float z, float size,char value)
{
    if(!isBegin) return;
    glPushMatrix();
    glTranslatef(x, y, z);
    glScalef(size, size, size);
    for(int i=0;i<6;i++)
        {
            if(value&voxelValue)
            {
                glNormal3fv(normalCoords[i]);
                glDrawElements (GL_QUADS, 4, GL_UNSIGNED_BYTE, faceCoords[i]);
            }
            value>>=1;
        }
    glPopMatrix();

}

