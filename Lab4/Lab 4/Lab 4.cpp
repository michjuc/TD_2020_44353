#include <iostream>
#include <fstream>
#include <cstdlib>
#include <stdio.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <string>
using namespace std;

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
	double fm;
	double fn;
	double end;
	double kp;
	double ka;
	double* function_values;
	double* amplitude_values;
	double* phase_values;
	double pFunc_N;
	string func_name;
	Complex* dft_values_phase;
	double* amplitude_spectrum_phase;
	double* stripe_frequency_phase;
	Complex* dft_values_amplitude;
	double* amplitude_spectrum_amplitude;
	double* stripe_frequency_amplitude;
	Signal(double fm, double fn, double end, double kp, double ka, double pFunc_N, string func_name) {
		this->fm = fm;
		this->fn = fn;
		this->end = end;
		this->kp = kp;
		this->ka = ka;
		this->function_values = new double[end * fm];
		this->amplitude_values = new double[end * fm];
		this->phase_values = new double[end * fm];
		this->func_name = func_name;
		this->pFunc_N = pFunc_N;
		this->dft_values_phase = new Complex(end * fm);
		this->amplitude_spectrum_phase = new double[end * fm];
		this->stripe_frequency_phase = new double[end * fm];
		this->dft_values_amplitude = new Complex(end * fm);
		this->amplitude_spectrum_amplitude = new double[end * fm];
		this->stripe_frequency_amplitude = new double[end * fm];
	}

	double pFunc(double t) {
		double result = 0;
		for (int i = 1; i <= pFunc_N; i++) {
			result += ((cos(12 * t * pow(i, 2)) + cos(16 * t * i)) / (pow(i, 2)));
		}
		return result;
	}

	double zaFunc(double t) {
		return (ka * pFunc(t) + 1) * cos(2 * M_PI * fn * t);
	}

	double zpFunc(double t) {
		return cos(2 * M_PI * fn * t + kp * pFunc(t));
	}

	void generateValues() {
		for (int i = 0; i < end * fm; i++) {
			function_values[i] = pFunc(1.0 / fm * i);
		}
		for (int j = 0; j < end * fm; j++) {
			amplitude_values[j] = zaFunc(1.0 / fm * j);
		}
		for (int k = 0; k < end * fm; k++) {
			phase_values[k] = zpFunc(1.0 / fm * k);
		}
	}
	void DFT_AMPLITUDE() {
		for (int k = 0; k < end * fm; k++) {
			double real_temp_sum = 0;
			double imag_temp_sum = 0;
			for (int n = 0; n < end * fm; n++) {
				real_temp_sum += amplitude_values[n] * cos(-2 * M_PI * n * k / (end * fm));
				imag_temp_sum += amplitude_values[n] * sin(-2 * M_PI * n * k / (end * fm));
			}
			dft_values_amplitude->real_value[k] = real_temp_sum;
			dft_values_amplitude->imag_value[k] = imag_temp_sum;
		}
	}
	void DFT_PHASE() {
		for (int k = 0; k < end * fm; k++) {
			double real_temp_sum = 0;
			double imag_temp_sum = 0;
			for (int n = 0; n < end * fm; n++) {
				real_temp_sum += phase_values[n] * cos(-2 * M_PI * n * k / (end * fm));
				imag_temp_sum += phase_values[n] * sin(-2 * M_PI * n * k / (end * fm));
			}
			dft_values_phase->real_value[k] = real_temp_sum;
			dft_values_phase->imag_value[k] = imag_temp_sum;
		}
	}

	void setAmpliSpec_PHASE() {
		for (int k = 0; k < end * fm; k++) {
			amplitude_spectrum_phase[k] = sqrt(pow(dft_values_phase->real_value[k], 2) + pow(dft_values_phase->imag_value[k], 2));
			stripe_frequency_phase[k] = (k * fm) / (end * fm);
		}
	}

	void setAmpliSpec_AMPLITUDE() {
		for (int k = 0; k < end * fm; k++) {
			amplitude_spectrum_amplitude[k] = sqrt(pow(dft_values_amplitude->real_value[k], 2) + pow(dft_values_amplitude->imag_value[k], 2));
			stripe_frequency_amplitude[k] = (k * fm) / (end * fm);
		}
	}

	void logFunc_PHASE() {
		for (int k = 0; k < end * fm; k++) {
			if (amplitude_spectrum_phase[k] != 0)amplitude_spectrum_phase[k] = 10 * log10(amplitude_spectrum_phase[k]);
		}
	}

	void logFunc_AMPLITUDE() {
		for (int k = 0; k < end * fm; k++) {
			if (amplitude_spectrum_amplitude[k] != 0)amplitude_spectrum_amplitude[k] = 10 * log10(amplitude_spectrum_amplitude[k]);
		}
	}

	void amplitudeBandwidth() {
		int MAX_X = 0;
		for (int i = 1; i < ceil(end * fm) / 2; i++) {
			if (amplitude_spectrum_amplitude[i] > amplitude_spectrum_amplitude[MAX_X])MAX_X = i;
		}
		double fmin = stripe_frequency_amplitude[0];
		double fmax = stripe_frequency_amplitude[MAX_X + 1];
		double difference = abs((amplitude_spectrum_amplitude[MAX_X] - 3) - amplitude_spectrum_amplitude[0]);
		for (int i = 1; i < MAX_X; i++) {
			if (difference > abs((amplitude_spectrum_amplitude[MAX_X] - 3) - amplitude_spectrum_amplitude[i])) {
				difference = abs((amplitude_spectrum_amplitude[MAX_X] - 3) - amplitude_spectrum_amplitude[i]);
				fmin = stripe_frequency_amplitude[i];
			}
		}
		difference = abs((amplitude_spectrum_amplitude[MAX_X] - 3) - amplitude_spectrum_amplitude[MAX_X + 1]);
		for (int i = MAX_X + 2; i < ceil(end * fm) / 2; i++) {
			if (difference > abs((amplitude_spectrum_amplitude[MAX_X] - 3) - amplitude_spectrum_amplitude[i])) {
				difference = abs((amplitude_spectrum_amplitude[MAX_X] - 3) - amplitude_spectrum_amplitude[i]);
				fmax = stripe_frequency_amplitude[i];
			}
		}
	}
	void phaseBandwidth() {
		int MAX_X = 0;
		for (int i = 1; i < ceil(end * fm) / 2; i++) {
			if (amplitude_spectrum_phase[i] > amplitude_spectrum_phase[MAX_X])MAX_X = i;
		}
		double fmin = stripe_frequency_phase[0];
		double fmax = stripe_frequency_phase[MAX_X + 1];
		double difference = abs((amplitude_spectrum_phase[MAX_X] - 3) - amplitude_spectrum_phase[0]);
		for (int i = 1; i < MAX_X; i++) {
			if (difference > abs((amplitude_spectrum_phase[MAX_X] - 3) - amplitude_spectrum_phase[i])) {
				difference = abs((amplitude_spectrum_phase[MAX_X] - 3) - amplitude_spectrum_phase[i]);
				fmin = stripe_frequency_phase[i];
			}
		}
		difference = abs((amplitude_spectrum_phase[MAX_X] - 3) - amplitude_spectrum_phase[MAX_X + 1]);
		for (int i = MAX_X + 2; i < ceil(end * fm) / 2; i++) {
			if (difference > abs((amplitude_spectrum_phase[MAX_X] - 3) - amplitude_spectrum_phase[i])) {
				difference = abs((amplitude_spectrum_phase[MAX_X] - 3) - amplitude_spectrum_phase[i]);
				fmax = stripe_frequency_phase[i];
			}
		}
	}

	void alternativeAmplitudeBandwidth() {
		int MAX_X = 0;
		for (int i = 1; i < ceil(end * fm) / 2; i++) {
			if (amplitude_spectrum_amplitude[i] > amplitude_spectrum_amplitude[MAX_X])MAX_X = i;
		}
		double fmin = stripe_frequency_amplitude[MAX_X];
		double fmax = stripe_frequency_amplitude[MAX_X];

		for (int i = MAX_X + 1; i < ceil(end * fm / 2); i++) {
			if (amplitude_spectrum_amplitude[i] >= amplitude_spectrum_amplitude[MAX_X] - 3) {
				fmax = stripe_frequency_amplitude[i];
			}
		}

		for (int i = MAX_X - 1; i <= 0; i--) {
			if (amplitude_spectrum_amplitude[i] >= amplitude_spectrum_amplitude[MAX_X] - 3) {
				fmin = stripe_frequency_amplitude[i];
			}
		}
	}
	void alternativePhaseBandwidth() {
		int MAX_X = 0;
		for (int i = 1; i < ceil(end * fm) / 2; i++) {
			if (amplitude_spectrum_phase[i] > amplitude_spectrum_phase[MAX_X])MAX_X = i;
		}
		double fmin = stripe_frequency_phase[MAX_X];
		double fmax = stripe_frequency_phase[MAX_X];

		for (int i = MAX_X + 1; i < ceil(end * fm / 2); i++) {
			if (amplitude_spectrum_phase[i] >= amplitude_spectrum_phase[MAX_X] - 3) {
				fmax = stripe_frequency_phase[i];
			}
		}

		for (int i = MAX_X - 1; i <= 0; i--) {
			if (amplitude_spectrum_phase[i] >= amplitude_spectrum_phase[MAX_X] - 3) {
				fmin = stripe_frequency_phase[i];
			}
		}
	}

	void saveToFiles() {
		ofstream file;
		generateValues();
		DFT_PHASE();
		DFT_AMPLITUDE();
		setAmpliSpec_PHASE();
		setAmpliSpec_AMPLITUDE();
		logFunc_PHASE();
		logFunc_AMPLITUDE();
		alternativeAmplitudeBandwidth();
		cout << endl;
		alternativePhaseBandwidth();
		string x = "X_";
		string y = "Y_";
		string file1 = "_1.txt";
		string file2 = "_2.txt";
		string file3 = "_3.txt";
		string file4 = "_4.txt";
		string file5 = "_5.txt";
		string filename = x + func_name + file1;

		file.open(filename);
		if (file.good()) {
			for (int i = 0; i < end * fm; i++) {
				file << (1.0 / fm) * i << endl;
			}
		}
		file.close();

		filename = y + func_name + file1;
		file.open(filename);
		if (file.good()) {
			for (int i = 0; i < end * fm; i++) {
				file << function_values[i] << endl;
			}
		}
		file.close();


		filename = x + func_name + file2;
		file.open(filename);
		if (file.good()) {
			for (int i = 0; i < end * fm; i++) {
				file << (1.0 / fm) * i << endl;
			}
		}
		file.close();

		filename = y + func_name + file2;
		file.open(filename);
		if (file.good()) {
			for (int i = 0; i < end * fm; i++) {
				file << amplitude_values[i] << endl;
			}
		}
		file.close();

		filename = x + func_name + file3;
		file.open(filename);
		if (file.good()) {
			for (int i = 0; i < end * fm; i++) {
				file << (1.0 / fm) * i << endl;
			}
		}
		file.close();

		filename = y + func_name + file3;
		file.open(filename);
		if (file.good()) {
			for (int i = 0; i < end * fm; i++) {
				file << phase_values[i] << endl;
			}
		}
		file.close();

		filename = x + func_name + file4;
		file.open(filename);
		if (file.good()) {
			for (int i = 0; i < end * fm; i++) {
				file << stripe_frequency_phase[i] << endl;
			}
		}
		file.close();

		filename = y + func_name + file4;
		file.open(filename);
		if (file.good()) {
			for (int i = 0; i < end * fm; i++) {
				file << amplitude_spectrum_phase[i] << endl;
			}
		}
		file.close();

		filename = x + func_name + file5;
		file.open(filename);
		if (file.good()) {
			for (int i = 0; i < end * fm; i++) {
				file << stripe_frequency_amplitude[i] << endl;
			}
		}
		file.close();

		filename = y + func_name + file5;
		file.open(filename);
		if (file.good()) {
			for (int i = 0; i < end * fm; i++) {
				file << amplitude_spectrum_amplitude[i] << endl;
			}
		}
		file.close();
	}
};
int main()
{	
	Signal* test = new Signal(10000, 1000, 1, 0.5, 0.5, 2, "FUNC_1");
	test->saveToFiles();
	delete test;

	Signal* test1 = new Signal(10000, 1000, 1, 2, 6, 2, "FUNC_2");
	test1->saveToFiles();
	delete test1;

	Signal* test2 = new Signal(10000, 1000, 1, 25, 100, 2, "FUNC_3");
	test2->saveToFiles();
	delete test2;
	return 0;

}