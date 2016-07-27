#include "frame.h"
#include "objects.h"
#include "sight/sight.h"

Sight* sight=NULL;
void buildCamera() {
	MATRIX4X4 trans,rotX,rotY;
	rotX=rotateX(sight->yrot);
	rotY=rotateY(sight->xrot);
	trans=translate(sight->sx,sight->sy,sight->sz);
	viewMatrix=rotX*rotY*trans;
}

void draw() {
	clearScreen(frontBuffer,128,178,204);
//	clearScreenFast(frontBuffer,200);
	clearDepth(depthBuffer);

	buildCamera();
	modelMatrix.LoadIdentity();

	renderShadowMap(renderShadow);

	renderCube();
	renderSquare();
	renderSphere();

//	flush(frontBuffer);
	swapBuffer();
}

void buildProjectMatrix(int w,int h) {
	clipNear=1;
	float fAspect=(float)w/(float)h;
	projectMatrix=perspective(60.0,fAspect,clipNear,100.0);
}

void initTextures() {
	texWood=new Texture("../texture/cube24.bmp");
	texGround=new Texture("../texture/ground24.bmp");
	if(!texWood->sampler&&!texGround->sampler) {
		delete texWood;
		delete texGround;
		texWood=new Texture("texture/cube24.bmp");
		texGround=new Texture("texture/ground24.bmp");
	}
}
void releaseTextures() {
	delete texWood;
	delete texGround;
}

void init() {
	initFixFace();
	initUniforms();
	initTextures();
	initShadow(256,256);
	initCube();
	initSquare();
	initSphere();

	eyeX=-2; eyeY=2; eyeZ=-4;
	sight=new Sight(-eyeX,-eyeY,-eyeZ);
	sight->xrot=180;
	sight->yrot=-10;
	initKeys();
}

void release() {
	releaseKeys();
	delete sight;

	releaseSphere();
	releaseSquare();
	releaseCube();
	releaseShadow();
	releaseTextures();
	releaseFixFace();
	releaseDevice2Buf(&frameBuffer1,&frameBuffer2,&depthBuffer);
}

void resize(int width,int height) {
	releaseDevice2Buf(&frameBuffer1,&frameBuffer2,&depthBuffer);
	initDevice2Buf(&frameBuffer1,&frameBuffer2,&depthBuffer,width,height);
	buildProjectMatrix(width,height);
}

void act() {
	if(sight!=NULL) {
		if(move[0])
			sight->moveSight(MNEAR,D_DISTANCE);
		if(move[1])
			sight->moveSight(MFAR,D_DISTANCE);
		if(move[2])
			sight->moveSight(LEFT,D_DISTANCE);
		if(move[3])
			sight->moveSight(RIGHT,D_DISTANCE);
		if(move[4])
			sight->moveSight(UP,D_DISTANCE);
		if(move[5])
			sight->moveSight(DOWN,D_DISTANCE);
		if(turn[0])
			sight->turnY(UP);
		if(turn[1])
			sight->turnY(DOWN);
		if(turn[2])
			sight->turnX(LEFT);
		if(turn[3])
			sight->turnX(RIGHT);
		eyeZ=-sight->sz;
		eyeX=-sight->sx;
		eyeY=-sight->sy;
	}
}
