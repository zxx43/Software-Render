#include "objects.h"

Texture* texWood;
Texture* texGround;
Cube* cube;
Square* square;
Sphere* sphere;

void initUniforms() {
	lightDir.x=-2.0; lightDir.y=2.0; lightDir.z=-1.0; lightDir.w=0.0;
	amb.x=0.72; amb.y=0.72; amb.z=0.72; amb.w=1.0;
	diff.x=0.7; diff.y=0.7; diff.z=0.7; diff.w=1.0;
	ambMat.x=0.72; ambMat.y=0.72; ambMat.z=0.72; ambMat.w=1.0;
	diffMat.x=0.7; diffMat.y=0.7; diffMat.z=0.7; diffMat.w=1.0;
}

void initCube() {
	cube=new Cube();
}
void releaseCube() {
	delete cube;
}
void renderCube() {
	modelMatrix.LoadIdentity();
	MATRIX4X4 rotMat=rotateY(30);
	MATRIX4X4 transMat=translate(0,1,0);
	MATRIX4X4 scaleMat=scale(1);
	modelMatrix=transMat*rotMat*scaleMat;
	currTexture=texWood->sampler;
	cube->render(frontBuffer,depthBuffer,vertexShader,fragmentShader,CULL_BACK);
}
void renderCubeShadow() {
	modelMatrix.LoadIdentity();
	MATRIX4X4 rotMat=rotateY(30);
	MATRIX4X4 transMat=translate(0,1,0);
	MATRIX4X4 scaleMat=scale(1);
	modelMatrix=transMat*rotMat*scaleMat;
	cube->render(shadowFrame,shadowDepth,storeVertShader,storeFragShader,CULL_FRONT);
}

void initSquare() {
	square=new Square();
}
void releaseSquare() {
	delete square;
}
void renderSquare() {
	modelMatrix.LoadIdentity();
	MATRIX4X4 transMat=translate(0,0,0);
	MATRIX4X4 scaleMat=scale(50);
	modelMatrix=transMat*scaleMat;
	currTexture=texGround->sampler;
	square->render(frontBuffer,depthBuffer,vertexShader,fragmentShader,CULL_BACK);
}

void initSphere() {
	sphere=new Sphere(16,16);
}
void releaseSphere() {
	delete sphere;
}
void renderSphere() {
	//blendFlag=true;
	modelMatrix.LoadIdentity();
	MATRIX4X4 transMat=translate(-2,3,2);
	modelMatrix=transMat;
	currTexture=texGround->sampler;
	sphere->render(frontBuffer,depthBuffer,vertexShader,simpleFragShader,CULL_BACK);
	//blendFlag=false;
}
void renderSphereShadow() {
	modelMatrix.LoadIdentity();
	MATRIX4X4 transMat=translate(-2,3,2);
	modelMatrix=transMat;
	sphere->render(shadowFrame,shadowDepth,storeVertShader,storeFragShader,CULL_FRONT);
}

void renderShadow() {
	renderCubeShadow();
	renderSphereShadow();
}
