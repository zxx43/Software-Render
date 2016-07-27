#ifndef OBJECTS_H_
#define OBJECTS_H_

#include "texture/texture.h"
#include "shader/shader.h"
#include "shadow/shadow.h"
#include "cube/cube.h"
#include "square/square.h"
#include "sphere/sphere.h"

extern Texture* texWood;
extern Texture* texGround;
extern Cube* cube;
extern Square* square;
extern Sphere* sphere;

void initUniforms();

void initCube();
void releaseCube();
void renderCube();
void renderCubeShadow();

void initSquare();
void releaseSquare();
void renderSquare();

void initSphere();
void releaseSphere();
void renderSphere();
void renderSphereShadow();

void renderShadow();

#endif /* OBJECTS_H_ */
