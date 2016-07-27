#include "shadow.h"
#include "../shader/shader.h"
#include "../util/util.h"

FrameBuffer* shadowFrame;
DepthBuffer* shadowDepth;
float shadowSize=10;

void initShadow(int width,int height) {
	initDevice(&shadowFrame,&shadowDepth,width,height);
	depthTexture=new Sampler(width,height);

	lightProjectionMatrix=ortho(-shadowSize,shadowSize,-shadowSize,shadowSize,-shadowSize,shadowSize);
	lightViewMatrix=lookAt(lightDir.x, lightDir.y, lightDir.z,
							0, 0, 0,
							0.0f, 1.0f, 0.0f);
}
void releaseShadow() {
	delete depthTexture;
	releaseDevice(&shadowFrame,&shadowDepth);
}

void renderShadowMap(DrawCall renderCall) {
	float tmpX=eyeX; float tmpY=eyeY; float tmpZ=eyeZ; float tmpNear=clipNear;
	eyeX=lightDir.x*2; eyeY=lightDir.y*2; eyeZ=lightDir.z*2; clipNear=-shadowSize;

	clearScreenFast(shadowFrame,255);
	clearDepth(shadowDepth);
	renderCall();
	writeFrameBuffer2Sampler(shadowFrame,depthTexture);

	eyeX=tmpX; eyeY=tmpY; eyeZ=tmpZ; clipNear=tmpNear;
}

