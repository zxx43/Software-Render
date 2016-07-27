#ifndef SHADOW_H_
#define SHADOW_H_

#include "../graphicLib/sampler.h"
#include "../graphicLib/graphicLib.h"

extern FrameBuffer* shadowFrame;
extern DepthBuffer* shadowDepth;

void initShadow(int width,int height);
void releaseShadow();

void renderShadowMap(DrawCall renderCall);

#endif /* SHADOW_H_ */
