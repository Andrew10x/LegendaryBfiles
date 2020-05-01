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
	int8_t id1;              // Завжди дві літери 'B' і 'M'
	int8_t id2;           
    int32_t filesize;        // Розмір файла в байтах
	int16_t reserved1;       // 0, 0
	int16_t reserved2;    
	int32_t headersize;      // 54L для 24-бітних зображень
	int32_t infoSize;        // 40L для 24-бітних зображень
	int32_t width;           // ширина зображення в пікселях
	int32_t depth;           // висота зображення в пікселях
	int16_t biPlanes;        // 1 (для 24-бітних зображень)
	int16_t bits;            // 24 (для 24-бітних зображень)
	int32_t biCompression;   // 0L
	int32_t biSizeImage;     // Можна поставити в 0L для зображень без компрессії (наш варіант)
	int32_t biXPelsPerMeter; // Рекомендована кількість пікселів на метр, можна 0L
	int32_t biYPelsPerMeter; // Те саме, по висоті
	int32_t biClrUsed;       // Для індексованих зображень, можна поставити 0L
	int32_t biClrImportant;  // Те саме
	Pixel** mas;
	//Pixel** new_mas;
public:
	BMP_file(string);
	void fill_mas(ifstream&); //заповненя матриці з файлу
	Pixel** create_mas(int, int); //створення матриці
};