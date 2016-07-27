#ifndef FACE_H_
#define FACE_H_

#include "../header/constants.h"
#include "../header/datatype.h"
#include "../Maths/Maths.h"

class Face {
public:
	Vertex modelA,modelB,modelC;
	VertexOut clipA,clipB,clipC;
	VECTOR2D ndcA,ndcB,ndcC;
	MATRIX4X4 clipMatrixInv;

	Face(Vertex ma,Vertex mb,Vertex mc);
	Face();
	~Face();
	void copy2Face(Vertex a,Vertex b,Vertex c);
	void copy2FaceOut(VertexOut a,VertexOut b,VertexOut c);
	void calculateNDCVertex();
	void calculateClipMatrixInv();
};

#endif /* FACE_H_ */
