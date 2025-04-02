#include <iostream>
#include <cmath>

using namespace std;

inline double sin_function(double x) { return sin(x); }
inline double wielomian(double x) { return pow(x, 2) + (2 * x) + 5; }
inline double exp_function(double x) { return exp(x); }

double calka_prostokat(double a, double b, int n, double (*function)(double))
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

double calka_trapez(double a, double b, int n, double (*function)(double))
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

double calka_simpsona(double a, double b, int n, double (*function)(double))
{
    double s = (b - a) / n;
    double sum = 0.0;
    double x1 = 0.0;
    double x2 = 0.0;
    for (int i = 0; i < n; i++) {
        double tmp = (int)i;
        x1 = a + i * s;
        x2 = a + (tmp + 1) * s;
        sum += ((x2 - x1) / 6.0) * (function(x1) + 4 * function((x1 + x2) / 2.0) + function(x2));
    }
    return sum;
}

double kwadratura_gaussa_lagrange(double a, double b, int n/*n = liczba wezlow*/, double (*function)(double))
{
    double s = (b - a) / 2.0;
    double t1, t2, x1, x2, a1, a2;
    double sum = 0.0;
    switch (n)
    {
    case 2:
        x1 = -(pow(3, 1.0 / 2.0) / 3.0);
        x2 = (pow(3, 1.0 / 2.0) / 3.0);

        t1 = ((a + b) / 2.0) + (s * x1);
        t2 = ((a + b) / 2.0) + (s * x2);
        sum += function(t1);
        sum += function(t2);
        //cout<< "x1 = " << x1 << endl;
        //cout<< "x2 = " << x2 << endl;
        //cout << "t1 = " << t1 << endl;
        //cout << "t2 = " << t2 << endl;
        break;
    case 3:
        a1 = 5.0 / 9.0;
        a2 = 8.0 / 9.0;
        x1 = -pow(3.0 / 5.0, 1.0 / 2.0);
        x2 = pow(3.0 / 5.0, 1.0 / 2.0);
        //cout<< "x1 = " << x1 << endl;
        //cout<< "x2 = " << x2 << endl;
        t1 = ((a + b) / 2.0) + (s * x1);
        sum += function(t1) * a1;
        t2 = ((a + b) / 2.0);
        sum += function(t2) * a2;
        t1 = ((a + b) / 2.0) + (s * x2);
        sum += function(t1) * a1;
        //cout << "t1 = " << t1 << endl;
        //cout << "t2 = " << t2 << endl;
        break;
    case 4:
        a1 = 1.0 / 36.0 * (18.0 - pow(30, 1.0 / 2.0));
        a2 = 1.0 / 36.0 * (18.0 + pow(30, 1.0 / 2.0));
        x1 = 1.0 / 35.0 * pow(525 + (70 * pow(30, 1.0 / 2.0)), 1.0 / 2.0);
        x2 = 1.0 / 35.0 * pow(525 - (70 * pow(30, 1.0 / 2.0)), 1.0 / 2.0);
        // i = 1
        t1 = ((a + b) / 2.0) + (s * -x1);
        sum += function(t1) * a1;
        // i =2
        t2 = ((a + b) / 2.0) + (s * -x2);
        sum += function(t2) * a2;
        // i = 3
        t1 = ((a + b) / 2.0) + (s * x2);
        sum += function(t1) * a2;
        //i = 4
        t1 = ((a + b) / 2.0) + (s * x1);
        sum += function(t1) * a1;
        break;
    default:
        cout << "Wybierz liczbe naturalna z przedzialu <2 , 4>" << endl;
        break;
    }
    return s * sum;

}

int main()
{
    double a = 0.5;
    double b = 2.5;
    int n = 4;

    if (n > 4 || n < 2) {
        kwadratura_gaussa_lagrange(a, b, n, sin_function);
        goto there;
    }

    cout << endl;
    cout << "Funkcja sin(x)" << endl;
    cout << "Przedzial: (" << a << " , " << b << ")" << endl;
    for (int i = 2; i < n + 1; i++) {
        cout << "Wynik dla kwadratury Gaussa-Lagrange'a " << i << " wezloweg wynosi: " << kwadratura_gaussa_lagrange(a, b, i, sin_function) << endl;
    }
    cout << endl;

    a = 0.5;
    b = 5.0;
    cout << "Funkcja x^2 +2x + 5(x)" << endl;
    cout << "Przedzial: (" << a << " , " << b << ")" << endl;
    for (int i = 2; i < n + 1; i++) {
        cout << "Wynik dla kwadratury Gaussa-Lagrange'a " << i << " wezloweg wynosi: " << kwadratura_gaussa_lagrange(a, b, i, wielomian) << endl;
    }
    cout << endl;

    a = 0.5;
    b = 5.0;

    cout << "Funkcja exp(x)" << endl;
    cout << "Przedzial: (" << a << " , " << b << ")" << endl;
    for (int i = 2; i < n + 1; i++) {
        cout << "Wynik dla kwadratury Gaussa-Lagrange'a " << i << " wezloweg wynosi: " << kwadratura_gaussa_lagrange(a, b, i, exp_function) << endl;
    }
    cout << endl;
there:
    a = 0.5;
    b = 2.5;
    n = 20;
    cout << "Funkcja sin(x)" << endl;
    cout << "Przedzial: (" << a << " , " << b << ")" << endl;
    cout << "Wynik dla calka_prostokat dla n = " << n << " wynosi: " << calka_prostokat(a, b, n, sin_function) << endl;
    cout << "Wynik dla calka_trapez dla n = " << n << " wynosi: " << calka_trapez(a, b, n, sin_function) << endl;
    cout << "Wynik dla calka_simsona dla n = " << n << " wynosi: " << calka_simpsona(a, b, n, sin_function) << endl;
    cout << endl;

    a = 0.5;
    b = 5.0;
    cout << "Funkcja x^2 +2x + 5(x)" << endl;
    cout << "Przedzial: (" << a << " , " << b << ")" << endl;
    cout << "Wynik dla calka_prostokat dla n = " << n << " wynosi: " << calka_prostokat(a, b, n, wielomian) << endl;
    cout << "Wynik dla calka_trapez dla n = " << n << " wynosi: " << calka_trapez(a, b, n, wielomian) << endl;
    cout << "Wynik dla calka_simsona dla n = " << n << " wynosi: " << calka_simpsona(a, b, n, wielomian) << endl;
    cout << endl;

    a = 0.5;
    b = 5.0;

    cout << "Funkcja exp(x)" << endl;
    cout << "Przedzial: (" << a << " , " << b << ")" << endl;
    cout << "Wynik dla calka_prostokat dla n = " << n << " wynosi: " << calka_prostokat(a, b, n, exp_function) << endl;
    cout << "Wynik dla calka_trapez dla n = " << n << " wynosi: " << calka_trapez(a, b, n, exp_function) << endl;
    cout << "Wynik dla calka_simsona dla n = " << n << " wynosi: " << calka_simpsona(a, b, n, exp_function) << endl;
    cout << endl;



}