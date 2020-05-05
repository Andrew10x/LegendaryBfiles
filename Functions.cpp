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

	new_mas = NULL;
	final_mas = NULL;
	new_width = 0;
	new_depth = 0;
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
				if (width * 3 % 4 != 0)
				{
					for (int i = 0; i < 4 - width * 3 % 4; i++)
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

void BMP_file::change_image(float n)
{
	change_width(n);
	change_depth(n);
}

void BMP_file::change_width(float n)
{
	new_width = (int32_t)(width * n);
	new_mas = create_mas(depth, new_width);

	if (n > 1)
	{
		int* temp = new int[width];
		for (int i = 0; i < width; i++)
			temp[i] = (int)(i * n);

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
						k++;
					}
					else
						new_mas[i][j] = interpolation(j - 1, j, temp[k], new_mas[i][j - 1], mas[i][k]);
				}
				else
					new_mas[i][j] = new_mas[i][j - 1];
			}
		}
	}
	else
	{
		for (int i = 0; i < depth; i++)
			for (int j = 0; j < new_width; j++)
			{
				int t = (int)(j / n);
				new_mas[i][j] = mas[i][t];
			}
	}
}

Pixel BMP_file::interpolation(int x0, int x, int x1, Pixel y0, Pixel y1)
{
	Pixel y;
	y.r = y0.r + (y1.r - y0.r) * (x - x0) / (x1 - x0);
	y.g = y0.g + (y1.g - y0.g) * (x - x0) / (x1 - x0);
	y.b = y0.b + (y1.b - y0.b) * (x - x0) / (x1 - x0);
	return y;
}

void BMP_file::change_depth(float n)
{

	new_depth = (int32_t)(depth * n);
	final_mas = create_mas(new_depth, new_width);

	if (n > 1)
	{
		int* temp = new int[new_depth];
		for (int i = 0; i < new_depth; i++)
			temp[i] = (int)(i * n);


		for (int i = 0; i < new_width; i++)
		{
			int k = 0;
			for (int j = 0; j < new_depth; j++)
			{
				if (k < depth)
				{
					if (j == temp[k])
					{
						final_mas[j][i] = new_mas[k][i];
						k++; 
					}
					else
						final_mas[j][i] = interpolation(j - 1, j, temp[k], final_mas[j - 1][i], new_mas[k][i]);
				}
				else
					final_mas[j][i] = final_mas[j - 1][i];
			}
		}
	}
	else
	{
		for (int i = 0; i < new_width; i++)
			for (int j = 0; j < new_depth; j++)
			{
				int t = (int)(j / n);
				final_mas[j][i] = new_mas[t][i];
			}
	}
}

void BMP_file::output_newImage()
{
	ofstream outfile("newbmb.bmp", ios::binary);
	ifstream infile("bmp2.bmp", ios::binary);
	uint8_t temp;
	for (int i = 0; i < headersize; i++) //копіюємо header
	{
		infile.read((char*)&temp, sizeof(uint8_t)); 
		outfile.write((char*)&temp, sizeof(uint8_t)); 
	}
	infile.close();

	int8_t t;  //заповнюємо пікселями
	int8_t zero = 0;

	for (int i = 0; i < new_depth; i++)
	{
		for (int j = 0; j < new_width; j++)
		{
			outfile.write((char*)&final_mas[i][j].r, sizeof(int8_t));
			outfile.write((char*)&final_mas[i][j].g, sizeof(int8_t));
			outfile.write((char*)&final_mas[i][j].b, sizeof(int8_t));

			if (j == new_width - 1)    //додаємо нульові байти
			{
				if ((new_width * 3) % 4 != 0)
				{
					for (int q = 0; q < 4 - (new_width * 3) % 4; q++)
					{
						outfile.write((char*)&zero, sizeof(int8_t));
					}
				}
			}
		}
	}
	int32_t new_width_inbytes = new_width * 3 + 4 - (new_width*3) % 4; //нові характеристики
	int32_t new_depth_inbytes = new_depth;
	int32_t newfilesize = new_width_inbytes * new_depth_inbytes + headersize;
	outfile.seekp(2, ios::beg); //записуємо їх у файл
	outfile.write((char*)&newfilesize, sizeof(int32_t));
	outfile.seekp(18, ios::beg);
	outfile.write((char*)&new_width, sizeof(int32_t));
	outfile.seekp(22, ios::beg);
	outfile.write((char*)&new_depth, sizeof(int32_t));
	outfile.close();
}