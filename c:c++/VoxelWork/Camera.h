#ifndef CAMERA_H
#define CAMERA_H
#include "allHeaders.h"
class Camera
{
public:
  float speedX,speedY,speedZ;
  Vector3D target,norm,eye;
  Camera(void)
  {
      Vector3D e = {0.0,0.0,0.5};
      Vector3D t = {0.0,0.0,-0.5};
      Vector3D n = {0.0,1.0,0.0};
      this->eye = e;
      this->target =  t;
      this->norm = n;
      this->speedX = 0.5;
      this->speedY = 0.5;
      this->speedZ = 0.5;
  }
  Camera(Vector3D e,Vector3D n,Vector3D t)
  {
    this->eye = e;
    this->norm = n;
    this->target = t;
  }

  void MoveL(void);
  void MoveR(void);
  void MoveF(void);
  void MoveB(void);
  void MoveUp(void);
  void MoveDown(void);

  void LookAt(float x,float y);

  void Update(void);

};



#endif // CAMERA_H
