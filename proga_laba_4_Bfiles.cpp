#include "Header.h"

int main()
{
	string in, out;
	float number;
	cout << "Input names of input and output files and a number:" << endl;
	getline(cin, in);
	getline(cin, out);
	cin >> number;

	//in = "bmp2.bmp";
	//out = "newbmp.bmp";
	BMP_file image(in);
	image.change_image(number);
	image.output_newImage(in, out);
}


