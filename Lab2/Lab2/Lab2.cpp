#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>

using namespace std;

double A = 1.0;
double f = 5;
double fi = 3 * M_PI;

double simple_tone(double x)
{
	return A * sin((2 * M_PI * f * x) + fi);
}

int main()
{
	double fs = pow(2, -8);
	vector<double> tone;
	for (double i = 0; i <= 3; i += fs)
	{
		tone.push_back(simple_tone(i));
	}
	fstream file;
	file.open("simple_tone_not_quantified.txt", ios::out);
	for (int i = 0; i < tone.size(); i++)
	{
		file << tone[i];
		file << " ";
	}
	file.close();
	file.open("q_16.txt", ios::out);
	double step = (double)2 / pow(2,16);
	for (int i = 0; i < tone.size(); i++)
	{
		for (double j = -1; j <= 1; j += step)
		{
			if (tone[i] > j && tone[i] <= j+step)
			{
				file << j;
				file << " ";
				break;
			}
			else
			{
				continue;
			}
		}
	}
	file.close();
	file.open("q_8.txt", ios::out);
	step = (double)2 / pow(2,8);
	for (int i = 0; i < tone.size(); i++)
	{
		for (double j = -1; j <= 1; j += step)
		{
			if (tone[i] > j && tone[i] <= j + step)
			{
				file << j;
				file << " ";
				break;
			}
			else
			{
				continue;
			}
		}
	}
	file.close();
	file.open("q_6.txt", ios::out);
	step = (double)2 / pow(2, 6);
	for (int i = 0; i < tone.size(); i++)
	{
		for (double j = -1; j <= 1; j += step)
		{
			if (tone[i] > j && tone[i] <= j + step)
			{
				file << j;
				file << " ";
				break;
			}
			else
			{
				continue;
			}
		}
	}
	file.close();
	file.open("q_4.txt", ios::out);
	step = (double)2 / pow(2,4);
	for (int i = 0; i < tone.size(); i++)
	{
		for (double j = -1; j <= 1; j += step)
		{
			if (tone[i] > j && tone[i] <= j + step)
			{
				file << j;
				file << " ";
				break;
			}
			else
			{
				continue;
			}
		}
	}
	file.close();
}