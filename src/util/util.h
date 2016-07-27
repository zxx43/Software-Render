#ifndef UTIL_H_
#define UTIL_H_

#include "../Maths/Maths.h"

#define PI 3.1415926
#define PI2 6.2831852
#define A2R 0.01745329222 //角度转弧度
#define R2A 57.2957804905 //弧度转角度

MATRIX4X4 lookAt(float eyeX, float eyeY, float eyeZ,
		float centerX, float centerY, float centerZ,
		float upX, float upY, float upZ);
MATRIX4X4 perspective(float fovy,float aspect,float zNear,float zFar);
MATRIX4X4 ortho(float left, float right, float bottom, float top, float n, float f);
int project(float objX, float objY, float objZ,
		const float* model, const float* proj, const int* view,
		float* winX, float* winY, float* winZ);
MATRIX4X4 rotateX(float angle);
MATRIX4X4 rotateY(float angle);
MATRIX4X4 rotateZ(float angle);
MATRIX4X4 scale(float size);
MATRIX4X4 translate(float tx,float ty,float tz);
VECTOR4D mul(VECTOR4D a,VECTOR4D b);

void interpolate3f(float pa,float pb,float pc,
		float a,float b,float c,
		float& result);
void interpolate2f(float pa,float pb,
		float a,float b,
		float& result);

float calcZPara(float v1z,float v2z,float z);
VECTOR3D calcParaEqu(VECTOR3D vect1,VECTOR3D vect2,float param);

inline float roundf(float number) {
	return number < 0.0 ? ceilf(number - 0.5) : floorf(number + 0.5);
}

#endif /* UTIL_H_ */
