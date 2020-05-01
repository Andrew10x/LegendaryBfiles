#pragma once
#include <fstream>
#include <iostream>
using namespace std;

class Pixel
{
	int8_t r;
	int8_t g;
	int8_t b;
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
	//Pixel** new_mas;
public:
	BMP_file(string);
	void fill_mas(ifstream&); //��������� ������� � �����
	Pixel** create_mas(int, int); //��������� �������
};