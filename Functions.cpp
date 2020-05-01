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
			switch (k % 3)
			{
			case 0: mas[i][j].r = temp;
				break;
			case 1: mas[i][j].g = temp;
				break;
			case 2: mas[i][j].r = temp;
				break;
			}

			k++;

			if (j == width - 1)
			{
				if (width % 4 != 0)
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
		mas[i] = new Pixel[w];
	return arr;
}