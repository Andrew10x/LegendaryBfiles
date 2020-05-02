#include "Header.h"
#include <fstream>
using namespace std;

BMP_file::BMP_file(string infile)
{
	ifstream file(infile, ios::binary);
    file.read((char*)&id1, sizeof(uint8_t));
	file.read((char*)&id2, sizeof(uint8_t));
	file.read((char*)&filesize, sizeof(int32_t));
	file.read((char*)&reserved1, sizeof(int16_t));
	file.read((char*)&reserved2, sizeof(int16_t));
	file.read((char*)&headersize, sizeof(int32_t));
	file.read((char*)&infoSize, sizeof(int32_t));
	file.read((char*)&width, sizeof(int32_t));
	file.read((char*)&depth, sizeof(int32_t));
	file.read((char*)&biPlanes, sizeof(int16_t));
	file.read((char*)&bits, sizeof(int16_t));
	file.read((char*)&biCompression, sizeof(int32_t));
	file.read((char*)&biSizeImage, sizeof(int32_t));
	file.read((char*)&biXPelsPerMeter, sizeof(int32_t));
	file.read((char*)&biYPelsPerMeter, sizeof(int32_t));
	file.read((char*)&biClrUsed, sizeof(int32_t));
	file.read((char*)&biClrImportant, sizeof(int32_t));

	mas = create_mas(depth, width);
	fill_mas(file);
	//cout << width << " " << depth;
	//cout << filesize;
	for (int i = 0; i < depth; i++)
	{
		for (int j = 0; j < width; j++)
			cout << (int)mas[i][j].r << " ";
		cout << endl;
	}

	file.close();
}

void BMP_file::fill_mas(ifstream& file)
{
	char temp;
	int k = 0;
	for (int i = 0; i < depth; i++)
		for (int j = 0; j < width; j++)
		{
			file.read(&temp, sizeof(int8_t));
				mas[i][j].r = temp;
		    file.read(&temp, sizeof(int8_t));
				mas[i][j].g = temp;
			file.read(&temp, sizeof(int8_t));
				mas[i][j].b = temp;	

			if (j == width - 1) //ігнорування нульових байтів
			{
				if (width*3 % 4 != 0)
				{
					for (int i = 0; i < 4 - width % 4; i++)
						file.read(&temp, sizeof(int8_t));
				}
			}
		}
}

Pixel** BMP_file::create_mas(int d, int w)
{
	Pixel** arr = new Pixel * [d];
	for (int i = 0; i < d; i++)
		arr[i] = new Pixel[w];
	return arr;
}

