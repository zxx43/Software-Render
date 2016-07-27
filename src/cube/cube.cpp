#include "cube.h"

Cube::Cube() {
	faceNum=12;
	initVerts();
}

void Cube::initVerts() {
	verts=new Vertex[faceNum*3];

	verts[0]=Vertex(
			1,-1,-1,
			0,0,-1,
			1,1);
	verts[1]=Vertex(
			-1,-1,-1,
			0,0,-1,
			0,1);
	verts[2]=Vertex(
			-1,1,-1,
			0,0,-1,
			0,0);
	verts[3]=Vertex(
			1,-1,-1,
			0,0,-1,
			1,1);
	verts[4]=Vertex(
			-1,1,-1,
			0,0,-1,
			0,0);
	verts[5]=Vertex(
			1,1,-1,
			0,0,-1,
			1,0);

	verts[6]=Vertex(
			-1,1,1,
			0,0,1,
			0,0);
	verts[7]=Vertex(
			-1,-1,1,
			0,0,1,
			0,1);
	verts[8]=Vertex(
			1,-1,1,
			0,0,1,
			1,1);
	verts[9]=Vertex(
			-1,1,1,
			0,0,1,
			0,0);
	verts[10]=Vertex(
			1,-1,1,
			0,0,1,
			1,1);
	verts[11]=Vertex(
			1,1,1,
			0,0,1,
			1,0);

	verts[12]=Vertex(
			1,1,1,
			1,0,0,
			1,0);
	verts[13]=Vertex(
			1,-1,1,
			1,0,0,
			1,1);
	verts[14]=Vertex(
			1,-1,-1,
			1,0,0,
			0,1);
	verts[15]=Vertex(
			1,1,1,
			1,0,0,
			1,0);
	verts[16]=Vertex(
			1,-1,-1,
			1,0,0,
			0,1);
	verts[17]=Vertex(
			1,1,-1,
			1,0,0,
			0,0);

	verts[18]=Vertex(
			-1,-1,1,
			-1,0,0,
			0,1);
	verts[19]=Vertex(
			-1,1,1,
			-1,0,0,
			0,0);
	verts[20]=Vertex(
			-1,1,-1,
			-1,0,0,
			1,0);
	verts[21]=Vertex(
			-1,-1,1,
			-1,0,0,
			0,1);
	verts[22]=Vertex(
			-1,1,-1,
			-1,0,0,
			1,0);
	verts[23]=Vertex(
			-1,-1,-1,
			-1,0,0,
			1,1);

	verts[24]=Vertex(
			-1,1,-1,
			0,1,0,
			0,1);
	verts[25]=Vertex(
			-1,1,1,
			0,1,0,
			0,0);
	verts[26]=Vertex(
			1,1,1,
			0,1,0,
			1,0);
	verts[27]=Vertex(
			-1,1,-1,
			0,1,0,
			0,1);
	verts[28]=Vertex(
			1,1,1,
			0,1,0,
			1,0);
	verts[29]=Vertex(
			1,1,-1,
			0,1,0,
			1,1);

	verts[30]=Vertex(
			1,-1,1,
			0,-1,0,
			1,0);
	verts[31]=Vertex(
			-1,-1,1,
			0,-1,0,
			0,0);
	verts[32]=Vertex(
			-1,-1,-1,
			0,-1,0,
			0,1);
	verts[33]=Vertex(
			1,-1,1,
			0,-1,0,
			1,0);
	verts[34]=Vertex(
			-1,-1,-1,
			0,-1,0,
			0,1);
	verts[35]=Vertex(
			1,-1,-1,
			0,-1,0,
			1,1);
}

Cube::~Cube() {
	delete[] verts;
}

void Cube::render(FrameBuffer* fb,DepthBuffer* db,VertexShader vs,FragmentShader fs,int cullFlag) {
	drawFaces(fb,db,vs,fs,cullFlag,verts,faceNum);
}
