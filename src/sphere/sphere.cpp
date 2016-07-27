#include "sphere.h"

Sphere::Sphere(int m,int n) {
	faceNum=(m-1)*n*2;
	verts=new Vertex[faceNum*3];

	float stepAngZ=PI/m;
	float stepAngXY=2.0*PI/n;
	float angZ=0.0;
	float angXY=0.0;

	int index=0;
	for(int i=0;i<m;i++) {
		for(int j=0;j<n;j++) {
			float x1=sin(angZ)*cos(angXY);
			float y1=sin(angZ)*sin(angXY);
			float z1=cos(angZ);
			float v1=angZ/PI;
			float u1=angXY/PI2;

			float x2=sin(angZ+stepAngZ)*cos(angXY);
			float y2=sin(angZ+stepAngZ)*sin(angXY);
			float z2=cos(angZ+stepAngZ);
			float v2=(angZ+stepAngZ)/PI;
			float u2=angXY/PI2;

			float x3=sin(angZ+stepAngZ)*cos(angXY+stepAngXY);
			float y3=sin(angZ+stepAngZ)*sin(angXY+stepAngXY);
			float z3=cos(angZ+stepAngZ);
			float v3=(angZ+stepAngZ)/PI;
			float u3=(angXY+stepAngXY)/PI2;

			if(i!=m-1) {
				verts[index]=Vertex(x1,y1,z1,
					x1,y1,z1,
					u1,v1);
				index++;

				verts[index]=Vertex(x2,y2,z2,
					x2,y2,z2,
					u2,v2);
				index++;

				verts[index]=Vertex(x3,y3,z3,
					x3,y3,z3,
					u3,v3);
				index++;
			}

			float x4=sin(angZ)*cos(angXY+stepAngXY);
			float y4=sin(angZ)*sin(angXY+stepAngXY);
			float z4=cos(angZ);
			float v4=angZ/PI;
			float u4=(angXY+stepAngXY)/PI2;

			if(i!=0) {
				verts[index]=Vertex(x1,y1,z1,
					x1,y1,z1,
					u1,v1);
				index++;

				verts[index]=Vertex(x3,y3,z3,
					x3,y3,z3,
					u3,v3);
				index++;

				verts[index]=Vertex(x4,y4,z4,
					x4,y4,z4,
					u4,v4);
				index++;
			}

			angXY+=stepAngXY;
		}
		angXY=0.0;
		angZ+=stepAngZ;
	}
}

Sphere::~Sphere() {
	delete[] verts;
}

void Sphere::render(FrameBuffer* fb,DepthBuffer* db,VertexShader vs,FragmentShader fs,int cullFlag) {
	drawFaces(fb,db,vs,fs,cullFlag,verts,faceNum);
}