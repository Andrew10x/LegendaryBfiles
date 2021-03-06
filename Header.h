#pragma once
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

class Pixel
{
	uint8_t b;
	uint8_t g;
	uint8_t r;
	friend class BMP_file;
};

class BMP_file
{
	int8_t id1;              // ������ �� ����� 'B' � 'M'
	int8_t id2;           
    int32_t filesize;        // ����� ����� � ������
	int16_t reserved1;       // 0, 0
	int16_t reserved2;    
	int32_t headersize;      // 54L ��� 24-����� ���������
	int32_t infoSize;        // 40L ��� 24-����� ���������
	int32_t width;           // ������ ���������� � �������
	int32_t depth;           // ������ ���������� � �������
	int16_t biPlanes;        // 1 (��� 24-����� ���������)
	int16_t bits;            // 24 (��� 24-����� ���������)
	int32_t biCompression;   // 0L
	int32_t biSizeImage;     // ����� ��������� � 0L ��� ��������� ��� �������� (��� ������)
	int32_t biXPelsPerMeter; // ������������� ������� ������ �� ����, ����� 0L
	int32_t biYPelsPerMeter; // �� ����, �� �����
	int32_t biClrUsed;       // ��� ������������ ���������, ����� ��������� 0L
	int32_t biClrImportant;  // �� ����
	Pixel** mas;

	Pixel** new_mas;
	Pixel** final_mas;
	int32_t new_width;
	int32_t new_depth;
public:
	BMP_file(string);
	void fill_mas(ifstream&); //��������� ������� � �����
	Pixel** create_mas(int, int); //��������� �������
	void change_image(float); //���� ������ ����������
	void change_width(float); //���� �������
	void change_depth(float); //���� ������
	Pixel interpolation(int, int, int, Pixel, Pixel); //������������
	void output_newImage(string, string);
	~BMP_file();
};