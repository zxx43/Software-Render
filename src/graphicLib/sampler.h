#ifndef SAMPLER_H_
#define SAMPLER_H_

#include "../texture/BmpLoader.h"
#include "../Maths/Maths.h"
#include "../header/header.h"

class Sampler {
private:
	int width,height;
public:
	unsigned char* imgData;

	Sampler(int sw,int sh);
	~Sampler();
	VECTOR4D texture2D(float s,float t);
};

void writeFrameBuffer2Sampler(FrameBuffer* fb,Sampler* sampler);

#endif /* SAMPLER_H_ */
