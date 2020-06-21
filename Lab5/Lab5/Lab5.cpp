#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#define _USE_MATH_DEFINES
#include <math.h>

class Complex {
public:
	double* real_value;
	double* imag_value;
	Complex(int length) {
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

	std::string ones_and_zeros;
	double bit_time;
	int amount;
	double N;
	int probing_frequency;
	double base_frequency;
	double frst_frequency;
	double scnd_frequency;
	double base_amplitude;
	double frst_amplitude;
	double scnd_amplitude;
	double base_const_shift;
	double frst_const_shift;
	double scnd_const_shift;
	double* information_signal;
	double* ask_modulation;
	double* fsk_modulation;
	double* psk_modulation;
	Complex* ASK_DFT_VALUES;
	Complex* FSK_DFT_VALUES;
	Complex* PSK_DFT_VALUES;
	double* stripe_frequency;
	double* ask_spectrum;
	double* fsk_spectrum;
	double* psk_spectrum;
	int bits;
	double whole_size;
	Signal(std::string word, bool order, double bit_time, double base_amplitude, double base_const_shift, double N, int bits, int probing_frequency) {
		this->probing_frequency = probing_frequency;
		this->ones_and_zeros = stringToBinary(word, order);
		this->bit_time = bit_time;
		this->N = N;
		this->whole_size = ones_and_zeros.size() * bit_time * probing_frequency;
		//frequency
		this->base_frequency = N * (1.0 / bit_time);
		this->frst_frequency = round((N + 1) / bit_time);
		this->scnd_frequency = round((N + 2) / bit_time);
		//amplitude
		this->base_amplitude = base_amplitude;
		this->frst_amplitude = 1;
		this->scnd_amplitude = 8;
		//const shift
		this->base_const_shift = base_const_shift;
		this->frst_const_shift = 0;
		this->scnd_const_shift = M_PI;
		//functions
		this->information_signal = new double[whole_size];
		this->ask_modulation = new double[whole_size];
		this->fsk_modulation = new double[whole_size];
		this->psk_modulation = new double[whole_size];
		//DFT values
		this->ASK_DFT_VALUES = new Complex(whole_size);
		this->FSK_DFT_VALUES = new Complex(whole_size);
		this->PSK_DFT_VALUES = new Complex(whole_size);
		//spectrum and frequency
		this->stripe_frequency = new double[whole_size];
		this->ask_spectrum = new double[whole_size];
		this->fsk_spectrum = new double[whole_size];
		this->psk_spectrum = new double[whole_size];

		this->bits = bits;
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
	void stringToInformationSignal() {
		for (int i = 0; i < ones_and_zeros.length(); i++) {
			if (ones_and_zeros[i] == '0') {
				for (int j = 0; j < bit_time * probing_frequency; j++) {
					information_signal[(int)(i * probing_frequency * bit_time) + j] = 0;
				}
			}
			else {
				for (int j = 0; j < bit_time * probing_frequency; j++) {
					information_signal[(int)(i * probing_frequency * bit_time) + j] = 1;
				}
			}
		}
	}
	void ASK_FunctionValues() {
		for (int i = 0; i < whole_size; i++) {
			if (information_signal[i] == 0) {
				ask_modulation[i] = frst_amplitude * sin(2 * M_PI * base_frequency * ((bit_time * i) / probing_frequency) + base_const_shift);
			}
			else {
				ask_modulation[i] = scnd_amplitude * sin(2 * M_PI * base_frequency * ((bit_time * i) / probing_frequency) + base_const_shift);
			}
		}
	}
	void FSK_FunctionValues() {
		for (int i = 0; i < whole_size; i++) {
			if (information_signal[i] == 0) {
				fsk_modulation[i] = base_amplitude * sin(2 * M_PI * frst_frequency * ((bit_time * i) / probing_frequency) + base_const_shift);
			}
			else {
				fsk_modulation[i] = base_amplitude * sin(2 * M_PI * scnd_frequency * ((bit_time * i) / probing_frequency) + base_const_shift);
			}
		}
	}
	void PSK_FunctionValues() {
		for (int i = 0; i < whole_size; i++) {
			if (information_signal[i] == 0) {
				psk_modulation[i] = base_amplitude * sin(2 * M_PI * base_frequency * ((bit_time * i) / probing_frequency) + frst_const_shift);
			}
			else {
				psk_modulation[i] = base_amplitude * sin(2 * M_PI * base_frequency * ((bit_time * i) / probing_frequency) + scnd_const_shift);
			}
		}
	}

	void ASK_DFT() {
		for (int k = 0; k < whole_size; k++) {
			double real_temp_sum = 0;
			double imag_temp_sum = 0;
			for (int n = 0; n < whole_size; n++) {
				real_temp_sum += ask_modulation[n] * cos(-2 * M_PI * n * k / whole_size);
				imag_temp_sum += ask_modulation[n] * sin(-2 * M_PI * n * k / whole_size);
			}
			ASK_DFT_VALUES->real_value[k] = real_temp_sum;
			ASK_DFT_VALUES->imag_value[k] = imag_temp_sum;
		}
	}
	void FSK_DFT() {
		for (int k = 0; k < whole_size; k++) {
			double real_temp_sum = 0;
			double imag_temp_sum = 0;
			for (int n = 0; n < whole_size; n++) {
				real_temp_sum += fsk_modulation[n] * cos(-2 * M_PI * n * k / whole_size);
				imag_temp_sum += fsk_modulation[n] * sin(-2 * M_PI * n * k / whole_size);
			}
			FSK_DFT_VALUES->real_value[k] = real_temp_sum;
			FSK_DFT_VALUES->imag_value[k] = imag_temp_sum;
		}
	}
	void PSK_DFT() {
		for (int k = 0; k < whole_size; k++) {
			double real_temp_sum = 0;
			double imag_temp_sum = 0;
			for (int n = 0; n < whole_size; n++) {
				real_temp_sum += psk_modulation[n] * cos(-2 * M_PI * n * k / whole_size);
				imag_temp_sum += psk_modulation[n] * sin(-2 * M_PI * n * k / whole_size);
			}
			PSK_DFT_VALUES->real_value[k] = real_temp_sum;
			PSK_DFT_VALUES->imag_value[k] = imag_temp_sum;
		}
	}

	void ASK_Spectrum() {
		for (int k = 0; k < whole_size; k++) {
			ask_spectrum[k] = sqrt(pow(ASK_DFT_VALUES->real_value[k], 2) + pow(ASK_DFT_VALUES->imag_value[k], 2));
			stripe_frequency[k] = k * ((probing_frequency) / whole_size);
		}
	}
	void FSK_Spectrum() {
		for (int k = 0; k < whole_size; k++) {
			fsk_spectrum[k] = sqrt(pow(FSK_DFT_VALUES->real_value[k], 2) + pow(FSK_DFT_VALUES->imag_value[k], 2));
		}
	}
	void PSK_Spectrum() {
		for (int k = 0; k < whole_size; k++) {
			psk_spectrum[k] = sqrt(pow(PSK_DFT_VALUES->real_value[k], 2) + pow(PSK_DFT_VALUES->imag_value[k], 2));
		}
	}

	void ASK_toLog() {
		for (int k = 0; k < whole_size; k++) {
			if (ask_spectrum[k] != 0)ask_spectrum[k] = 10 * log10(ask_spectrum[k]);
		}
	}
	void FSK_toLog() {
		for (int k = 0; k < whole_size; k++) {
			if (fsk_spectrum[k] != 0)fsk_spectrum[k] = 10 * log10(fsk_spectrum[k]);
		}
	}
	void PSK_toLog() {
		for (int k = 0; k < whole_size; k++) {
			if (psk_spectrum[k] != 0)psk_spectrum[k] = 10 * log10(psk_spectrum[k]);
		}
	}

	void ASK_Bandwidth() {
		int MAX_X = 0;
		for (int i = 1; i < ceil(whole_size) / 2; i++) {
			if (ask_spectrum[i] > ask_spectrum[MAX_X])MAX_X = i;
		}
		double fmin = stripe_frequency[MAX_X];
		double fmax = stripe_frequency[MAX_X];

		for (int i = MAX_X + 1; i < ceil(whole_size / 2); i++) {
			if (ask_spectrum[i] >= ask_spectrum[MAX_X] - 3) {
				fmax = stripe_frequency[i];
			}
		}
		if (MAX_X != 0) {
			for (int i = MAX_X - 1; i >= 0; i--) {
				if (ask_spectrum[i] >= ask_spectrum[MAX_X] - 3) {
					fmin = stripe_frequency[i];
				}
			}
		}
		else {
			fmin = 0;
		}

		double width;
		if (fmin == fmax)width = 1;
		else {
			width = fmax - fmin;
		}

		std::cout << "Max w :" << stripe_frequency[MAX_X] << std::endl;
		std::cout << "Lewy kraniec w :" << fmin << std::endl;
		std::cout << "Prawy kraniec w : " << fmax << std::endl;
		std::cout << std::endl;
		std::cout << "Szerokosc pasma sygnalu za(t) wynosi: " << width << "Hz" << std::endl;
	}
	void FSK_Bandwidth() {
		int MAX_X = 0;
		for (int i = 1; i < ceil(whole_size) / 2; i++) {
			if (fsk_spectrum[i] > fsk_spectrum[MAX_X])MAX_X = i;
		}
		double fmin = stripe_frequency[MAX_X];
		double fmax = stripe_frequency[MAX_X];

		for (int i = MAX_X + 1; i < ceil(whole_size / 2); i++) {
			if (fsk_spectrum[i] >= fsk_spectrum[MAX_X] - 3) {
				fmax = stripe_frequency[i];
			}
		}
		if (MAX_X != 0) {
			for (int i = MAX_X - 1; i >= 0; i--) {
				if (fsk_spectrum[i] >= fsk_spectrum[MAX_X] - 3) {
					fmin = stripe_frequency[i];
				}
			}
		}
		else {
			fmin = 0;
		}
		double width;
		if (fmin == fmax)width = 1;
		else {
			width = fmax - fmin;
		}

		std::cout << "Max w :" << stripe_frequency[MAX_X] << std::endl;
		std::cout << "Lewy kraniec w :" << fmin << std::endl;
		std::cout << "Prawy kraniec w : " << fmax << std::endl;
		std::cout << std::endl;
		std::cout << "Szerokosc pasma sygnalu za(t) wynosi: " << width << "Hz" << std::endl;
	}
	void PSK_Bandwidth() {
		int MAX_X = 0;
		for (int i = 1; i < ceil(whole_size) / 2; i++) {
			if (psk_spectrum[i] > psk_spectrum[MAX_X])MAX_X = i;
		}
		double fmin = stripe_frequency[MAX_X];
		double fmax = stripe_frequency[MAX_X];

		for (int i = MAX_X + 1; i < ceil(whole_size / 2); i++) {
			if (psk_spectrum[i] >= psk_spectrum[MAX_X] - 3) {
				fmax = stripe_frequency[i];
			}
		}
		if (MAX_X != 0) {
			for (int i = MAX_X - 1; i >= 0; i--) {
				if (psk_spectrum[i] >= psk_spectrum[MAX_X] - 3) {
					fmin = stripe_frequency[i];
				}
			}
		}
		else {
			fmin = 0;
		}

		double width;
		if (fmin == fmax)width = 1;
		else {
			width = fmax - fmin;
		}

		std::cout << "Max w :" << stripe_frequency[MAX_X] << std::endl;
		std::cout << "Lewy kraniec w :" << fmin << std::endl;
		std::cout << "Prawy kraniec w : " << fmax << std::endl;
		std::cout << std::endl;
		std::cout << "Szerokosc pasma sygnalu za(t) wynosi: " << width << "Hz" << std::endl;
	}

	void alternative_ASK_Bandwidth() {
		int MAX_X = 0;
		for (int i = 1; i < ceil(whole_size) / 2; i++) {
			if (ask_spectrum[i] > ask_spectrum[MAX_X])MAX_X = i;
		}
		double fmin = stripe_frequency[0];
		double fmax = stripe_frequency[MAX_X + 1];
		double difference = abs((ask_spectrum[MAX_X] - 3) - ask_spectrum[0]);
		for (int i = 1; i < MAX_X; i++) {
			if (difference > abs((ask_spectrum[MAX_X] - 3) - ask_spectrum[i])) {
				difference = abs((ask_spectrum[MAX_X] - 3) - ask_spectrum[i]);
				fmin = stripe_frequency[i];
			}
		}
		difference = abs((ask_spectrum[MAX_X] - 3) - ask_spectrum[MAX_X + 1]);
		for (int i = MAX_X + 2; i < ceil(whole_size) / 2; i++) {
			if (difference > abs((ask_spectrum[MAX_X] - 3) - ask_spectrum[i])) {
				difference = abs((ask_spectrum[MAX_X] - 3) - ask_spectrum[i]);
				fmax = stripe_frequency[i];
			}
		}
		std::cout << "Max w :" << MAX_X << std::endl;
		std::cout << "Lewy kraniec w :" << fmin << std::endl;
		std::cout << "Prawy kraniec w : " << fmax << std::endl;
		std::cout << std::endl;
		std::cout << "Szerokosc pasma ASK wynosi: " << fmax - fmin << "Hz" << std::endl;
	}
	void alternative_PSK_Bandwidth() {
		int MAX_X = 0;
		for (int i = 1; i < ceil(whole_size) / 2; i++) {
			if (psk_spectrum[i] > psk_spectrum[MAX_X])MAX_X = i;
		}
		double fmin = stripe_frequency[0];
		double fmax = stripe_frequency[MAX_X + 1];
		double difference = abs((psk_spectrum[MAX_X] - 3) - psk_spectrum[0]);
		for (int i = 1; i < MAX_X; i++) {
			if (difference > abs((psk_spectrum[MAX_X] - 3) - psk_spectrum[i])) {
				difference = abs((psk_spectrum[MAX_X] - 3) - psk_spectrum[i]);
				fmin = stripe_frequency[i];
			}
		}
		difference = abs((psk_spectrum[MAX_X] - 3) - psk_spectrum[MAX_X + 1]);
		for (int i = MAX_X + 2; i < ceil(whole_size) / 2; i++) {
			if (difference > abs((psk_spectrum[MAX_X] - 3) - psk_spectrum[i])) {
				difference = abs((psk_spectrum[MAX_X] - 3) - psk_spectrum[i]);
				fmax = stripe_frequency[i];
			}
		}
		std::cout << "Max w :" << MAX_X << std::endl;
		std::cout << "Lewy kraniec w :" << fmin << std::endl;
		std::cout << "Prawy kraniec w : " << fmax << std::endl;
		std::cout << std::endl;
		std::cout << "Szerokosc pasma ASK wynosi: " << fmax - fmin << "Hz" << std::endl;
	}
	void alternative_FSK_Bandwidth() {
		int MAX_X = 0;
		for (int i = 1; i < ceil(whole_size) / 2; i++) {
			if (fsk_spectrum[i] > fsk_spectrum[MAX_X])MAX_X = i;
		}
		double fmin = stripe_frequency[0];
		double fmax = stripe_frequency[MAX_X + 1];
		double difference = abs((fsk_spectrum[MAX_X] - 3) - fsk_spectrum[0]);
		for (int i = 1; i < MAX_X; i++) {
			if (difference > abs((fsk_spectrum[MAX_X] - 3) - fsk_spectrum[i])) {
				difference = abs((fsk_spectrum[MAX_X] - 3) - fsk_spectrum[i]);
				fmin = stripe_frequency[i];
			}
		}
		difference = abs((fsk_spectrum[MAX_X] - 3) - fsk_spectrum[MAX_X + 1]);
		for (int i = MAX_X + 2; i < ceil(whole_size) / 2; i++) {
			if (difference > abs((fsk_spectrum[MAX_X] - 3) - fsk_spectrum[i])) {
				difference = abs((fsk_spectrum[MAX_X] - 3) - fsk_spectrum[i]);
				fmax = stripe_frequency[i];
			}
		}
		std::cout << "Max w :" << MAX_X << std::endl;
		std::cout << "Lewy kraniec w :" << fmin << std::endl;
		std::cout << "Prawy kraniec w : " << fmax << std::endl;
		std::cout << std::endl;
		std::cout << "Szerokosc pasma ASK wynosi: " << fmax - fmin << "Hz" << std::endl;
	}

	void saveToFiles() {
		stringToInformationSignal();
		ASK_FunctionValues();
		FSK_FunctionValues();
		PSK_FunctionValues();
		ASK_DFT();
		FSK_DFT();
		PSK_DFT();
		ASK_Spectrum();
		FSK_Spectrum();
		PSK_Spectrum();
		ASK_toLog();
		FSK_toLog();
		PSK_toLog();
		ASK_Bandwidth();
		FSK_Bandwidth();
		PSK_Bandwidth();

		std::cout << "ASK" << std::endl;
		//alternative_ASK_Bandwidth();
		std::cout << "FSK" << std::endl;
		//alternative_FSK_Bandwidth();
		std::cout << "PSK" << std::endl;
		//alternative_PSK_Bandwidth();

		std::ofstream file;
		std::string x = "X_";
		std::string y = "Y_";
		std::string inf = "INF.txt";
		std::string ask = "ASK_";
		std::string fsk = "FSK_";
		std::string psk = "PSK_";
		std::string spec = "SPEC.txt";
		std::string norm = "NORM.txt";
		std::string whl = "whl.txt";
		std::string filename = x + inf;

		//information signal
		file.open(filename);
		if (file.good()) {
			for (int i = 0; i < bits * bit_time * probing_frequency; i++) {
				file << ((bit_time * i) / probing_frequency) << std::endl;
			}
		}
		else {
			std::cout << "Could not write to the file " << std::endl;
		}
		file.close();

		filename = y + inf;
		file.open(filename);
		if (file.good()) {
			for (int i = 0; i < bits * bit_time * probing_frequency; i++) {
				file << information_signal[i] << std::endl;
			}
		}
		else {
			std::cout << "Could not write to the file " << std::endl;
		}
		file.close();

		//SIGNALS TO 10 BITS

		//ask
		filename = x + ask + norm;
		file.open(filename);
		if (file.good()) {
			for (int i = 0; i < bits * bit_time * probing_frequency; i++) {
				file << ((bit_time * i) / probing_frequency) << std::endl;
			}
		}
		else {
			std::cout << "Could not write to the file " << std::endl;
		}
		file.close();

		filename = y + ask + norm;
		file.open(filename);
		if (file.good()) {
			for (int i = 0; i < bits * bit_time * probing_frequency; i++) {
				file << ask_modulation[i] << std::endl;
			}
		}
		else {
			std::cout << "Could not write to the file " << std::endl;
		}
		file.close();

		//fsk
		filename = x + fsk + norm;
		file.open(filename);
		if (file.good()) {
			for (int i = 0; i < bits * bit_time * probing_frequency; i++) {
				file << ((bit_time * i) / probing_frequency) << std::endl;
			}
		}
		else {
			std::cout << "Could not write to the file " << std::endl;
		}
		file.close();

		filename = y + fsk + norm;
		file.open(filename);
		if (file.good()) {
			for (int i = 0; i < bits * bit_time * probing_frequency; i++) {
				file << fsk_modulation[i] << std::endl;
			}
		}
		else {
			std::cout << "Could not write to the file " << std::endl;
		}
		file.close();

		//psk
		filename = x + psk + norm;
		file.open(filename);
		if (file.good()) {
			for (int i = 0; i < bits * bit_time * probing_frequency; i++) {
				file << ((bit_time * i) / probing_frequency) << std::endl;
			}
		}
		else {
			std::cout << "Could not write to the file " << std::endl;
		}
		file.close();

		filename = y + psk + norm;
		file.open(filename);
		if (file.good()) {
			for (int i = 0; i < bits * bit_time * probing_frequency; i++) {
				file << psk_modulation[i] << std::endl;
			}
		}
		else {
			std::cout << "Could not write to the file " << std::endl;
		}
		file.close();


		//WHOLE SIGNALS
			//ask
		filename = x + ask + whl;
		file.open(filename);
		if (file.good()) {
			for (int i = 0; i < whole_size; i++) {
				file << ((bit_time * i) / probing_frequency) << std::endl;
			}
		}
		else {
			std::cout << "Could not write to the file " << std::endl;
		}
		file.close();

		filename = y + ask + whl;
		file.open(filename);
		if (file.good()) {
			for (int i = 0; i < whole_size; i++) {
				file << ask_modulation[i] << std::endl;
			}
		}
		else {
			std::cout << "Could not write to the file " << std::endl;
		}
		file.close();

		//fsk
		filename = x + fsk + whl;
		file.open(filename);
		if (file.good()) {
			for (int i = 0; i < whole_size; i++) {
				file << ((bit_time * i) / probing_frequency) << std::endl;
			}
		}
		else {
			std::cout << "Could not write to the file " << std::endl;
		}
		file.close();

		filename = y + fsk + whl;
		file.open(filename);
		if (file.good()) {
			for (int i = 0; i < whole_size; i++) {
				file << fsk_modulation[i] << std::endl;
			}
		}
		else {
			std::cout << "Could not write to the file " << std::endl;
		}
		file.close();

		//psk
		filename = x + psk + whl;
		file.open(filename);
		if (file.good()) {
			for (int i = 0; i < whole_size; i++) {
				file << ((bit_time * i) / probing_frequency) << std::endl;
			}
		}
		else {
			std::cout << "Could not write to the file " << std::endl;
		}
		file.close();

		filename = y + psk + whl;
		file.open(filename);
		if (file.good()) {
			for (int i = 0; i < whole_size; i++) {
				file << psk_modulation[i] << std::endl;
			}
		}
		else {
			std::cout << "Could not write to the file " << std::endl;
		}
		file.close();




		//SPECTRUMS

		//ask spectrum
		filename = x + ask + spec;
		file.open(filename);
		if (file.good()) {
			for (int i = 0; i < whole_size; i++) {
				file << stripe_frequency[i] << std::endl;
			}
		}
		else {
			std::cout << "Could not write to the file " << std::endl;
		}
		file.close();

		filename = y + ask + spec;
		file.open(filename);
		if (file.good()) {
			for (int i = 0; i < whole_size; i++) {
				file << ask_spectrum[i] << std::endl;
			}
		}
		else {
			std::cout << "Could not write to the file " << std::endl;
		}
		file.close();

		//fsk spectrum
		filename = x + fsk + spec;
		file.open(filename);
		if (file.good()) {
			for (int i = 0; i < whole_size; i++) {
				file << stripe_frequency[i] << std::endl;
			}
		}
		else {
			std::cout << "Could not write to the file " << std::endl;
		}
		file.close();

		filename = y + fsk + spec;
		file.open(filename);
		if (file.good()) {
			for (int i = 0; i < whole_size; i++) {
				file << fsk_spectrum[i] << std::endl;
			}
		}
		else {
			std::cout << "Could not write to the file " << std::endl;
		}
		file.close();

		//psk spectrum 
		filename = x + psk + spec;
		file.open(filename);
		if (file.good()) {
			for (int i = 0; i < whole_size; i++) {
				file << stripe_frequency[i] << std::endl;
			}
		}
		else {
			std::cout << "Could not write to the file " << std::endl;
		}
		file.close();

		filename = y + psk + spec;
		file.open(filename);
		if (file.good()) {
			for (int i = 0; i < whole_size; i++) {
				file << psk_spectrum[i] << std::endl;
			}
		}
		else {
			std::cout << "Could not write to the file " << std::endl;
		}
		file.close();
	}

};
int main()
{
	Signal* test = new Signal("ABCDEFGHIJKLMNOPRSTUVWXYZ", true, 1.0, 1, 1 * M_PI, 2, 10, 100);
	//Szerokosc pasma sygnalu za(t) wynosi: 0Hz
	//Szerokosc pasma sygnalu za(t) wynosi: 0Hz
	//Szerokosc pasma sygnalu za(t) wynosi: 0.75Hz
	test->saveToFiles();
	return 0;
}