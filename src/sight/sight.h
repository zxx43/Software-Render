#ifndef SIGHT_H_
#define SIGHT_H_

#include "../header/header.h"

class Sight {
public:
	float sx,sy,sz,sh;
	float xrot,yrot,zrot;

	Sight(float x,float y,float z);
	~Sight();
	void turnY(int ud);
	void turnX(int lr);
	void moveSight(int dist,float speed);
};

float atr(float angle);
float rta(float rot);

#endif /* SIGHT_H_ */
