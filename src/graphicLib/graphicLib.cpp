#include "graphicLib.h"
#include "../shader/shader.h"

float eyeX,eyeY,eyeZ,clipNear;
Face* nFace1;
Face* nFace2;
bool blendFlag=false;
FrameBuffer* frontBuffer=NULL;
FrameBuffer* backBuffer=NULL;
FrameBuffer* frameBuffer1=NULL;
FrameBuffer* frameBuffer2=NULL;
DepthBuffer* depthBuffer=NULL;
bool buffersReady=false;

unsigned char* screenBits=NULL;

void initFrameBuffer(FrameBuffer** pfb,int width,int height) {
	*pfb=(FrameBuffer*)malloc(sizeof(FrameBuffer));
	(*pfb)->width=width; (*pfb)->height=height;
	(*pfb)->colorBuffer=new unsigned char[width*height*3];
	memset((*pfb)->colorBuffer,0,sizeof(unsigned char)*width*height*3);
}
void releaseFrameBuffer(FrameBuffer** pfb) {
	if(*pfb==NULL)
		return;
	delete[] (*pfb)->colorBuffer;
	free(*pfb);
	*pfb=NULL;
}

void initDepthBuffer(DepthBuffer** pdb,int width,int height) {
	*pdb=(DepthBuffer*)malloc(sizeof(DepthBuffer));
	(*pdb)->width=width; (*pdb)->height=height;
	(*pdb)->depthBuffer=new float[width*height];
	memset((*pdb)->depthBuffer,0,sizeof(float)*width*height);
}
void releaseDepthBuffer(DepthBuffer** pdb) {
	if(*pdb==NULL)
		return;
	delete[] (*pdb)->depthBuffer;
	free(*pdb);
	*pdb=NULL;
}

void initDevice(FrameBuffer** pfb,DepthBuffer** pdb,int width,int height) {
	initFrameBuffer(pfb,width,height);
	initDepthBuffer(pdb,width,height);
}

void releaseDevice(FrameBuffer** pfb,DepthBuffer** pdb) {
	releaseFrameBuffer(pfb);
	releaseDepthBuffer(pdb);
}

void initDevice2Buf(FrameBuffer** pfb1,FrameBuffer** pfb2,DepthBuffer** pdb,int width,int height) {
	initFrameBuffer(pfb1,width,height);
	initFrameBuffer(pfb2,width,height);
	initDepthBuffer(pdb,width,height);
	frontBuffer=*pfb1;
	backBuffer=*pfb2;
	buffersReady=false;
}

void releaseDevice2Buf(FrameBuffer** pfb1,FrameBuffer** pfb2,DepthBuffer** pdb) {
	frontBuffer=NULL;
	backBuffer=NULL;
	releaseFrameBuffer(pfb1);
	releaseFrameBuffer(pfb2);
	releaseDepthBuffer(pdb);
}

void clearScreen(FrameBuffer* fb,unsigned char red,unsigned char green,unsigned char blue) {
	for(int i=0;i<fb->height;i++) {
		for(int j=0;j<fb->width;j++) {
			int index=(i*fb->width+j)*3;
			fb->colorBuffer[index]=red;
			fb->colorBuffer[index+1]=green;
			fb->colorBuffer[index+2]=blue;
		}
	}
}
void clearScreenFast(FrameBuffer* fb,unsigned char color) {
	int size=fb->width*fb->height*3;
	memset(fb->colorBuffer,color*sizeof(unsigned char),size);
}
void clearDepth(DepthBuffer* db) {
	for(int i=0;i<db->height;i++) {
		for(int j=0;j<db->width;j++) 
			db->depthBuffer[i*db->width+j]=1.0;
	}
}
void flush(FrameBuffer* fb) {
	for(int i=0;i<fb->height;i++) {
		for(int j=0;j<fb->width;j++) {
			int index=(i*fb->width+j)*3;
			unsigned char red=fb->colorBuffer[index];
			unsigned char green=fb->colorBuffer[index+1];
			unsigned char blue=fb->colorBuffer[index+2];
			screenBits[index]=blue;
			screenBits[index+1]=green;
			screenBits[index+2]=red;
		}
	}
}
void swapBuffer() {
	if(frontBuffer==frameBuffer1) {
		frontBuffer=frameBuffer2;
		backBuffer=frameBuffer1;
	} else {
		frontBuffer=frameBuffer1;
		backBuffer=frameBuffer2;
	}

	if(!buffersReady) {
		buffersReady=true;
		return;
	}
	FrameBuffer* fb=frontBuffer;
	for(int i=0;i<fb->height;i++) {
		for(int j=0;j<fb->width;j++) {
			int index=(i*fb->width+j)*3;
			unsigned char red=fb->colorBuffer[index];
			unsigned char green=fb->colorBuffer[index+1];
			unsigned char blue=fb->colorBuffer[index+2];
			screenBits[index]=blue;
			screenBits[index+1]=green;
			screenBits[index+2]=red;
		}
	}
}

void convertToScreen(int height,int& sx,int& sy) {
	sy=height-1-sy;
}
void drawPixel(FrameBuffer* fb,int x,int y,
		unsigned char r,unsigned char g,unsigned char b) {
	convertToScreen(fb->height,x,y);
	int index=(y*fb->width+x)*3;
	fb->colorBuffer[index]=r;
	fb->colorBuffer[index+1]=g;
	fb->colorBuffer[index+2]=b;
}
void readFrameBuffer(FrameBuffer* fb,int x,int y,
		unsigned char& r,unsigned char& g,unsigned char& b) {
	convertToScreen(fb->height,x,y);
	int index=(y*fb->width+x)*3;
	r=fb->colorBuffer[index];
	g=fb->colorBuffer[index+1];
	b=fb->colorBuffer[index+2];
}
void writeDepth(DepthBuffer* db,int x,int y,float depth) {
	convertToScreen(db->height,x,y);
	db->depthBuffer[y*db->width+x]=depth;
}
float readDepth(DepthBuffer* db,int x,int y) {
	convertToScreen(db->height,x,y);
	return db->depthBuffer[y*db->width+x];
}

void scaleColor(float red,float green,float blue,
		unsigned char& iRed,unsigned char& iGreen,unsigned char& iBlue) {
	red*=255.0;
	green*=255.0;
	blue*=255.0;
	iRed=red>255?255:red;
	iGreen=green>255?255:green;
	iBlue=blue>255?255:blue;
}

void viewPortTransform(float ndcX,float ndcY,float width,float height,
		int& screenX,int& screenY) {
	float biasX=(ndcX+1.0)*0.5;
	float biasY=(ndcY+1.0)*0.5;
	screenX=roundf(biasX*(width-1.0));
	screenY=roundf(biasY*(height-1.0));
}
void viewPortTransform(float ndcX,float ndcY,float width,float height,
		float& screenX,float& screenY) {
	float biasX=(ndcX+1.0)*0.5;
	float biasY=(ndcY+1.0)*0.5;
	screenX=biasX*(width-1.0);
	screenY=biasY*(height-1.0);
}
void invViewPortTransform(int screenX,int screenY,float width,float height,
		float& ndcX,float& ndcY) {
	float scaleX=(float)screenX/(width-1.0);
	float scaleY=(float)screenY/(height-1.0);
	ndcX=scaleX*2.0-1.0;
	ndcY=scaleY*2.0-1.0;
}

void blend(unsigned char srcR,unsigned char srcG,unsigned char srcB,float srcA,
		unsigned char dstR,unsigned char dstG,unsigned char dstB,
		unsigned char& finalR,unsigned char& finalG,unsigned char& finalB) {
	float dstA=1.0-srcA;
	float finR=(float)srcR*srcA+(float)dstR*dstA;
	float finG=(float)srcG*srcA+(float)dstG*dstA;
	float finB=(float)srcB*srcA+(float)dstB*dstA;
	finalR=finR>255?255:finR;
	finalG=finG>255?255:finG;
	finalB=finB>255?255:finB;
}

void rasterize(FrameBuffer* fb,DepthBuffer* db,FragmentShader fs,Face* face) {
	float ndcX=0,ndcY=0,clipW=0;
	int scrAX,scrAY,scrBX,scrBY,scrCX,scrCY;
	viewPortTransform(face->ndcA.x,face->ndcA.y,fb->width,fb->height,scrAX,scrAY);
	viewPortTransform(face->ndcB.x,face->ndcB.y,fb->width,fb->height,scrBX,scrBY);
	viewPortTransform(face->ndcC.x,face->ndcC.y,fb->width,fb->height,scrCX,scrCY);
	int minX=max(0,min(scrAX,min(scrBX,scrCX)));
	int maxX=min(fb->width-1,max(scrAX,max(scrBX,scrCX)));
	int minY=max(0,min(scrAY,min(scrBY,scrCY)));
	int maxY=min(fb->height-1,max(scrAY,max(scrBY,scrCY)));
	for(int scrY=minY;scrY<=maxY;scrY++) {
		for(int scrX=minX;scrX<=maxX;scrX++) {
			invViewPortTransform(scrX,scrY,fb->width,fb->height,ndcX,ndcY);
			VECTOR4D ndcPixel(ndcX,ndcY,1,0);
			VECTOR4D proportion4D=face->clipMatrixInv*ndcPixel;
			VECTOR3D proportionFragment(proportion4D.x,proportion4D.y,proportion4D.z);
			float pa=proportionFragment.x;
			float pb=proportionFragment.y;
			float pc=proportionFragment.z;
			if(pa<0.0||pb<0.0||pc<0.0)
				continue;
			float sum=pa+pb+pc;
			float invSum=1.0/sum;
			pa*=invSum; pb*=invSum; pc*=invSum;

			Fragment frag;
			interpolate3f(pa,pb,pc,face->clipA.w,face->clipB.w,face->clipC.w,clipW);
			interpolate3f(pa,pb,pc,face->clipA.z,face->clipB.z,face->clipC.z,frag.ndcZ);
			float invClipW=1.0/clipW;
			frag.ndcZ*=invClipW;
			if(frag.ndcZ<-1.0||frag.ndcZ>1.0)
				continue;
			if(db!=NULL) {
				float storeZ=readDepth(db,scrX,scrY);
				if(storeZ<frag.ndcZ)
					continue;
				writeDepth(db,scrX,scrY,frag.ndcZ);
			}

			interpolate3f(pa,pb,pc,face->clipA.x,face->clipB.x,face->clipC.x,frag.ndcX);
			frag.ndcX*=invClipW;
			interpolate3f(pa,pb,pc,face->clipA.y,face->clipB.y,face->clipC.y,frag.ndcY);
			frag.ndcY*=invClipW;

			interpolate3f(pa,pb,pc,face->clipA.wx,face->clipB.wx,face->clipC.wx,frag.wx);
			interpolate3f(pa,pb,pc,face->clipA.wy,face->clipB.wy,face->clipC.wy,frag.wy);
			interpolate3f(pa,pb,pc,face->clipA.wz,face->clipB.wz,face->clipC.wz,frag.wz);
			interpolate3f(pa,pb,pc,face->clipA.ww,face->clipB.ww,face->clipC.ww,frag.ww);

			interpolate3f(pa,pb,pc,face->clipA.nx,face->clipB.nx,face->clipC.nx,frag.nx);
			interpolate3f(pa,pb,pc,face->clipA.ny,face->clipB.ny,face->clipC.ny,frag.ny);
			interpolate3f(pa,pb,pc,face->clipA.nz,face->clipB.nz,face->clipC.nz,frag.nz);

			interpolate3f(pa,pb,pc,face->clipA.s,face->clipB.s,face->clipC.s,frag.s);
			interpolate3f(pa,pb,pc,face->clipA.t,face->clipB.t,face->clipC.t,frag.t);

			FragmentOut outFrag;
			fs(frag,outFrag);
			unsigned char cr=255,cg=255,cb=255;
			scaleColor(outFrag.r,outFrag.g,outFrag.b,cr,cg,cb);
			drawPixel(fb,scrX,scrY,cr,cg,cb);
		}
	}
}

void calcBounds(float scrAX,float scrAY,float scrBX,float scrBY,float scrCX,float scrCY,
		float scrY,float& x1,float& x2) {
	if(scrAY==scrBY) {
		float paramAC=(scrY-scrAY)/(scrCY-scrAY);
		float paramBC=(scrY-scrBY)/(scrCY-scrBY);
		x1=(scrCX-scrAX)*paramAC+scrAX;
		x2=(scrCX-scrBX)*paramBC+scrBX;
	} else if(scrAY==scrCY) {
		float paramAB=(scrY-scrAY)/(scrBY-scrAY);
		float paramBC=(scrY-scrBY)/(scrCY-scrBY);
		x1=(scrBX-scrAX)*paramAB+scrAX;
		x2=(scrCX-scrBX)*paramBC+scrBX;
	} else if(scrBY==scrCY) {
		float paramAB=(scrY-scrAY)/(scrBY-scrAY);
		float paramAC=(scrY-scrAY)/(scrCY-scrAY);
		x1=(scrBX-scrAX)*paramAB+scrAX;
		x2=(scrCX-scrAX)*paramAC+scrAX;
	} else {
		float paramAB=(scrY-scrAY)/(scrBY-scrAY);
		float paramAC=(scrY-scrAY)/(scrCY-scrAY);
		float paramBC=(scrY-scrBY)/(scrCY-scrBY);
		bool ab=(paramAB<=1.0&&paramAB>=0.0)?true:false;
		bool ac=(paramAC<=1.0&&paramAC>=0.0)?true:false;
		bool bc=(paramBC<=1.0&&paramBC>=0.0)?true:false;
		float xAB=(scrBX-scrAX)*paramAB+scrAX;
		float xAC=(scrCX-scrAX)*paramAC+scrAX;
		float xBC=(scrCX-scrBX)*paramBC+scrBX;
		if(!ab) {
			x1=xAC;
			x2=xBC;
		} else if(!ac) {
			x1=xAB;
			x2=xBC;
		} else if(!bc) {
			x1=xAB;
			x2=xAC;
		} else {
			x1=xAC;
			x2=xBC;
			if(x1==x2)
				x2=xAB;
		}
	}
}
void rasterize2(FrameBuffer* fb,DepthBuffer* db,FragmentShader fs,Face* face) {
	float ndcX=0,ndcY=0,clipW=0;
	float scrAX,scrAY,scrBX,scrBY,scrCX,scrCY;
	viewPortTransform(face->ndcA.x,face->ndcA.y,fb->width,fb->height,scrAX,scrAY);
	viewPortTransform(face->ndcB.x,face->ndcB.y,fb->width,fb->height,scrBX,scrBY);
	viewPortTransform(face->ndcC.x,face->ndcC.y,fb->width,fb->height,scrCX,scrCY);
	if(scrAY==scrBY&&scrAY==scrCY)
		return;
	int minY=max(0,min(scrAY,min(scrBY,scrCY)));
	int maxY=min(fb->height-1,max(scrAY,max(scrBY,scrCY)));
	for(int scrY=minY;scrY<=maxY;scrY++) {
		float x1,x2;
		calcBounds(scrAX,scrAY,scrBX,scrBY,scrCX,scrCY,(float)scrY,x1,x2);
		int minX=max(0,roundf(min(x1,x2)));
		int maxX=min(fb->width-1,roundf(max(x1,x2)));
		for(int scrX=minX;scrX<=maxX;scrX++) {
			invViewPortTransform(scrX,scrY,fb->width,fb->height,ndcX,ndcY);
			VECTOR4D ndcPixel(ndcX,ndcY,1,0);
			VECTOR4D proportion4D=face->clipMatrixInv*ndcPixel;
			VECTOR3D proportionFragment(proportion4D.x,proportion4D.y,proportion4D.z);
			float pa=proportionFragment.x;
			float pb=proportionFragment.y;
			float pc=proportionFragment.z;
			if(pa<0.0||pb<0.0||pc<0.0)
				continue;
			float sum=pa+pb+pc;
			float invSum=1.0/sum;
			pa*=invSum; pb*=invSum; pc*=invSum;

			Fragment frag;
			interpolate3f(pa,pb,pc,face->clipA.w,face->clipB.w,face->clipC.w,clipW);
			interpolate3f(pa,pb,pc,face->clipA.z,face->clipB.z,face->clipC.z,frag.ndcZ);
			float invClipW=1.0/clipW;
			frag.ndcZ*=invClipW;
			if(frag.ndcZ<-1.0||frag.ndcZ>1.0)
				continue;
			if(db!=NULL) {
				float storeZ=readDepth(db,scrX,scrY);
				if(storeZ<frag.ndcZ)
					continue;
				writeDepth(db,scrX,scrY,frag.ndcZ);
			}

			interpolate3f(pa,pb,pc,face->clipA.x,face->clipB.x,face->clipC.x,frag.ndcX);
			frag.ndcX*=invClipW;
			interpolate3f(pa,pb,pc,face->clipA.y,face->clipB.y,face->clipC.y,frag.ndcY);
			frag.ndcY*=invClipW;

			interpolate3f(pa,pb,pc,face->clipA.wx,face->clipB.wx,face->clipC.wx,frag.wx);
			interpolate3f(pa,pb,pc,face->clipA.wy,face->clipB.wy,face->clipC.wy,frag.wy);
			interpolate3f(pa,pb,pc,face->clipA.wz,face->clipB.wz,face->clipC.wz,frag.wz);
			interpolate3f(pa,pb,pc,face->clipA.ww,face->clipB.ww,face->clipC.ww,frag.ww);

			interpolate3f(pa,pb,pc,face->clipA.nx,face->clipB.nx,face->clipC.nx,frag.nx);
			interpolate3f(pa,pb,pc,face->clipA.ny,face->clipB.ny,face->clipC.ny,frag.ny);
			interpolate3f(pa,pb,pc,face->clipA.nz,face->clipB.nz,face->clipC.nz,frag.nz);

			interpolate3f(pa,pb,pc,face->clipA.s,face->clipB.s,face->clipC.s,frag.s);
			interpolate3f(pa,pb,pc,face->clipA.t,face->clipB.t,face->clipC.t,frag.t);

			FragmentOut outFrag;
			fs(frag,outFrag);
			unsigned char cr=255,cg=255,cb=255,
					sr=255,sg=255,sb=255;
			scaleColor(outFrag.r,outFrag.g,outFrag.b,cr,cg,cb);
			if(blendFlag) {
				readFrameBuffer(fb,scrX,scrY,sr,sg,sb);
				blend(cr,cg,cb,outFrag.a,sr,sg,sb,cr,cg,cb);
			}
			drawPixel(fb,scrX,scrY,cr,cg,cb);
		}
	}
}

bool cullFace(Face* face,int flag) {
	VECTOR3D faceNormal(face->clipA.nx,face->clipA.ny,face->clipA.nz);
	VECTOR3D eyeVec(eyeX-face->clipA.wx,eyeY-face->clipA.wy,eyeZ-face->clipA.wz);
	if(flag==CULL_NONE)
		return false;
	if(flag==CULL_BACK) {
		if(eyeVec.DotProduct(faceNormal)<=0)
			return true;
		return false;
	} else if(flag==CULL_FRONT) {
		if(eyeVec.DotProduct(faceNormal)>=0)
			return true;
		return false;
	}
	return false;
}

void drawFace(FrameBuffer* fb,DepthBuffer* db,VertexShader vs,FragmentShader fs,int cullFlag,Face* face) {
	vs(face->modelA,face->clipA);
	vs(face->modelB,face->clipB);
	vs(face->modelC,face->clipC);
	if(cullFace(face,cullFlag))
		return;
	int clipFlag=checkFace(face);
	if(clipFlag!=111) {
		if(clipFlag==000)
			return;
		fixFaces(face,clipFlag);
		if(!cullFace(nFace1,cullFlag)) {
			nFace1->calculateClipMatrixInv();
			nFace1->calculateNDCVertex();
			rasterize2(fb,db,fs,nFace1);
		}
		if(clipFlag==011||clipFlag==101||clipFlag==110) {
			if(!cullFace(nFace2,cullFlag)) {
				nFace2->calculateClipMatrixInv();
				nFace2->calculateNDCVertex();
				rasterize2(fb,db,fs,nFace2);
			}
		}
	} else if(clipFlag==111) {
		face->calculateClipMatrixInv();
		face->calculateNDCVertex();
		rasterize2(fb,db,fs,face);
	}
}

void drawFaces(FrameBuffer* fb,DepthBuffer* db,VertexShader vs,FragmentShader fs,int cullFlag,Vertex* buffer,int count) {
	for(int i=0;i<count;i++) {
		Face face(buffer[i*3],buffer[i*3+1],buffer[i*3+2]);
		drawFace(fb,db,vs,fs,cullFlag,&face);
	}
}


int checkFace(Face* face) {
	bool failA=false,failB=false,failC=false;
	int nFail=0;
	if(face->clipA.vz/face->clipA.vw>-clipNear) {
		failA=true;
		nFail++;
	}
	if(face->clipB.vz/face->clipB.vw>-clipNear) {
		failB=true;
		nFail++;
	}
	if(face->clipC.vz/face->clipC.vw>-clipNear) {
		failC=true;
		nFail++;
	}

	if(nFail==3)
		return 000;
	else if(nFail==0)
		return 111;
	else if(nFail==2) {
		if(failA&&failB)
			return 001;
		else if(failA&&failC)
			return 010;
		else if(failB&&failC)
			return 100;
	} else if(nFail==1) {
		if(failA)
			return 011;
		else if(failB)
			return 101;
		else if(failC)
			return 110;
	}
	return 000;
}

void initFixFace() {
	nFace1=new Face();
	nFace2=new Face();
}
void releaseFixFace() {
	delete nFace1;
	delete nFace2;
}

void fixFaces(Face* face,int fixFlag) {
	switch(fixFlag) {
		case 011:
			fix1FailFace(face->clipA,face->clipB,face->clipC);
			break;
		case 101:
			fix1FailFace(face->clipB,face->clipA,face->clipC);
			break;
		case 110:
			fix1FailFace(face->clipC,face->clipA,face->clipB);
			break;
		case 001:
			fix2FailFace(face->clipA,face->clipB,face->clipC);
			break;
		case 010:
			fix2FailFace(face->clipA,face->clipC,face->clipB);
			break;
		case 100:
			fix2FailFace(face->clipB,face->clipC,face->clipA);
			break;
	}
}

void interpolate2v(float pa,float pb,
		VertexOut a,VertexOut b,
		VertexOut& result) {
	interpolate2f(pa,pb,a.x,b.x,result.x);
	interpolate2f(pa,pb,a.y,b.y,result.y);
	interpolate2f(pa,pb,a.z,b.z,result.z);
	interpolate2f(pa,pb,a.w,b.w,result.w);
	interpolate2f(pa,pb,a.wx,b.wx,result.wx);
	interpolate2f(pa,pb,a.wy,b.wy,result.wy);
	interpolate2f(pa,pb,a.wz,b.wz,result.wz);
	interpolate2f(pa,pb,a.ww,b.ww,result.ww);
	interpolate2f(pa,pb,a.vx,b.vx,result.vx);
	interpolate2f(pa,pb,a.vy,b.vy,result.vy);
	interpolate2f(pa,pb,a.vz,b.vz,result.vz);
	interpolate2f(pa,pb,a.vw,b.vw,result.vw);
	interpolate2f(pa,pb,a.nx,b.nx,result.nx);
	interpolate2f(pa,pb,a.ny,b.ny,result.ny);
	interpolate2f(pa,pb,a.nz,b.nz,result.nz);
	interpolate2f(pa,pb,a.s,b.s,result.s);
	interpolate2f(pa,pb,a.t,b.t,result.t);
}

void fix1FailFace(VertexOut fail,VertexOut succ1,VertexOut succ2) {
	float z=-clipNear;
	float invFailW=1.0/fail.vw;
	float invSucc1W=1.0/succ1.vw;
	float invSucc2W=1.0/succ2.vw;
	VECTOR3D pFail(fail.vx*invFailW,fail.vy*invFailW,fail.vz*invFailW);
	VECTOR3D pSucc1(succ1.vx*invSucc1W,succ1.vy*invSucc1W,succ1.vz*invSucc1W);
	VECTOR3D pSucc2(succ2.vx*invSucc2W,succ2.vy*invSucc2W,succ2.vz*invSucc2W);
	float param1=calcZPara(pFail.z,pSucc1.z,z);
	VECTOR3D interPoint1=calcParaEqu(pFail,pSucc1,param1);
	float sp=(pFail-interPoint1).GetLength();
	float fp=(pSucc1-interPoint1).GetLength();
	float sum=sp+fp;
	float invSum=1.0/sum;
	sp*=invSum; fp*=invSum;
	VertexOut inter1;
	interpolate2v(sp,fp,succ1,fail,inter1);

	float param2=calcZPara(pFail.z,pSucc2.z,z);
	VECTOR3D interPoint2=calcParaEqu(pFail,pSucc2,param2);
	sp=(pFail-interPoint2).GetLength();
	fp=(pSucc2-interPoint2).GetLength();
	sum=sp+fp;
	invSum=1.0/sum;
	sp*=invSum; fp*=invSum;
	VertexOut inter2;
	interpolate2v(sp,fp,succ2,fail,inter2);

	nFace1->copy2FaceOut(succ1,inter1,inter2);
	nFace2->copy2FaceOut(succ2,succ1,inter2);
}
void fix2FailFace(VertexOut fail1,VertexOut fail2,VertexOut succ) {
	float z=-clipNear;
	float invFail1W=1.0/fail1.vw;
	float invFail2W=1.0/fail2.vw;
	float invSuccW=1.0/succ.vw;
	VECTOR3D pFail1(fail1.vx*invFail1W,fail1.vy*invFail1W,fail1.vz*invFail1W);
	VECTOR3D pFail2(fail2.vx*invFail2W,fail2.vy*invFail2W,fail2.vz*invFail2W);
	VECTOR3D pSucc(succ.vx*invSuccW,succ.vy*invSuccW,succ.vz*invSuccW);
	float param1=calcZPara(pFail1.z,pSucc.z,z);
	VECTOR3D interPoint1=calcParaEqu(pFail1,pSucc,param1);
	float sp=(pFail1-interPoint1).GetLength();
	float fp=(pSucc-interPoint1).GetLength();
	float sum=sp+fp;
	float invSum=1.0/sum;
	sp*=invSum; fp*=invSum;
	VertexOut inter1;
	interpolate2v(sp,fp,succ,fail1,inter1);

	float param2=calcZPara(pFail2.z,pSucc.z,z);
	VECTOR3D interPoint2=calcParaEqu(pFail2,pSucc,param2);
	sp=(pFail2-interPoint2).GetLength();
	fp=(pSucc-interPoint2).GetLength();
	sum=sp+fp;
	invSum=1.0/sum;
	sp*=invSum; fp*=invSum;
	VertexOut inter2;
	interpolate2v(sp,fp,succ,fail2,inter2);

	nFace1->copy2FaceOut(succ,inter1,inter2);
}
