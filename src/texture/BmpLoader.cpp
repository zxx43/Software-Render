#include "BmpLoader.h"

BmpLoader::BmpLoader() {
	header=new unsigned char[54];
}

BmpLoader::~BmpLoader() {
	delete[] header;
	delete[] data;
	printf("release image\n");
}

bool BmpLoader::loadBitmap(const char* fileName) {
	FILE * file = fopen(fileName,"rb");
	if (!file) {
		printf("Image %s could not be opened\n",fileName);
		return false;
	}
	if (fread(header, 1, 54, file)!=54) {//文件头并非54字节 读取失败
	    printf("Not a correct BMP file\n");
	    return false;
	}
	if (header[0]!='B' || header[1]!='M') {//文件头开头并非BM 读取失败
	    printf("Not a correct BMP file\n");
	    return false;
	}

	dataPos    = *(int*)&(header[0x0A]);//读取位置 位置在文件头0x0A处
	imageSize  = *(int*)&(header[0x22]);//图片内容大小数据 位置在文件头0x22处
	width      = *(int*)&(header[0x12]);//图片宽度数据 位置在文件头0x12处
	height     = *(int*)&(header[0x16]);//图片高度数据 位置在文件头0x16处

	if (imageSize==0)
		imageSize=width*height*3;//图片内容数据=总像素数x3
	if (dataPos==0)
		dataPos=54;//文件头读完 位置在54字节处

	data = new unsigned char[imageSize];//data放像素信息
	fread(data,1,imageSize,file);//读取像素
	fclose(file);

	for(int i= 0;i<(int)imageSize;i+=3)
		swapcolor(data[i],data[i+2]);//bgr变为rgb
	
	return true;
}

int BmpLoader::getWidth() {
	return width;
}

int BmpLoader::getHeight() {
	return height;
}


