#ifndef DATATYPE_H_
#define DATATYPE_H_

struct FrameBuffer {
	unsigned char* colorBuffer;
	int width,height;
};
struct DepthBuffer {
	float* depthBuffer;
	int width,height;
};

struct Vertex {
	float x,y,z,w;
	float nx,ny,nz;
	float s,t;
	Vertex(): x(0),y(0),z(0),w(1),
			nx(0),ny(0),nz(0),
			s(0),t(0) {}
	Vertex(float vx,float vy,float vz,
			float vnx,float vny,float vnz,
			float vs,float vt):
				x(vx),y(vy),z(vz),w(1),
				nx(vnx),ny(vny),nz(vnz),
				s(vs),t(vt) {}
};

inline void vertexCopy(Vertex* d,Vertex* s) {
	d->x=s->x;
	d->y=s->y;
	d->z=s->z;
	d->w=s->w;
	d->nx=s->nx;
	d->ny=s->ny;
	d->nz=s->nz;
	d->s=s->s;
	d->t=s->t;
}

struct VertexOut {
	float x,y,z,w;
	float wx,wy,wz,ww;
	float vx,vy,vz,vw;
	float nx,ny,nz;
	float s,t;
	VertexOut(): x(0),y(0),z(0),w(1),
			wx(0),wy(0),wz(0),ww(1),
			vx(0),vy(0),vz(0),vw(1),
			nx(0),ny(0),nz(0),
			s(0),t(0) {}
	VertexOut(float vx,float vy,float vz,
			float vwx,float vwy,float vwz,
			float vvx,float vvy,float vvz,
			float vnx,float vny,float vnz,
			float vs,float vt):
				x(vx),y(vy),z(vz),w(1),
				wx(vwx),wy(vwy),wz(vwz),ww(1),
				vx(vvx),vy(vvy),vz(vvz),vw(1),
				nx(vnx),ny(vny),nz(vnz),
				s(vs),t(vt) {}
};

inline void vertexOutCopy(VertexOut* d,VertexOut* s) {
	d->x=s->x;
	d->y=s->y;
	d->z=s->z;
	d->w=s->w;
	d->wx=s->wx;
	d->wy=s->wy;
	d->wz=s->wz;
	d->ww=s->ww;
	d->vx=s->vx;
	d->vy=s->vy;
	d->vz=s->vz;
	d->vw=s->vw;
	d->nx=s->nx;
	d->ny=s->ny;
	d->nz=s->nz;
	d->s=s->s;
	d->t=s->t;
}

struct Fragment {
	float ndcX,ndcY,ndcZ;
	float wx,wy,wz,ww;
	float nx,ny,nz;
	float s,t;
	Fragment(): ndcX(0),ndcY(0),ndcZ(1),
			wx(0),wy(0),wz(0),ww(1),
			nx(0),ny(0),nz(0),
			s(0),t(0) {}
};

struct FragmentOut {
	float r,g,b,a;
	FragmentOut():r(0),g(0),b(0),a(1) {}
};

typedef void (*VertexShader)(Vertex input,VertexOut& output);
typedef void (*FragmentShader)(Fragment input,FragmentOut& output);
typedef void (*DrawCall)();

#endif /* DATATYPE_H_ */
