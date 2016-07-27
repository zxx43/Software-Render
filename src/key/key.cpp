#include "key.h"

bool* turn=NULL;
bool* move=NULL;
bool willExit=false;

void initKeys() {
	turn=new bool[4];
	memset(turn,0,4*sizeof(bool));
	move=new bool[6];
	memset(move,0,6*sizeof(bool));
}
void releaseKeys() {
	delete[] turn; turn=NULL;
	delete[] move; move=NULL;
}

void keyDown(int key) {
	switch(key) {
		case 'W':
			move[0]=true;
			break;
		case 'S':
			move[1]=true;
			break;
		case 'A':
			move[2]=true;
			break;
		case 'D':
			move[3]=true;
			break;
		case VK_SPACE:
			move[4]=true;
			break;
		case 'Z':
			move[5]=true;
			break;
		case VK_UP:
			turn[0]=true;
			break;
		case VK_DOWN:
			turn[1]=true;
			break;
		case VK_LEFT:
			turn[2]=true;
			break;
		case VK_RIGHT:
			turn[3]=true;
			break;
	}
}

void keyUp(int key) {
	switch(key) {
		case 'W':
			move[0]=false;
			break;
		case 'S':
			move[1]=false;
			break;
		case 'A':
			move[2]=false;
			break;
		case 'D':
			move[3]=false;
			break;
		case VK_SPACE:
			move[4]=false;
			break;
		case 'Z':
			move[5]=false;
			break;
		case VK_UP:
			turn[0]=false;
			break;
		case VK_DOWN:
			turn[1]=false;
			break;
		case VK_LEFT:
			turn[2]=false;
			break;
		case VK_RIGHT:
			turn[3]=false;
			break;
		case VK_ESCAPE:
			willExit=true;
			break;
	}
}

