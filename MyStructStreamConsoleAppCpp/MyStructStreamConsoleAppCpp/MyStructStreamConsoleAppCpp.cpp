// MyStructStreamConsoleAppCpp.cpp : Definiert den Einstiegspunkt für die Konsolenanwendung.
//

#include "stdafx.h"
#include <string>
#include <iostream>
#include <conio.h>
#include <time.h>
#include <iomanip>

#define FILE_NAME "MyStructData.bin"

using namespace std;

void SetConsoleColor(int c);

struct TypesI
{
	BYTE   b1;
	USHORT us;
	BYTE   b2;
	UINT   ui;
	short  s1;
	short  s2;
	int    i;
};

// PrintAllColors
void PrintAllColors()
{
	for (int i = 0; i < 255; i++)
	{
		SetConsoleColor(i);
		std::cout << "Color is: " << i << std::endl;
	}
}

// SetConsoleColor
void SetConsoleColor(int c)
{
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, c);
}

// round
inline double round(double val, int prec)
{
	val *= pow(10, prec);
	val = ceil(val);
	val /= pow(10, prec);
	return val;
}

// fRand
double fRand(double fMin, double fMax,int iPres)
{
	double f = (double) rand() / RAND_MAX;
	return round(fMin + f * (fMax - fMin),iPres);
}

int _tmain(int argc, _TCHAR* argv[])
{

	TypesI TI1;
	TypesI *TI2;

	srand(time(NULL));
	char c;
	do
	{
		system("cls");
		SetConsoleColor(7);
		string Version = "1.0.0.0";
		cout << "Program MyStructStreamConsoleAppCpp C++ Version " << Version;
		SetConsoleColor(7);
		cout << endl << endl;

		TI1.b1 = (BYTE)fRand(0, 255, 0);
		TI1.us = (USHORT)fRand(0, 65535, 0);
		TI1.b2 = (BYTE)fRand(0, 255, 0);
		TI1.ui = (UINT)fRand(0, 4294967295, 0);
		TI1.s1 = (short)fRand(-32767, 32767, 0);
		TI1.s2 = (short)fRand(-32767, 32767, 0);
		TI1.i =  (int)fRand(-2147483647, 2147483647, 0);

		SetConsoleColor(7);
		cout << "byte   b1 = " << (int)TI1.b1 << endl;
		cout << "ushort us = " << (int)TI1.us << endl;
		cout << "byte   b2 = " << (int)TI1.b2 << endl;
		cout << "uint   ui = " << (int)TI1.ui << endl;
		cout << "short  s1 = " << (int)TI1.s1 << endl;
		cout << "short  s2 = " << (int)TI1.s2 << endl;
		cout << "int    i  = " << (int)TI1.i  << endl;

		BYTE bstream1[sizeof(TI1)];
		_memccpy(bstream1, &TI1, 0, sizeof(TI1));


		// just save it in a binary file
		FILE* pFile;
		pFile = fopen("MyStructData.bin", "wb");
		fwrite(bstream1, 1, sizeof(TI1), pFile);
		fclose(pFile);


		cout << "\n\r";
		cout << "the size should be 16 size is: " << sizeof(TI1) << "\n\r";
		for (int j = 0; j < sizeof(TI1); j++)
		{
			printf("%02X", bstream1[j]);
			if (j < sizeof(TI1) - 1)
				printf("-");
		}
		cout << "\n\r\n\r";

		TI2 = (TypesI*)&bstream1;

		cout << "byte   b1 = " << (int) TI2->b1 << endl;
		cout << "ushort us = " << (int) TI2->us << endl;
		cout << "byte   b2 = " << (int) TI2->b2 << endl;
		cout << "uint   ui = " << (int) TI2->ui << endl;
		cout << "short  s1 = " << (int) TI2->s1 << endl;
		cout << "short  s2 = " << (int) TI2->s2 << endl;
		cout << "int    i  = " << (int) TI2->i  << endl;

		cout << "\n\rpress Return to continue q to quit ";

		c = _getch();
	} while (c!='q');



	// Uncomment to print all colors, if you want.
	//PrintAllColors();

	SetConsoleColor(7);
	cout << endl << endl << "End." << endl;
	return 0;
}

