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
	double amplitude;
	double frequency;
	double const_shift;
	double probing_amount;
	double probing_frequency;
	double* function_values;
	Complex* dft_values;
	double* amplitude_spectrum;
	double* stripe_frequency;

	Signal(double ABC, double B, double C, double amplitude, double probing_frequency) {
		this->probing_amount = ABC;
		this->frequency = B;
		this->const_shift = C * M_PI;
		this->amplitude = amplitude;
		this->probing_frequency = probing_frequency;
		this->function_values = new double[probing_amount];
		this->dft_values = new Complex(probing_amount);
		this->amplitude_spectrum = new double[probing_amount];
		this->stripe_frequency = new double[probing_amount];
	}

	void generateFunction(int select) {
		if (select == 0) {
			for (int i = 0; i < probing_amount; i++) {
				function_values[i] = sFunc((1.0 / probing_frequency) * i);
			}
		}
		else if (select == 1) {
			for (int i = 0; i < probing_amount; i++) {
				function_values[i] = xFunc((1.0 / probing_frequency) * i);
			}
		}
		else if (select == 2) {
			for (int i = 0; i < probing_amount; i++) {
				function_values[i] = yFunc((1.0 / probing_frequency) * i);
			}
		}
		else if (select == 3) {
			for (int i = 0; i < probing_amount; i++) {
				function_values[i] = zFunc((1.0 / probing_frequency) * i);
			}
		}
		else if (select == 4) {
			for (int i = 0; i < probing_amount; i++) {
				function_values[i] = uFunc((1.0 / probing_frequency) * i);
			}
		}
		else if (select == 5) {
			for (int i = 0; i < probing_amount; i++) {
				{
					if (((1.0 / probing_frequency) * i) < 0.22) {
						function_values[i] = vFuncA((1.0 / probing_frequency) * i);
					}
					if (((1.0 / probing_frequency) * i) >= 0.22 && ((1.0 / probing_frequency) * i) < 0.7) {
						function_values[i] = vFuncB((1.0 / probing_frequency) * i);
					}
					if (((1.0 / probing_frequency) * i) >= 0.7) {
						function_values[i] = vFuncC((1.0 / probing_frequency) * i);
					}
				}
			}
		}
		else if (select == 6) {
			for (int i = 0; i < probing_amount; i++) {
				function_values[i] = pFunc((1.0 / probing_frequency) * i, 2);
			}
		}
		else if (select == 7) {
			for (int i = 0; i < probing_amount; i++) {
				function_values[i] = pFunc((1.0 / probing_frequency) * i, 4);
			}
		}
		else if (select == 8) {
			for (int i = 0; i <= probing_amount; i++) {
				function_values[i] = pFunc((1.0 / probing_frequency) * i, 81);
			}
		}
	}

	double sFunc(double x) {
		return (amplitude * sin(2 * M_PI * frequency * x + const_shift));
	}

	double xFunc(double x) {
		return (8 * pow(x, 2) + 1 * x + 3);
	}

	double yFunc(double x) {
		return (2 * pow(xFunc(x), 2) + 12 * cos(x));
	}

	double zFunc(double x) {
		return  (sin(2 * (M_PI) * 7 * x) * xFunc(x) - 0.2 * log10(abs(yFunc(x)) + M_PI));
	}

	double uFunc(double x) {
		return (sqrt(abs(yFunc(x) * yFunc(x) * zFunc(x)) - 1.8 * sin(0.4 * x * zFunc(x) * xFunc(x))));
	}

	double vFuncA(double x) {
		return ((1 - 7 * x) * sin((2 * (M_PI)*x * 10) / (x + 0.04)));
	}

	double vFuncB(double x) {
		return (0.63 * x * sin(125 * x));
	}

	double vFuncC(double x) {
		return (pow(x, -0.662) + 0.77 * sin(8 * x));
	}

	double pFunc(double x, int N) {
		double result = 0;
		for (int i = 1; i <= N; i++) {
			result += ((cos(12 * x * pow(i, 2)) + cos(16 * x * i)) / (pow(i, 2)));
		}
		return result;
	}

	void DFT() {
		for (int k = 0; k < probing_amount; k++) {
			double real_temp_sum = 0;
			double imag_temp_sum = 0;
			for (int n = 0; n < probing_amount; n++) {
				real_temp_sum += function_values[n] * cos(-2 * M_PI * n * k / (probing_amount));
				imag_temp_sum += function_values[n] * sin(-2 * M_PI * n * k / (probing_amount));
			}
			dft_values->real_value[k] = real_temp_sum;
			dft_values->imag_value[k] = imag_temp_sum;
		}
	}

	void IDFT() {
		for (int k = 0; k < probing_amount; k++) {
			double new_func_value = 0;
			for (int n = 0; n < probing_amount; n++) {
				new_func_value += (dft_values->real_value[n] * cos(2 * M_PI * n * k / (probing_amount)) - dft_values->imag_value[n] * sin(2 * M_PI * n * k / (probing_amount))) / probing_amount;
			}
			function_values[k] = new_func_value;
		}
	}

	void setAmpliSpec() {
		for (int k = 0; k < probing_amount; k++) {
			amplitude_spectrum[k] = sqrt(pow(dft_values->real_value[k], 2) + pow(dft_values->imag_value[k], 2));
			stripe_frequency[k] = (k * probing_frequency) / (probing_amount);
		}
	}

	void logFunc() {
		for (int k = 0; k < probing_amount; k++) {
			if (amplitude_spectrum[k] != 0)amplitude_spectrum[k] = 10 * log10(amplitude_spectrum[k]);
		}
	}

	void saveToFiles(int select) {
		ofstream file;
		generateFunction(select);
		DFT();
		setAmpliSpec();
		if (select == 5) {
			string number = to_string(select);
			string x1 = "X1_";
			string y1 = "Y1_";
			string x2 = "X2_";
			string y2 = "Y2_";
			string x3 = "X3_";
			string y3 = "Y3_";
			string x = "X_";
			string y = "Y_";
			string file1 = "_1.txt";
			string file2 = "_2.txt";
			string file3 = "_3.txt";
			int j = 0;

			string filename = y1 + number + file1;
			file.open(filename);
			if (file.good()) {
				while ((1.0 / probing_frequency) * j < 0.22) {
					file << function_values[j] << endl;
					j++;
				}
			}
			file.close();

			filename = y2 + number + file1;
			file.open(filename);
			if (file.good()) {
				while ((1.0 / probing_frequency) * j < 0.7) {
					file << function_values[j] << endl;
					j++;
				}
			}			
			file.close();

			filename = y3 + number + file1;
			file.open(filename);
			if (file.good()) {
				while (j < probing_amount) {
					file << function_values[j] << endl;
					j++;
				}
			}
			file.close();

			j = 0;
			filename = x1 + number + file1;
			file.open(filename);
			if (file.good()) {
				while ((1.0 / probing_frequency) * j < 0.22) {
					file << (1.0 / probing_frequency) * j << endl;
					j++;
				}
			}
			file.close();

			filename = x2 + number + file1;
			file.open(filename);
			if (file.good()) {
				while ((1.0 / probing_frequency) * j < 0.7) {
					file << (1.0 / probing_frequency) * j << endl;
					j++;
				}
			}
			file.close();

			filename = x3 + number + file1;
			file.open(filename);
			if (file.good()) {
				while (j < probing_amount) {
					file << (1.0 / probing_frequency) * j << endl;
					j++;
				}
			}
			file.close();

			filename = x + number + file2;
			file.open(filename);
			if (file.good()) {
				for (int i = 0; i < probing_amount; i++) {
					file << stripe_frequency[i] << endl;
				}
			}
			file.close();

			filename = y + number + file2;
			file.open(filename);
			if (file.good()) {
				for (int i = 0; i < probing_amount; i++) {
					file << amplitude_spectrum[i] << endl;
				}
			}
			file.close();

			logFunc();
			filename = x + number + file3;
			file.open(filename);
			if (file.good()) {
				for (int i = 0; i < probing_amount; i++) {
					file << stripe_frequency[i] << endl;
				}
			}
			file.close();

			filename = y + number + file3;
			file.open(filename);
			if (file.good()) {
				for (int i = 0; i < probing_amount; i++) {
					file << amplitude_spectrum[i] << endl;
				}
			}
			file.close();
		}
		else {
			string number = to_string(select);
			string x = "X_";
			string y = "Y_";
			string file1 = "_1.txt";
			string file2 = "_2.txt";
			string file3 = "_3.txt";
			string file4 = "_4.txt";
			string filename = x + number + file1;

			file.open(filename);
			if (file.good()) {
				for (int i = 0; i < probing_amount; i++) {
					file << (1.0 / probing_frequency) * i << endl;
				}
			}			
			file.close();

			filename = y + number + file1;
			file.open(filename);
			if (file.good()) {
				for (int i = 0; i < probing_amount; i++) {
					file << function_values[i] << endl;
				}
			}
			file.close();

			filename = x + number + file2;
			file.open(filename);
			if (file.good()) {
				for (int i = 0; i < probing_amount; i++) {
					file << stripe_frequency[i] << endl;
				}
			}
			file.close();

			filename = y + number + file2;
			file.open(filename);
			if (file.good()) {
				for (int i = 0; i < probing_amount; i++) {
					file << amplitude_spectrum[i] << endl;
				}
			}
			file.close();

			logFunc();
			filename = x + number + file3;
			file.open(filename);
			if (file.good()) {
				for (int i = 0; i < probing_amount; i++) {
					file << stripe_frequency[i] << endl;
				}
			}
			file.close();

			filename = y + number + file3;
			file.open(filename);
			if (file.good()) {
				for (int i = 0; i < probing_amount; i++) {
					file << amplitude_spectrum[i] << endl;
				}
			}
			file.close();

			IDFT();
			filename = x + number + file4;
			file.open(filename);
			if (file.good()) {
				for (int i = 0; i < probing_amount; i++) {
					file << (1.0 / probing_frequency) * i << endl;
				}
			}
			file.close();

			filename = y + number + file4;
			file.open(filename);
			if (file.good()) {
				for (int i = 0; i < probing_amount; i++) {
					file << function_values[i] << endl;
				}
			}
			file.close();
		}
	}
};
int main()
{
	Signal* test = new Signal(353, 3, 5, 1, 271);
	test->saveToFiles(0);
	test->saveToFiles(1);
	test->saveToFiles(2);
	test->saveToFiles(3);
	test->saveToFiles(5);
	test->saveToFiles(4);
	test->saveToFiles(6);
	test->saveToFiles(7);
	test->saveToFiles(8);


	return 0;
}