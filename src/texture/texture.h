#ifndef TEXTURE_H_
#define TEXTURE_H_

#include "BmpLoader.h"
#include "../graphicLib/sampler.h"

class Texture {
public:
	Sampler* sampler;

	Texture(const char* src);
	~Texture();
};

#endif /* TEXTURE_H_ */
