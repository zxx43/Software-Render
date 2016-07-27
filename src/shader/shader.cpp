#include "shader.h"

MATRIX4X4 modelMatrix,viewMatrix,projectMatrix,
lightProjectionMatrix,lightViewMatrix;
VECTOR4D lightDir,amb,diff,ambMat,diffMat;
Sampler* currTexture=NULL;
Sampler* depthTexture=NULL;

void vertexShader(Vertex input,VertexOut& output) {
	MATRIX4X4 mv=viewMatrix*modelMatrix;
	MATRIX4X4 mvp=projectMatrix*mv;
	VECTOR4D modelVert(input.x,input.y,input.z,input.w);
	VECTOR4D worldVert=modelMatrix*modelVert;
	VECTOR4D viewVert=mv*modelVert;
	VECTOR4D clipVert=mvp*modelVert;

	VECTOR4D modelNormal(input.nx,input.ny,input.nz,0.0);
	VECTOR4D worldNormal=modelMatrix*modelNormal;

	output.x=clipVert.x;
	output.y=clipVert.y;
	output.z=clipVert.z;
	output.w=clipVert.w;

	output.wx=worldVert.x;
	output.wy=worldVert.y;
	output.wz=worldVert.z;
	output.ww=worldVert.w;

	output.vx=viewVert.x;
	output.vy=viewVert.y;
	output.vz=viewVert.z;
	output.vw=viewVert.w;

	output.nx=worldNormal.x;
	output.ny=worldNormal.y;
	output.nz=worldNormal.z;

	output.s=input.s;
	output.t=input.t;
}

void fragmentShader(Fragment input,FragmentOut& output) {
	VECTOR3D worldNormal(input.nx,input.ny,input.nz);
	worldNormal.Normalize();
	VECTOR3D worldLightDir(lightDir.x,lightDir.y,lightDir.z);
	worldLightDir.Normalize();
	float nDotL=worldLightDir.DotProduct(worldNormal);
	nDotL=max(nDotL,0.0);

	VECTOR4D lightColor=mul(amb,ambMat)+mul(diff,diffMat)*nDotL;
	float shadowFactor=1;

	VECTOR4D shadowVert(input.wx,input.wy,input.wz,input.ww);
	shadowVert=lightProjectionMatrix*lightViewMatrix*shadowVert;
	float invShadowVertW=1.0/shadowVert.w;
	shadowVert.x*=invShadowVertW;
	shadowVert.y*=invShadowVertW;
	shadowVert.z*=invShadowVertW;
	float bias=0.00001;
	if(shadowVert.x<=1&&shadowVert.x>=-1&&
			shadowVert.y<=1&&shadowVert.y>=-1&&
			shadowVert.z<=1&&shadowVert.z>=-1) {
		shadowVert.x=0.5*(shadowVert.x+1);
		shadowVert.y=0.5*(shadowVert.y+1);
		shadowVert.z=0.5*(shadowVert.z+1);
		float depthStore=depthTexture->texture2D(shadowVert.x,shadowVert.y).x;
		float depthNow=shadowVert.z+bias;
		if(depthNow>depthStore)
			shadowFactor=0.5;
	}
	lightColor*=shadowFactor;

	VECTOR4D texColor(1,1,1,1);
	if(currTexture!=NULL)
		texColor=currTexture->texture2D(input.s,input.t)*1.2;

	output.r=texColor.x*lightColor.x;
	output.g=texColor.y*lightColor.y;
	output.b=texColor.z*lightColor.z;
	output.a=texColor.w*lightColor.w;
}

void simpleFragShader(Fragment input,FragmentOut& output) {
	VECTOR3D worldNormal(input.nx,input.ny,input.nz);
	worldNormal.Normalize();
	VECTOR3D worldLightDir(lightDir.x,lightDir.y,lightDir.z);
	worldLightDir.Normalize();
	float nDotL=worldLightDir.DotProduct(worldNormal);
	nDotL=max(nDotL,0.0);

	VECTOR4D lightColor=mul(amb,ambMat)+mul(diff,diffMat)*nDotL;
	VECTOR4D texColor(1,1,0,1);
	texColor*=1.2;

	output.r=texColor.x*lightColor.x;
	output.g=texColor.y*lightColor.y;
	output.b=texColor.z*lightColor.z;
	output.a=0.6;
}

void storeVertShader(Vertex input,VertexOut& output) {
	MATRIX4X4 mv=lightViewMatrix*modelMatrix;
	MATRIX4X4 mvp=lightProjectionMatrix*mv;
	VECTOR4D modelVert(input.x,input.y,input.z,input.w);
	VECTOR4D worldVert=modelMatrix*modelVert;
	VECTOR4D viewVert=mv*modelVert;
	VECTOR4D clipVert=mvp*modelVert;

	VECTOR4D modelNormal(input.nx,input.ny,input.nz,0.0);
	VECTOR4D worldNormal=modelMatrix*modelNormal;

	output.x=clipVert.x;
	output.y=clipVert.y;
	output.z=clipVert.z;
	output.w=clipVert.w;

	output.wx=worldVert.x;
	output.wy=worldVert.y;
	output.wz=worldVert.z;
	output.ww=worldVert.w;

	output.vx=viewVert.x;
	output.vy=viewVert.y;
	output.vz=viewVert.z;
	output.vw=viewVert.w;

	output.nx=worldNormal.x;
	output.ny=worldNormal.y;
	output.nz=worldNormal.z;
}
void storeFragShader(Fragment input,FragmentOut& output) {
	output.r=input.ndcZ*0.5+0.5;
	output.g=input.ndcZ*0.5+0.5;
	output.b=input.ndcZ*0.5+0.5;
	output.a=input.ndcZ*0.5+0.5;
}
