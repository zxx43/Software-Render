#include <stdio.h>
#ifndef _BMPLOADER_H_
#define _BMPLOADER_H_

#define BLUE 0
#define GREEN 1
#define RED 2

#define swapcolor(a,b){ \
        (a) ^= (b);     \
        (b) ^= (a);     \
        (a) ^= (b);     \
}

class BmpLoader {
private:
	unsigned char* header;//文件头
	unsigned int dataPos;//读取位置
	unsigned int imageSize;//图片内容大小

public:
	unsigned int width, height;//图片宽度 高度
	unsigned char* data;//图片内容 rgb
	BmpLoader();
	~BmpLoader();
	int getWidth();
	int getHeight();
	bool loadBitmap(const char* fileName);
};

#endif
