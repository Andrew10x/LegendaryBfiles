#include "Header.h"

int main()
{
	BMP_file image("bmp2.bmp");
	image.change_image(2);
	image.output_newImage();
}


