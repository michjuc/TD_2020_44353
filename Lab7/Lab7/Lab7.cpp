#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#define _USE_MATH_DEFINES
#include <math.h>

class Signal {
public:
	const std::string BITS;
	const int G_MATRIX[7][4] = { {1,1,0,1},{1,0,1,1},{1,0,0,0},{0,1,1,1},{0,1,0,0},{0,0,1,0},{0,0,0,1} };
	const int PARITY_MATRIX[3][7] = { {1,0,1,0,1,0,1},{0,1,1,0,0,1,1},{0,0,0,1,1,1,1} };
	Signal(std::string word, bool select) : BITS(stringToBinary(word, select)) {}

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
	int** hammingCode(bool select) {
		if (select == true) {
			int** codes = new int* [7];
			for (int i = 0; i < 7; i++)
				codes[i] = new int[BITS.length() / 4];

			for (int i = 0; i < BITS.length() / 4; i++)
				for (int j = 0; j < 7; j++) {
					int temp = 0;
					for (int k = 0; k < 4; k++) {
						temp += G_MATRIX[j][k] * BITS[i * 4 + k];
					}
					codes[j][i] = temp % 2;
				}
			return codes;
		}
		else {
			int** codes = new int* [8];
			for (int i = 0; i < 8; i++)
				codes[i] = new int[BITS.length() / 4];

			for (int i = 0; i < BITS.length() / 4; i++)
				for (int j = 0; j < 7; j++) {
					int temp = 0;
					for (int k = 0; k < 4; k++) {
						temp += G_MATRIX[j][k] * BITS[i * 4 + k];
					}
					codes[j][i] = temp % 2;
				}
			for (int i = 0; i < BITS.length() / 4; i++) {
				int sum = 0;
				for (int j = 0; j < 7; j++) {
					sum += codes[j][i];
				}
				sum = sum % 2;
				codes[7][i] = sum;
			}
			return codes;
		}
	}
	void printCoded(int** codes, bool select) {
		int rows;
		if (select == true) {
			rows = 7;
		}
		else {
			rows = 8;
		}
		for (int i = 0; i < (int)(BITS.length() / 4); i++) {
			std::cout << "BITS:";
			for (int k = i * 4; k < ((i + 1) * 4); k++)
				std::cout << BITS[k];

			std::cout << std::endl << "Hamming code:";
			for (int j = 0; j < rows; j++) {
				std::cout << codes[j][i];
			}
			std::cout << std::endl;
		}
	}
	void decodeHamming(int** codes, int* to_print, bool select) {
		int size;
		if (select == true) {
			size = 7;
		}
		else {
			size = 8;
		}
		for (int i = 0; i < (int)(BITS.length() / 4); i++) {
			for (int j = 0; j < size; j++) {
				std::cout << codes[j][i];
			}
			std::cout << "-->";
			if (to_print[i] == 0) {
				std::string decoded = "";
				decoded += std::to_string(codes[2][i]);
				decoded += std::to_string(codes[4][i]);
				decoded += std::to_string(codes[5][i]);
				decoded += std::to_string(codes[6][i]);
				std::cout << decoded << std::endl;
			}
			else {
				std::cout << "Double bit error" << std::endl;
			}
		}

	}
	void checkCorrectness(int** codes, bool select) {

		int* to_print = new int[(int)(BITS.length() / 4)];
		int** syndrome = new int* [3];
		for (int i = 0; i < 3; i++) {
			syndrome[i] = new int[BITS.length() / 4];
		}

		for (int i = 0; i < (int)(BITS.length() / 4); i++) {
			for (int j = 0; j < 3; j++) {
				int temp = 0;
				for (int k = 0; k < 7; k++) {
					temp += PARITY_MATRIX[j][k] * codes[k][i];
				}
				syndrome[j][i] = temp % 2;
			}
		}

		for (int i = 0; i < (int)(BITS.length() / 4); i++) {

			int sum = 0;

			for (int j = 0; j < 3; j++) {
				sum += syndrome[j][i] * pow(2, j);
			}

			for (int k = i * 4; k < ((i + 1) * 4); k++) {
				std::cout << BITS[k];
			}

			if (select == true) {
				std::cout << "-->";
				for (int j = 0; j < 7; j++) {
					std::cout << codes[j][i];
				}
				if (sum != 0) {
					std::cout << "-->Error in bit:" << sum + i * 7 << std::endl;
					if (codes[sum - 1][i] == 0) {
						codes[sum - 1][i] = 1;
					}
					else {
						codes[sum - 1][i] = 0;
					}
					to_print[i] = 0;
				}
				else {
					std::cout << "-->Correct" << std::endl;
					to_print[i] = 0;
				}
			}
			else
			{
				std::cout << "-->";
				for (int j = 0; j < 8; j++) {
					std::cout << codes[j][i];
				}

				int parity_bit_check = 0;
				for (int j = 0; j < 7; j++) {
					parity_bit_check += codes[j][i];
				}
				parity_bit_check = parity_bit_check % 2;

				if (sum == 0 && parity_bit_check == codes[7][i]) {
					std::cout << "-->Correct" << std::endl;
					to_print[i] = 0;
				}
				else if (sum != 0 && parity_bit_check != codes[7][i]) {
					std::cout << "-->Error in bit:" << sum + i * 8 << std::endl;
					if (codes[sum - 1][i] == 0) {
						codes[sum - 1][i] = 1;
					}
					else {
						codes[sum - 1][i] = 0;
					}
					to_print[i] = 0;
				}
				else if (sum != 0 && parity_bit_check == codes[7][i]) {
					std::cout << "-->Double bit error" << std::endl;
					to_print[i] = 1;
				}
				else if (sum == 0 && parity_bit_check != codes[7][i]) {
					std::cout << "-->Error in bit:" << 8 + i * 8 << std::endl;
					if (codes[7][i] == 0) {
						codes[7][i] = 1;
					}
					else {
						codes[7][i] = 0;
					}
					to_print[i] = 0;
				}
			}
		}

		std::cout << std::endl;
		std::cout << "Decoding after correction" << std::endl;
		std::cout << std::endl;
		decodeHamming(codes, to_print, select);
	}
	int** falsifyBit(int** codes, int bit, bool select) {
		int rows;
		if (select == true) {
			rows = 7;
		}
		else {
			rows = 8;
		}
		bit--;
		if (bit > BITS.length() * 8 / 4 * rows || bit < 0) {
			std::cout << "Selected wrong bit!" << std::endl;
		}
		else {
			int column = bit / rows;
			int row = bit % rows;
			if (codes[row][column] == 0) {
				codes[row][column] = 1;
			}
			else {
				codes[row][column] = 0;
			}
		}
		return codes;
	}
};
int main()
{
	Signal* test = new Signal("OBC", true);
	//std::cout << "1.BITS:" << test->BITS << std::endl;
	//std::cout << "2.BITS:" << test->decodeHamming(test->hammingCode())<<std::endl;
	//test->printCoded(test->hammingCode(false), false);
	//test->checkCorrectness(test->falsifyBit(test->falsifyBit(test->falsifyBit(test->falsifyBit(test->hammingCode(false), 7, false), 1, false), 16, false), 20, false), false);

	test->checkCorrectness(test->falsifyBit(test->falsifyBit(test->hammingCode(true), 1, true), 16, true), true);

	delete test;
	return 0;
}