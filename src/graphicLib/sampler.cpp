#include "sampler.h"

Sampler::Sampler(int sw,int sh) {
	width=sw;
	height=sh;
	imgData=new unsigned char[width*height*3];
	memset(imgData,0,width*height*3*sizeof(unsigned char));
}

Sampler::~Sampler() {
	delete[] imgData;
	printf("release sampler\n");
}

VECTOR4D Sampler::texture2D(float s,float t) {
	VECTOR4D color(1,1,1,1);
	float u=(float)(width-1)*s;
	float v=(float)(height-1)*(1.0-t);
	int iu=(int)u;
	int iv=(int)v;
	int uNext=iu+1<=(width-1)?iu+1:iu;
	int vNext=iv+1<=(height-1)?iv+1:iv;

	float uNextPer=u-iu;
	float vNextPer=v-iv;
	float uPer=1.0-uNextPer;
	float vPer=1.0-vNextPer;

	int imgIndex=3*(iv*width+iu);
	color.x=(float)imgData[imgIndex]*INV_SCALE;
	color.y=(float)imgData[imgIndex+1]*INV_SCALE;
	color.z=(float)imgData[imgIndex+2]*INV_SCALE;
	
	int imgIndexNextU=3*(iv*width+uNext);
	int imgIndexNextV=3*(vNext*width+iu);
	int imgIndexNextUV=3*(vNext*width+uNext);

	VECTOR4D colorNextU(1,1,1,1),colorNextV(1,1,1,1),colorNextUV(1,1,1,1);
	colorNextU.x=(float)imgData[imgIndexNextU]*INV_SCALE;
	colorNextU.y=(float)imgData[imgIndexNextU+1]*INV_SCALE;
	colorNextU.z=(float)imgData[imgIndexNextU+2]*INV_SCALE;
	colorNextV.x=(float)imgData[imgIndexNextV]*INV_SCALE;
	colorNextV.y=(float)imgData[imgIndexNextV+1]*INV_SCALE;
	colorNextV.z=(float)imgData[imgIndexNextV+2]*INV_SCALE;
	colorNextUV.x=(float)imgData[imgIndexNextUV]*INV_SCALE;
	colorNextUV.y=(float)imgData[imgIndexNextUV+1]*INV_SCALE;
	colorNextUV.z=(float)imgData[imgIndexNextUV+2]*INV_SCALE;

	color.x=color.x*uPer*vPer+colorNextU.x*uNextPer*vPer+colorNextV.x*uPer*vNextPer+colorNextUV.x*uNextPer*vNextPer;
	color.y=color.y*uPer*vPer+colorNextU.y*uNextPer*vPer+colorNextV.y*uPer*vNextPer+colorNextUV.y*uNextPer*vNextPer;
	color.z=color.z*uPer*vPer+colorNextU.z*uNextPer*vPer+colorNextV.z*uPer*vNextPer+colorNextUV.z*uNextPer*vNextPer;
	
	return color;
}

void writeFrameBuffer2Sampler(FrameBuffer* fb,Sampler* sampler) {
	for(int i=0;i<fb->height;i++) {
		for(int j=0;j<fb->width;j++) {
			int index=(i*fb->width+j)*3;
			sampler->imgData[((i)*fb->width+j)*3]=fb->colorBuffer[index];
			sampler->imgData[((i)*fb->width+j)*3+1]=fb->colorBuffer[index+1];
			sampler->imgData[((i)*fb->width+j)*3+2]=fb->colorBuffer[index+2];
		}
	}
}
