#ifndef SHADER_H_
#define SHADER_H_

#include "../header/header.h"
#include "../graphicLib/sampler.h"

//uniforms
extern MATRIX4X4 modelMatrix,viewMatrix,projectMatrix,
lightProjectionMatrix,lightViewMatrix;
extern VECTOR4D lightDir,amb,diff,ambMat,diffMat;
extern Sampler* currTexture;
extern Sampler* depthTexture;

void vertexShader(Vertex input,VertexOut& output);
void fragmentShader(Fragment input,FragmentOut& output);

void simpleFragShader(Fragment input,FragmentOut& output);

void storeVertShader(Vertex input,VertexOut& output);
void storeFragShader(Fragment input,FragmentOut& output);

#endif /* SHADER_H_ */
