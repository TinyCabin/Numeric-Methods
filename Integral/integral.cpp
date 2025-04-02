#include <iostream>
#include <cmath>

using namespace std;

double sin_function(double x){return sin(x);}
double wielomian(double x) { return pow(x,2)+(2 *x) +5; }
double exp_function(double x) { return exp(x); }

double calka_prostokat(double a, double b, double n , double (*function)(double))
{
	double s = (b - a) / n;
	double sum = 0.0;
	double x = 0.0;
	for (int i = 0; i < n; i++)
	{
		x = a + i * s;
		sum += function(x + 0.5 * s);
	}
	return s * sum;
}

double calka_trapez(double a, double b, double n, double (*function)(double))
{
	double s = (b - a) / n;
	double sum = 0.0;
	double x1 = 0.0;
	double x2 = 0.0;
	for (int i = 0; i < n; i++)
	{
		double tmp = (int)i;
		x1 = a + i * s;
		x2 = a + (tmp + 1) * s;
		sum += (function(x1) + function(x2)) * (x2 - x1) / 2.0;
	}
	return sum;
}

double calka_simpsona(double a, double b, double n, double (*function)(double))
{
	double s = (b - a) / n;
	double sum = 0.0;
	double x1 = 0.0;
	double x2 = 0.0;
	for (int i = 0; i < n; i++) {
		double tmp = (int)i;
		x1 = a + i * s;
		x2 = a + (tmp+1) * s;
		sum += ((x2 - x1) / 6.0) * (function(x1) + 4 * function((x1 + x2) / 2.0) + function(x2));
	}
	return sum;
}

int main()
{
	double a = 0.5;
	double b = 2.5;
	int n = 4;
	cout << "Funkcja sin(x)" << endl;
	cout << "Wynik dla calka_prostokat dla n = " << n << " wynosi: " << calka_prostokat(a, b, n, sin_function) << endl;
	cout << "Wynik dla calka_trapez dla n = " << n << " wynosi: " << calka_trapez(a, b, n, sin_function) << endl;
	cout << "Wynik dla calka_simsona dla n = " << n << " wynosi: " << calka_simpsona(a, b, n, sin_function) << endl;

	a = 0.5;
	b = 5.0;
	cout << "Funkcja x^2 +2x + 5(x)" << endl;
	cout << "Wynik dla calka_prostokat dla n = " << n << " wynosi: " << calka_prostokat(a, b, n, wielomian) << endl;
	cout << "Wynik dla calka_trapez dla n = " << n << " wynosi: " << calka_trapez(a, b, n, wielomian) << endl;
	cout << "Wynik dla calka_simsona dla n = " << n << " wynosi: " << calka_simpsona(a, b, n, wielomian) << endl;

	a = 0.5;
	b = 5.0;

	cout << "Funkcja exp(x)" << endl;
	cout << "Wynik dla calka_prostokat dla n = " << n << " wynosi: " << calka_prostokat(a, b, n, exp_function) << endl;
	cout << "Wynik dla calka_trapez dla n = " << n << " wynosi: " << calka_trapez(a, b, n, exp_function) << endl;
	cout << "Wynik dla calka_simsona dla n = " << n << " wynosi: " << calka_simpsona(a, b, n, exp_function) << endl;

	//for (int i = 1; i < 11; i++) {
	//	//cout << "Wynik dla calka_prostokat dla n = " << i << " wynosi: " << calka_prostokat(a, b, i, exp_function) << endl;
	//	//cout << "Wynik dla calka_trapez dla n = " << i << " wynosi: " << calka_trapez(a, b, i, exp_function) << endl;//
	//	//cout << "Wynik dla calka_simsona dla n = " << i << " wynosi: " << calka_simpsona(a, b, i, exp_function) << endl;
	//}

}