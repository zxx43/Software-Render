#ifndef SQUARE_H_
#define SQUARE_H_

#include "../graphicLib/graphicLib.h"

class Square {
private:
	int faceNum;
	void initVerts();
public:
	Vertex* verts;

	Square();
	~Square();
	void render(FrameBuffer* fb,DepthBuffer* db,VertexShader vs,FragmentShader fs,int cullFlag);
};

#endif /* SQUARE_H_ */
