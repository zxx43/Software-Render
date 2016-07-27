#include "sight.h"
#include <math.h>

Sight::Sight(float x,float y,float z) {
	sx=x;
	sy=y;
	sz=z;
	sh=2;
	xrot=0;
	yrot=0;
	zrot=0;
}

Sight::~Sight() {

}

void Sight::turnX(int lr) {
	switch(lr) {
		case LEFT:
			xrot-=D_ROTATION;
			break;
		case RIGHT:
			xrot+=D_ROTATION;
			break;
	}
	if(xrot>360.0)
		xrot-=360.0;
	else if(xrot<0)
		xrot+=360.0;
}

void Sight::turnY(int ud) {
	switch(ud) {
		case UP:
			yrot-=D_ROTATION;
			break;
		case DOWN:
			yrot+=D_ROTATION;
			break;
	}
	if(yrot>360.0)
		yrot-=360.0;
	else if(yrot<0)
		yrot+=360.0;
}

void Sight::moveSight(int dist,float speed) {
	float xz=atr(xrot);
	float yz=atr(yrot);
	float dx=speed*cos(yz)*sin(xz);
	float dy=speed*sin(yz);
	float dz=speed*cos(yz)*cos(xz);

	switch(dist) {
		case DOWN:
			sy+=speed;
			sh-=speed;
			break;
		case UP:
			sy-=speed;
			sh+=speed;
			break;
		case RIGHT:
			sx-=speed*cos(xz);
			sz-=speed*sin(xz);
			break;
		case LEFT:
			sx+=speed*cos(xz);
			sz+=speed*sin(xz);
			break;
		case MFAR:
			sx+=dx;
			sy-=dy;
			sz-=dz;
			break;
		case MNEAR:
			sx-=dx;
			sy+=dy;
			sz+=dz;
			break;
	}
}

float atr(float angle) {
	return angle*A2R;
}
float rta(float rot) {
	return rot*R2A;
}

