#ifndef SPHERE_H_
#define SPHERE_H_

#include "../graphicLib/graphicLib.h"

class Sphere {
private:
	int faceNum;
public:
	Vertex* verts;

	Sphere(int m,int n);
	~Sphere();
	void render(FrameBuffer* fb,DepthBuffer* db,VertexShader vs,FragmentShader fs,int cullFlag);
};

#endif /* SPHERE_H_ */
