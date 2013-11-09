#include "Camera.h"

void Camera :: MoveL(void)
{
    float temp = this->target.x - this->eye.x;
    this->eye.x -= temp * this->speedX;
    this->target.x -= temp * this->speedX;
  //  this->norm.x -= temp * this->speedX;
}

void Camera :: MoveR(void)
{
    float temp = this->target.x - this->eye.x;
    this->eye.x += temp * this->speedX;
    this->target.x +=temp * this->speedX;
  //  this->norm.x +=temp * this->speedX;
}


void Camera :: MoveF(void)
{
    float temp = this->target.z - this->eye.z;
    this->eye.z -= temp * this->speedZ;
    this->target.z -=temp * this->speedZ;
  //  this->norm.z -=temp * this->speedZ;
}

void Camera :: MoveB(void)
{
    float temp = this->target.z - this->eye.z;
    this->eye.z += temp * this->speedZ;
    this->target.z += temp * this->speedZ;
   // this->norm.z += temp * this->speedZ;
}

void Camera :: MoveUp(void)
{
    float temp = this->target.y - this->eye.y;
    this->eye.y += temp * this->speedY;
    this->target.y += temp * this->speedY;
   // this->norm.y += temp * this->speedY;
}

void Camera :: MoveDown(void)
{
    float temp = this->target.y - this->eye.y;
    this->eye.y -= temp * this->speedY;
    this->target.y -= temp * this->speedY;
   // this->norm.y -= temp * this->speedY;
}


void Camera::LookAt(float x, float y)
{
    this->target.x = x;
    this->target.y = -y;

   // this->norm.x = this->eye.y * this->target.z - this->eye.z * this->target.y;
   // this->norm.y = this->eye.z * this->target.x - this->eye.x * this->target.z;
   // this->norm.z = this->eye.x * this->target.y - this->eye.y * this->target.x;
  //  float n = (float)sqrt(this->norm.x*this->norm.x + this->norm.y * this->norm.y + this->norm.z * this->norm.z);
  //  this->norm.x/=n;
   // this->norm.y/=n;
   // this->norm.z/=n;
}

void Camera::Update(void)
{
    gluLookAt(this->eye.x,this->eye.y,this->eye.z,this->target.x,this->target.y,this->target.z,this->norm.x,this->norm.y,this->norm.z);
}
