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
	/*for (int i = 0; i < depth; i++)
	{
		for (int j = 0; j < width; j++)
			cout << (int)mas[i][j].r << " ";
		cout << endl;
	}*/

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
			mas[i][j].r = temp; //cout <<(int) temp << " ";
		    file.read(&temp, sizeof(int8_t));
				mas[i][j].g = temp; //cout <<(int) temp << " ";
			file.read(&temp, sizeof(int8_t));
				mas[i][j].b = temp;//	cout <<(int) temp << " ";
				//cout << endl;
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

void BMP_file::increase_width(float n)
{
	
    int32_t new_width = width * n;
	Pixel** new_mas = create_mas(depth, new_width);

	int* temp = new int[width];
	for (int i = 0; i < width; i++)
		 temp[i] = i * n;

	/*for (int i = 0; i < width; i++)
		cout << temp[i] << " ";*/


	for (int i = 0; i < depth; i++)
	{ 
		int k = 0;
		for (int j = 0; j < new_width; j++)
		{
			if (k < width)
			{
				if (j == temp[k])
				{
					new_mas[i][j] = mas[i][k];
					k++; //cout << k << " ";
				}
				else
					new_mas[i][j] = interpolation(j - 1, j, temp[k], new_mas[i][j - 1], mas[i][k]);
			}
			else
				new_mas[i][j] = new_mas[i][j - 1];
		} //cout << endl;
	}

	//cout << new_mas[depth - 1][new_width - 1].r;
	//cout << mas[9][10].g;
	//cout << width;
	/*for(int i=0; i<depth; i++)
		for (int j = 0; j < new_width; j++)
		{
			cout << (int) new_mas[i][j].r << " ";
			cout << (int) new_mas[i][j].g << " ";
			cout << (int) new_mas[i][j].b << " ";
			cout << endl;
		}*/
}

Pixel BMP_file::interpolation(int x0, int x, int x1, Pixel y0, Pixel y1)
{
	Pixel y;
	y.r = y0.r + (y1.r - y0.r) * (x - x0) / (x1 - x0);
	y.g = y0.g + (y1.g - y0.g) * (x - x0) / (x1 - x0);
	y.b = y0.b + (y1.b - y0.b) * (x - x0) / (x1 - x0);
	return y;
}