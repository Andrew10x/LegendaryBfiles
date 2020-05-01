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
	file.close();

	mas = new Pixel * [width];
	for (int i = 0; i < width; i++)
		mas[i] = new Pixel [depth];
}