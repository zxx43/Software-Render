#include "face.h"

Face::Face(Vertex ma,Vertex mb,Vertex mc) {
	modelA=ma;
	modelB=mb;
	modelC=mc;

	clipMatrixInv.LoadIdentity();
}

Face::Face() {
	clipMatrixInv.LoadIdentity();
}

Face::~Face() {

}

void Face::calculateNDCVertex() {
	float invClipAW=1.0/clipA.w;
	float invClipBW=1.0/clipB.w;
	float invClipCW=1.0/clipC.w;
	ndcA.x=clipA.x*invClipAW;
	ndcA.y=clipA.y*invClipAW;
	ndcB.x=clipB.x*invClipBW;
	ndcB.y=clipB.y*invClipBW;
	ndcC.x=clipC.x*invClipCW;
	ndcC.y=clipC.y*invClipCW;
}

void Face::calculateClipMatrixInv() {
	clipMatrixInv.LoadIdentity();
	clipMatrixInv.entries[0]=clipA.x;
	clipMatrixInv.entries[1]=clipA.y;
	clipMatrixInv.entries[2]=clipA.w;
	clipMatrixInv.entries[4]=clipB.x;
	clipMatrixInv.entries[5]=clipB.y;
	clipMatrixInv.entries[6]=clipB.w;
	clipMatrixInv.entries[8]=clipC.x;
	clipMatrixInv.entries[9]=clipC.y;
	clipMatrixInv.entries[10]=clipC.w;
	clipMatrixInv.Invert();
}

void Face::copy2Face(Vertex a,Vertex b,Vertex c) {
	vertexCopy(&modelA,&a);
	vertexCopy(&modelB,&b);
	vertexCopy(&modelC,&c);
}

void Face::copy2FaceOut(VertexOut a,VertexOut b,VertexOut c) {
	vertexOutCopy(&clipA,&a);
	vertexOutCopy(&clipB,&b);
	vertexOutCopy(&clipC,&c);
}

