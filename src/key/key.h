#ifndef KEY_H_
#define KEY_H_

#include "../header/header.h"

#ifndef VK_ESCAPE
#define VK_ESCAPE 0x1B
#define VK_SPACE    32
#define VK_LEFT	    37
#define VK_UP	    38
#define VK_RIGHT    39
#define VK_DOWN	    40
#endif

extern bool* turn;
extern bool* move;
extern bool willExit;

void initKeys();
void releaseKeys();
void keyDown(int key);
void keyUp(int key);

#endif /* KEY_H_ */
