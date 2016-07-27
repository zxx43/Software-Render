#ifndef CONSTANTS_H_
#define CONSTANTS_H_

#define SCREEN_WIDTH 640 //长度范围 0到639
#define SCREEN_HEIGHT 480 //宽度范围 0到479
#define MAX_X SCREEN_WIDTH-1 //屏幕最宽639
#define MAX_Y SCREEN_HEIGHT-1 //屏幕最高479
#define MIN_X 0
#define MIN_Y 0
#define CULL_BACK 0
#define CULL_FRONT 1
#define CULL_NONE 2
#define INV_SCALE 0.003921568627451

#define NONE 0
#define LEFT 1
#define RIGHT 2
#define UP 3
#define DOWN 4
#define MNEAR 5
#define MFAR 6
#define D_ROTATION 4.0
#define D_DISTANCE 1.0

#endif /* CONSTANTS_H_ */
