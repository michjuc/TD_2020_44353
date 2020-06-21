#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <bitset>
#include <stdlib.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <sstream>
#include <cstdlib>
#include <ctime>

class Complex {
public:
	double* real_value;
	double* imag_value;
	Complex(double length) {
		real_value = new double[length];
		imag_value = new double[length];
		for (int i = 0; i < length; i++) {
			real_value[i] = 0;
			imag_value[i] = 0;
		}
	}
};

class Signal {

public:
	const std::string BITS;
	const double BIT_TIME;
	const double PROBING_FREQUENCY;
	const double SECDED_SIZE;
	const double NORMAL_SIZE;

	const double BASE_AMPLITUDE;
	const double FRST_AMPLITUDE;
	const double SCND_AMPLITUDE;

	const double BASE_FREQUENCY;
	const double FRST_FREQUENCY;
	const double SCND_FREQUENCY;

	const double BASE_CONST_SHIFT;
	const double FRST_CONST_SHIFT;
	const double SCND_CONST_SHIFT;

	const double K_ASK;
	const double K_FSK;
	const double K_PSK;

	const double ALPHA;

	const int G_MATRIX[7][4] = { {1,1,0,1},{1,0,1,1},{1,0,0,0},{0,1,1,1},{0,1,0,0},{0,0,1,0},{0,0,0,1} };
	const int PARITY_MATRIX[3][7] = { {1,0,1,0,1,0,1},{0,1,1,0,0,1,1},{0,0,0,1,1,1,1} };

	Signal(std::string word, bool order, double BIT_TIME, double PROBING_FREQUENCY, double alpha, double N) :
		BITS(S2BS(word, order)),
		BIT_TIME(BIT_TIME),
		PROBING_FREQUENCY(PROBING_FREQUENCY),
		SECDED_SIZE(BITS.size() * 2 * BIT_TIME * PROBING_FREQUENCY),
		NORMAL_SIZE(BITS.size() / 4 * 7 * BIT_TIME * PROBING_FREQUENCY),
		BASE_AMPLITUDE(1.0), FRST_AMPLITUDE(1.0), SCND_AMPLITUDE(8.0),
		BASE_FREQUENCY(N* (1.0 / BIT_TIME)), FRST_FREQUENCY(round((N + 2) / BIT_TIME)), SCND_FREQUENCY(round((N + 1) / BIT_TIME)),
		BASE_CONST_SHIFT(1 * M_PI), FRST_CONST_SHIFT(0.0), SCND_CONST_SHIFT(M_PI),
		K_ASK(0.92), K_FSK(0.008), K_PSK(0.000001), ALPHA(alpha) {}

	std::string S2BS(std::string variable, bool select) {
		if (select == true) {
			std::string together = "";
			for (std::size_t i = 0; i < variable.size(); ++i) {
				std::bitset<8> b(variable.c_str()[i]);
				together += b.to_string();
			}
			return together;
		}
		else {
			std::string together = "";
			for (std::size_t i = 0; i < variable.size(); ++i) {
				std::bitset<8> b(variable.c_str()[i]);
				together += b.to_string();
			}
			std::reverse(together.begin(), together.end());
			return together;
		}
	}
	std::string SB2S(std::string variable) {
		std::string text = "";
		std::stringstream sstream(variable);
		while (sstream.good()) {
			std::bitset<8>bits;
			sstream >> bits;
			text += char(bits.to_ulong());
		}
		return text;
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
	double calculateBER(std::string variable) {
		double counter = 0;

		for (int i = 0; i < BITS.length(); i++) {
			if (BITS[i] != variable[i]) {
				counter++;
			}
		}
		return (counter / (double)BITS.length());
	}
	std::string decodeHamming(int** codes, bool select) {
		int size;
		std::string received = "";
		if (select == true) {
			size = 7;
		}
		else {
			size = 8;
		}
		for (int i = 0; i < (int)(BITS.length() / 4); i++) {

			std::string decoded = "";
			decoded += std::to_string(codes[2][i]);
			decoded += std::to_string(codes[4][i]);
			decoded += std::to_string(codes[5][i]);
			decoded += std::to_string(codes[6][i]);
			received += decoded;
		}
		std::cout << "Decoded message:" << SB2S(received) << std::endl;
		return received;
	}
	void checkCorrectness(int** codes, bool select) {

		std::cout << std::endl;
		std::cout << "Decoding before correction" << std::endl;
		std::string message = decodeHamming(codes, select);
		double BER_1 = calculateBER(message);
		std::cout << "BER equals:" << BER_1 << std::endl;
		std::cout << std::endl;

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

			std::cout << "Original signal:";
			for (int k = i * 4; k < ((i + 1) * 4); k++) {
				std::cout << BITS[k];
			}

			if (select == true) {
				std::cout << " received as: ";
				for (int j = 0; j < 7; j++) {
					std::cout << codes[j][i];
				}
				if (sum != 0) {
					std::cout << " with error in bit: " << sum << std::endl;
					if (codes[sum - 1][i] == 0) {
						codes[sum - 1][i] = 1;
					}
					else {
						codes[sum - 1][i] = 0;
					}
				}
				else {
					std::cout << " with no errors " << std::endl;
				}
			}
			else
			{
				std::cout << " received as: ";
				for (int j = 0; j < 8; j++) {
					std::cout << codes[j][i];
				}

				int parity_bit_check = 0;
				for (int j = 0; j < 7; j++) {
					parity_bit_check += codes[j][i];
				}
				parity_bit_check = parity_bit_check % 2;

				if (sum == 0 && parity_bit_check == codes[7][i]) {
					std::cout << " with no errors " << std::endl;
				}
				else if (sum != 0 && parity_bit_check != codes[7][i]) {
					std::cout << " with error in bit: " << sum << std::endl;
					if (codes[sum - 1][i] == 0) {
						codes[sum - 1][i] = 1;
					}
					else {
						codes[sum - 1][i] = 0;
					}
				}
				else if (sum != 0 && parity_bit_check == codes[7][i]) {
					std::cout << " with double bit error " << std::endl;
				}
				else if (sum == 0 && parity_bit_check != codes[7][i]) {
					std::cout << " with error in bit: " << 8 << std::endl;
					if (codes[7][i] == 0) {
						codes[7][i] = 1;
					}
					else {
						codes[7][i] = 0;
					}
				}
			}
		}

		std::cout << std::endl;
		std::cout << "Decoding after correction" << std::endl;
		std::cout << std::endl;
		message = decodeHamming(codes, select);
		double BER_2 = calculateBER(message);
		std::cout << "BER equals:" << BER_2 << std::endl;
		std::cout << "Difference before and after correction(positive = less errors, negative = more errors):" << BER_1 - BER_2 << std::endl;

	}
	int* hammingToArray(int** codes, int SIZE, int bits) {
		int* NEW_HAMMING = new int[SIZE];
		for (int i = 0; i < BITS.length() / 4; i++) {
			for (int j = 0; j < bits; j++) {
				for (int k = 0; k < BIT_TIME * PROBING_FREQUENCY; k++) {
					NEW_HAMMING[(int)(i * bits * BIT_TIME * PROBING_FREQUENCY + j * BIT_TIME * PROBING_FREQUENCY) + k] = codes[j][i];
				}
			}
		}
		return NEW_HAMMING;
	}

	Complex* DFT(int SIZE, double* VALUES) {
		Complex* dft = new Complex(SIZE);
		for (int k = 0; k < SIZE; k++) {
			double real_temp_sum = 0;
			double imag_temp_sum = 0;
			for (int n = 0; n < SIZE; n++) {
				real_temp_sum += VALUES[n] * cos(-2 * M_PI * n * k / (SIZE));
				imag_temp_sum += VALUES[n] * sin(-2 * M_PI * n * k / (SIZE));
			}
			dft->real_value[k] = real_temp_sum;
			dft->imag_value[k] = imag_temp_sum;
		}
		return dft;
	}
	double* setAmplitudeSpecturm(int SIZE, Complex* dft) {
		double* ampli_spec = new double[SIZE];
		for (int k = 0; k < SIZE; k++) {
			ampli_spec[k] = sqrt(pow(dft->real_value[k], 2) + pow(dft->imag_value[k], 2));
		}
		return ampli_spec;
	}
	double* setStripeFrequency(int SIZE) {
		double* stripe_freq = new double[SIZE];
		for (int k = 0; k < SIZE; k++) {
			stripe_freq[k] = (k * PROBING_FREQUENCY) / (SIZE);
		}
		return stripe_freq;
	}
	double* logFunc(double* amplitude_spectrum, int SIZE) {
		for (int k = 0; k < SIZE; k++) {
			if (amplitude_spectrum[k] != 0)amplitude_spectrum[k] = 10 * log10(amplitude_spectrum[k]);
		}
		return amplitude_spectrum;
	}

	double* values_ASK(int* HAMMING_VALUES, int SIZE) {
		double* ASK_VALUES = new double[SIZE];
		for (int i = 0; i < SIZE; i++) {
			if (HAMMING_VALUES[i] == 0) {
				ASK_VALUES[i] = FRST_AMPLITUDE * sin(2 * M_PI * BASE_FREQUENCY * i / PROBING_FREQUENCY + BASE_CONST_SHIFT);
			}
			else {
				ASK_VALUES[i] = SCND_AMPLITUDE * sin(2 * M_PI * BASE_FREQUENCY * i / PROBING_FREQUENCY + BASE_CONST_SHIFT);
			}
		}
		return ASK_VALUES;

	}

	double* integral_ASK(double* MODIFIED_ASK, int SIZE, int bits) {

		double* ASK_INTEGRAL = new double[SIZE];
		for (int i = 0; i < bits; i++) {
			ASK_INTEGRAL[(int)(i * PROBING_FREQUENCY * BIT_TIME)] = MODIFIED_ASK[int(i * PROBING_FREQUENCY * BIT_TIME)] * 1 / PROBING_FREQUENCY;
			for (int j = 1; j < BIT_TIME * PROBING_FREQUENCY; j++) {
				ASK_INTEGRAL[(int)(i * PROBING_FREQUENCY * BIT_TIME) + j] = ASK_INTEGRAL[(int)(i * PROBING_FREQUENCY * BIT_TIME + j - 1)] + MODIFIED_ASK[(int)(i * PROBING_FREQUENCY * BIT_TIME + j)] * 1 / PROBING_FREQUENCY;
			}
		}
		return ASK_INTEGRAL;
	}

	int* toSignal_ASK(double* ASK_INTEGRAL, int SIZE) {
		int* ASK_SIGNAL = new int[SIZE];
		for (int i = 0; i < SIZE; i++) {
			if (ASK_INTEGRAL[i] > K_ASK)ASK_SIGNAL[i] = 1;
			else {
				ASK_SIGNAL[i] = 0;
			}
		}
		return ASK_SIGNAL;
	}

	int** convertToHamming(int* SIGNAL, int SIZE) {
		int** codes = new int* [SIZE];
		for (int i = 0; i < SIZE; i++)
			codes[i] = new int[BITS.length() / 4];

		for (int i = 0; i < BITS.length() / 4; i++)
			for (int j = 0; j < SIZE; j++) {
				bool control = true;
				for (int k = 0; k < BIT_TIME * PROBING_FREQUENCY; k++) {
					if (SIGNAL[(int)(i * SIZE * BIT_TIME * PROBING_FREQUENCY + j * BIT_TIME * PROBING_FREQUENCY + k)] == 1) {
						control = false;
					}
				}
				if (control == false) {
					codes[j][i] = 1;
				}
				else {
					codes[j][i] = 0;
				}
			}
		return codes;

	}

	void save_stripe_X(std::string filename, int size, double* stripe_freq) {
		std::ofstream file;
		file.open(filename);
		if (file.good()) {
			for (int i = 0; i < size; i++) {
				file << stripe_freq[i] << std::endl;
			}
		}
		else {
			std::cout << "Could not write to the file " << std::endl;
		}
		file.close();
	}
	void save_X(std::string filename, int size) {
		std::ofstream file;
		file.open(filename);
		if (file.good()) {
			double temp;
			for (int i = 0; i < size; i++) {
				temp = (double)i / (double)PROBING_FREQUENCY;
				file << temp << std::endl;
			}
		}
		else {
			std::cout << "Could not write to the file " << std::endl;
		}
		file.close();
	}
	void save_Y(std::string filename, double* arr, int size) {
		std::ofstream file;
		file.open(filename);
		if (file.good()) {
			for (int i = 0; i < size; i++) {
				file << arr[i] << std::endl;
			}
		}
		else {
			std::cout << "Could not write to the file " << std::endl;
		}
		file.close();
	}
	void save_Y_INT(std::string filename, int* arr, int size) {
		std::ofstream file;
		file.open(filename);
		if (file.good()) {
			for (int i = 0; i < size; i++) {
				file << arr[i] << std::endl;
			}
		}
		else {
			std::cout << "Could not write to the file " << std::endl;
		}
		file.close();
	}

	void plotDFT(int SIZE, double* ASK_VALUES, double* FSK_VALUES, double* PSK_VALUES) {
		Complex* ASK_DFT = DFT(SIZE, ASK_VALUES);
		double* STRIPE_FREQUENCY = setStripeFrequency(SIZE);
		double* ASK_SPECTRUM = logFunc(setAmplitudeSpecturm(SIZE, ASK_DFT), SIZE);
		save_stripe_X("STRIPE_FREQUENCY.txt", SIZE, STRIPE_FREQUENCY);
		save_Y("ASK_SPECTRUM.txt", ASK_SPECTRUM, SIZE);
		delete ASK_SPECTRUM, ASK_DFT;

		
	}

	void mainLoop(bool select) {

		int SIZE;
		int bits_arr;
		int bits;

		if (select == true) {
			SIZE = NORMAL_SIZE;
			bits_arr = BITS.size() / 4 * 7;
			bits = 7;
		}
		else {
			SIZE = SECDED_SIZE;
			bits_arr = BITS.size() / 4 * 8;
			bits = 8;
		}
		int** TWO_DIM_HAMMING = hammingCode(select);
		int* HAMMING_VALUES = hammingToArray(TWO_DIM_HAMMING, SIZE, bits);
		double* ASK_VALUES = values_ASK(HAMMING_VALUES, SIZE);
		double* ASK_INTEGRAL = integral_ASK(ASK_VALUES, SIZE, bits_arr);
		int* ASK_SIGNAL = toSignal_ASK(ASK_INTEGRAL, SIZE);
		int** RECEIVED_ASK = convertToHamming(ASK_SIGNAL, bits);

		save_Y_INT("HAMMING_VALUES.txt", HAMMING_VALUES, SIZE);
		save_Y("ASK_VALUES.txt", ASK_VALUES, SIZE);
		save_Y("ASK_INTEGRAL.txt", ASK_INTEGRAL, SIZE);	
		save_X("X_VALUES.txt", SIZE);

		std::cout << "---------------------------ASK---------------------------" << std::endl;
		checkCorrectness(RECEIVED_ASK, select);
	}
};
int main()
{
	//0.9
	Signal* test = new Signal("test signal", true, 0.1, 1000, 0.4, 10);
	test->mainLoop(true);
	delete test;
	return 0;
}