#include "square.h"

Square::Square() {
	faceNum=2;
	initVerts();
}

void Square::initVerts() {
	verts=new Vertex[faceNum*3];

	verts[0]=Vertex(
			-1,0,-1,
			0,1,0,
			0,1);
	verts[1]=Vertex(
			-1,0,1,
			0,1,0,
			0,0);
	verts[2]=Vertex(
			1,0,1,
			0,1,0,
			1,0);
	verts[3]=Vertex(
			1,0,1,
			0,1,0,
			1,0);
	verts[4]=Vertex(
			1,0,-1,
			0,1,0,
			1,1);
	verts[5]=Vertex(
			-1,0,-1,
			0,1,0,
			0,1);
}

Square::~Square() {
	delete[] verts;
}

void Square::render(FrameBuffer* fb,DepthBuffer* db,VertexShader vs,FragmentShader fs,int cullFlag) {
	drawFaces(fb,db,vs,fs,cullFlag,verts,faceNum);
}

