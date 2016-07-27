#ifndef GRAPHICLIB_H_
#define GRAPHICLIB_H_

#include "../header/header.h"
#include "../face/face.h"

extern float eyeX,eyeY,eyeZ,clipNear;
extern Face* nFace1;
extern Face* nFace2;
extern bool blendFlag;

extern FrameBuffer* frontBuffer;
extern FrameBuffer* backBuffer;

extern FrameBuffer* frameBuffer1;
extern FrameBuffer* frameBuffer2;
extern DepthBuffer* depthBuffer;

extern unsigned char* screenBits;

void initFrameBuffer(FrameBuffer** pfb,int width,int height);
void releaseFrameBuffer(FrameBuffer** pfb);
void initDepthBuffer(DepthBuffer** pdb,int width,int height);
void releaseDepthBuffer(DepthBuffer** pdb);
void initDevice(FrameBuffer** pfb,DepthBuffer** pdb,int width,int height);
void releaseDevice(FrameBuffer** pfb,DepthBuffer** pdb);
void initDevice2Buf(FrameBuffer** pfb1,FrameBuffer** pfb2,DepthBuffer** pdb,int width,int height);
void releaseDevice2Buf(FrameBuffer** pfb1,FrameBuffer** pfb2,DepthBuffer** pdb);
void clearScreen(FrameBuffer* fb,unsigned char red,unsigned char green,unsigned char blue);
void clearScreenFast(FrameBuffer* fb,unsigned char color);
void clearDepth(DepthBuffer* db);
void flush(FrameBuffer* fb);
void swapBuffer();

bool cullFace(Face* face,int flag);
void viewPortTransform(float ndcX,float ndcY,float width,float height,
		int& screenX,int& screenY);
void viewPortTransform(float ndcX,float ndcY,float width,float height,
		float& screenX,float& screenY);
void rasterize(FrameBuffer* fb,DepthBuffer* db,
		FragmentShader fs,Face* face);
void rasterize2(FrameBuffer* fb,DepthBuffer* db,
		FragmentShader fs,Face* face);
void blend(unsigned char srcR,unsigned char srcG,unsigned char srcB,float srcA,
	unsigned char dstR,unsigned char dstG,unsigned char dstB,
	unsigned char& finalR,unsigned char& finalG,unsigned char& finalB);
void drawFace(FrameBuffer* fb,DepthBuffer* db,
		VertexShader vs,FragmentShader fs,int cullFlag,
		Face* face);
void drawFaces(FrameBuffer* fb,DepthBuffer* db,
		VertexShader vs,FragmentShader fs,int cullFlag,
		Vertex* buffer,int count);
void drawPixel(FrameBuffer* fb,int x,int y,
	unsigned char r,unsigned char g,unsigned char b);
void readFrameBuffer(FrameBuffer* fb,int x,int y,
	unsigned char& r,unsigned char& g,unsigned char& b);
void writeDepth(DepthBuffer* db,int x,int y,float depth);
float readDepth(DepthBuffer* db,int x,int y);

void invViewPortTransform(int screenX,int screenY,float width,float height,
		float& ndcX,float& ndcY);

void initFixFace();
void releaseFixFace();
int checkFace(Face* face);
void fixFaces(Face* face,int fixFlag);
void fix1FailFace(VertexOut fail,VertexOut succ1,VertexOut succ2);
void fix2FailFace(VertexOut fail1,VertexOut fail2,VertexOut succ);
void interpolate2v(float pa,float pb,
		VertexOut a,VertexOut b,
		VertexOut& result);

#endif /* GRAPHICLIB_H_ */
