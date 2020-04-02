#define _USE_MATH_DEFINES
#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>

using namespace std;

double a = 3;
double b = 5;
double c = 3;

double quad(double input)
{
    return (a * (input * input)) + (b * input) + c;
}

double y(double i)
{
    return 2 * pow(quad(i), 2) + 12 * cos(i);
}

double z(double i)
{
    return sin(14 * M_PI * i) * quad(i) - (0.2 * log10(abs(y(i)))+M_PI);
}

double u(double i)
{
    return sqrt(abs(y(i) * y(i) * z(i))) - (1.8 * sin(0.4 * i * z(i) * quad(i)));
}

double v(double i)
{
    double result;
    if (i < 0.22)
    {
        return (1 - (7 * i)) * (sin((20*M_PI*i)/(i+0.04)));
    }
    else if (i < 0.7)
    {
        return 0.63 * i * sin(125 * i);
    }
    else
    {
        return pow(i, -0.662) + (0.77 * sin(8 * i));
    }
}
double p(double i)
{
    double t[3] = {2,4,35};
    double result=0;
    for (int j = 0; j < 3; j++)
    {
        result += (cos(12 * i * pow(t[j], 2))+cos(16*i*t[j]))/pow(t[j],2);
    }
    return result;
}

double zeros(double a, double b, double delta,int flag)
{
    if (flag == 0)
    {
        return ((-1 * b) + sqrt(delta)) / (2 * a);
    }
    else if(flag==1)
    {
        return ((-1 * b) - sqrt(delta)) / (2 * a);
    }
   
}

int main()
{
    double delta = (b * b) + (4 * a * c);
    vector<double> results;
    double zero[2];
    for (int i = 0;i < 2; i++)
    {
        zero[i] = zeros(a, b, delta, i);
    }
    for (double i = -10; i <= 10; i += 0.01)
    {
        results.push_back(quad(i));
    }
    fstream file;
    file.open("output.txt",ios::out);
    for (int i = 0; i < results.size(); i++)
    {
        file << results[i];
        file << " ";
    }
    file.close();
    cout << "Done\n";
    double step = (double)1 / (double)22050;
    file.open("2_1.txt",ios::out);
    for (double i = 0; i <= 1 ;i += step)
    {
        double result = y(i);
        file << result;
        file << " ";
    }
    file.close();
    cout << "Done\n";
    file.open("2_2.txt",ios::out);
    for (double i = 0; i <= 1; i += step)
    {
        double result = z(i);
        file << result;
        file << " ";
    }
    file.close();
    cout << "Done\n";
    file.open("2_3.txt",ios::out);
    for (double i = 0; i <= 1; i += step)
    {
        double result = u(i);
        file << result;
        file << " ";
    }
    file.close();
    cout << "Done\n";
    file.open("2_4.txt",ios::out);
    for (double i = 0; i <= 1; i += step)
    {
        double result = v(i);
        file << result;
        file << " ";
    }
    file.close();
    cout << "Done\n";
    file.open("2_5.txt",ios::out);
    for (double i = 0; i <= 1; i += step)
    {
        double result = p(i);
        file << result;
        file << " ";
    }
    file.close();
}