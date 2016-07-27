#include "texture.h"
#include "../header/header.h"

Texture::Texture(const char* src) {
	BmpLoader* loader=new BmpLoader();
	if(!loader->loadBitmap(src)) {
		sampler=NULL;
		return;
	}
	sampler=new Sampler(loader->width,loader->height);
	memcpy(sampler->imgData,loader->data,loader->width*loader->height*3*sizeof(unsigned char));
	delete loader;
}

Texture::~Texture() {
	if(sampler!=NULL)
		delete sampler;
}
