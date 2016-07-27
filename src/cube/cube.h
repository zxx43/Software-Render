#ifndef CUBE_H_
#define CUBE_H_

#include "../graphicLib/graphicLib.h"

class Cube {
private:
	int faceNum;
	void initVerts();
public:
	Vertex* verts;

	Cube();
	~Cube();
	void render(FrameBuffer* fb,DepthBuffer* db,VertexShader vs,FragmentShader fs,int cullFlag);
};

#endif /* CUBE_H_ */
