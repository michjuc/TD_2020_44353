#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#define _USE_MATH_DEFINES
#include <math.h>

class Signal {
public:
	std::string ones_and_zeros;
	double whole_size;
	double bit_time;
	int probing_frequency;
	int bits;
	double plotting_time;
	double* TTL;
	double* CLK;
	double* Manchester;



	Signal(std::string word, bool order, double bit_time, double probing_frequency, int bits) {
		this->ones_and_zeros = stringToBinary(word, order);
		this->bit_time = bit_time;
		this->bits = bits;
		this->plotting_time = bits * bit_time * probing_frequency;
		this->probing_frequency = probing_frequency;
		this->whole_size = ones_and_zeros.size() * bit_time * probing_frequency;

		this->TTL = new double[whole_size];
		this->CLK = new double[whole_size];
		this->Manchester = new double[whole_size];

	}
	std::string stringToBinary(std::string variable, bool select) {
		if (select == true) {
			std::string together = "";
			std::string zero = "0";
			for (int i = 0; i < variable.size(); i++) {
				int to_int = variable[i];
				char buffor[9];
				_itoa_s(to_int, buffor, 2);
				std::string to_zeros_and_ones(buffor);
				together += zero + to_zeros_and_ones;
			}
			return together;
		}
		else {
			std::string together = "";
			std::string zero = "0";
			for (int i = 0; i < variable.size(); i++) {
				int to_int = variable[i];
				char buffor[9];
				_itoa_s(to_int, buffor, 2);
				std::string to_zeros_and_ones(buffor);
				together += zero + to_zeros_and_ones;
			}
			std::reverse(together.begin(), together.end());
			return together;
		}
	}
	void set_TTL() {
		for (int i = 0; i < ones_and_zeros.length(); i++) {
			if (ones_and_zeros[i] == '0') {
				for (int j = 0; j < bit_time * probing_frequency; j++) {
					TTL[int(i * probing_frequency * bit_time) + j] = 0;
				}
			}
			else {
				for (int j = 0; j < bit_time * probing_frequency; j++) {
					TTL[int(i * probing_frequency * bit_time) + j] = 1;
				}
			}
		}
	}
	void set_CLK() {
		for (int i = 0; i < ones_and_zeros.length(); i++) {
			for (int j = 0; j < ceil((bit_time * probing_frequency) / 2); j++) {
				CLK[int(i * probing_frequency * bit_time) + j] = 1;
			}
			for (int j = ceil((bit_time * probing_frequency) / 2); j < bit_time * probing_frequency; j++) {
				CLK[int(i * probing_frequency * bit_time) + j] = 0;
			}
		}
	}
	void set_Manchester() {
		for (int i = 0; i < whole_size; i++) {
			if (TTL[i] == 0 && CLK[i] == 0) {
				Manchester[i] = 0;
			}
			if (TTL[i] == 0 && CLK[i] == 1) {
				Manchester[i] = 1;
			}
			if (TTL[i] == 1 && CLK[i] == 0) {
				Manchester[i] = 1;
			}
			if (TTL[i] == 1 && CLK[i] == 1) {
				Manchester[i] = 0;
			}
		}
	}

	void save_X(std::string filename) {
		std::ofstream file;
		file.open(filename);
		if (file.good()) {
			double temp;
			for (int i = 0; i < plotting_time; i++) {
				temp = (double)i / (double)probing_frequency;
				file << temp << std::endl;
			}
		}
		else {
			std::cout << "Could not write to the file " << std::endl;
		}
		file.close();
	}
	void save_Y(std::string filename, double* arr) {
		std::ofstream file;
		file.open(filename);
		if (file.good()) {
			for (int i = 0; i < plotting_time; i++) {
				file << arr[i] << std::endl;
			}
		}
		else {
			std::cout << "Could not write to the file " << std::endl;
		}
		file.close();
	}

	std::string decode_TTL() {
		std::string temp = "";
		for (int i = 0; i < ones_and_zeros.size(); i++) {
			temp += std::to_string((int)TTL[(int)(i * probing_frequency * bit_time)]);
		}
		return temp;
	}
	std::string decode_Manchester() {
		for (int i = 0; i < whole_size; i++) {
			if (Manchester[i] == 0 && CLK[i] == 0) {
				Manchester[i] = 1;
			}
			if (Manchester[i] == 0 && CLK[i] == 1) {
				Manchester[i] = 0;
			}
			if (Manchester[i] == 1 && CLK[i] == 0) {
				Manchester[i] = 0;
			}
			if (Manchester[i] == 1 && CLK[i] == 1) {
				Manchester[i] = 1;
			}
			std::string temp = "";

			for (int i = 0; i < ones_and_zeros.size(); i++) {
				if ((int)Manchester[(int)(i * probing_frequency * bit_time)] == 1) {
					temp += "0";
				}
				else {
					temp += "1";
				}
			}
			return temp;
		}

	}
	

	void compareOperation(std::string s1, std::string s2) {
		if ((s1.compare(s2)) == 0) {
			std::cout << " Match" << std::endl;
		}
		else {
			std::cout << " No match" << std::endl;
		}
	}
	void showDecoded() {
		std::cout << "Original signal is: " << ones_and_zeros << std::endl;
		std::cout << "TTL decoded: " << decode_TTL(); compareOperation(ones_and_zeros, decode_TTL());
		std::cout << "Manchester decoded: " << decode_Manchester(); compareOperation(ones_and_zeros, decode_Manchester());		

	}
	void saveToFiles() {
		set_TTL();
		set_CLK();
		set_Manchester();

		std::ofstream file;
		std::string x = "X_";
		std::string y = "Y_";
		std::string clk = "CLK.txt";
		std::string ttl = "TTL.txt";
		std::string man = "MAN.txt";
		std::string filename;

		//CLK
		save_X(x + clk);
		save_Y(y + clk, CLK);

		//ttl
		save_X(x + ttl);
		save_Y(y + ttl, TTL);

		//Manchester
		save_X(x + man);
		save_Y(y + man, Manchester);
	}
};

int main()
{
	Signal* test = new Signal("ABC", true, 1, 1000, 16);
	test->saveToFiles();
	test->showDecoded();
	return 0;
}