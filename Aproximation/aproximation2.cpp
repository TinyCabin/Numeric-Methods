#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

//---------------------------------------

double factorial(int n)
{
    double result = 1.0;
    if (n < 0)
        return -1;
    if (n == 0 || n == 1)
        return result;
    for (int i = 2; i <= n; i++) {
        result *= i;
    }
    return result;
}

double dwumianNetwona(int n, int k)
{
    if (n < k || k < 0)
        return -1;
    return (factorial(n) / (factorial(k) * factorial(n - k)));
}

double wielomianCzynnikowy(double x, int n)
{
    double result = 1.0;
    if (n == 0)
        return result;
    for (int i = 0; i < n; i++) {
        result *= (x - i);
    }
    return result;
}

double wielomianGramma(int k, int n, double q)
{
    if (q == 0)
        return 1.0;
    double result = 0.0;
    for (int s = 0; s <= k; s++) {
        result += pow(-1, s) * dwumianNetwona(k, s) * dwumianNetwona(k + s, s) * (wielomianCzynnikowy(q, s) / wielomianCzynnikowy(n, s));
    }
    return result;
}

double oblicz_sk(int k, int n) {
    double sk = 0.0;
    for (int i = 0; i <= n; i++) {
        sk += pow(wielomianGramma(k, n, i), 2);
    }
    return sk;
}

double oblicz_ck(int k, int n, vector<double>& y) {
    double ck = 0.0;
    for (int i = 0; i <= n; i++) {
        ck += y[i] * wielomianGramma(k, n, i);
    }
    return ck;
}

double aproksymacja(int m, int n, double wybrany, vector<double>& x, double h, vector<double>& y) {
    double q = (wybrany - x[0]) / h;
    double ym = 0.0;
    for (int k = 0; k <= m; k++) {
        double sk = oblicz_sk(k, n);
        double ck = oblicz_ck(k, n, y);
        ym += (ck / sk) * wielomianGramma(k, n, q);
    }
    return ym;
}

int main() {
    int degree = 2;
    double h = 1.0;
    vector<double> x = { 1, 2, 3, 4, 5, 6, 7, 8 };
    vector<double> y = { 2, 4, 3, 5, 6, 9, 11, 11 };
    int numPoints = x.size() - 1;

    for (int i = 0; i <= degree; i++) {
        
        cout << "Ck = " << oblicz_ck(i, numPoints, y) << endl;
        cout << "Sk = " << oblicz_sk(i, numPoints) << endl;
        cout << endl;
    }

    cout << "Liczba wezlow: " << numPoints + 1 << endl;

    cout << "Wezly aproksymacji i wartosci w wezlach aproksymacji: " << endl;
    for (int i = 0; i <= numPoints; i++) {
        cout << "x[" << i << "] = " << x[i] << " y[" << i << "] = " << y[i] << endl;
    }

    cout << "Wartosci aproksymowane: " << endl;
    for (int i = 0; i <= numPoints; i++) {
        double y_approx = aproksymacja(degree, numPoints, x[i], x, h, y);
        cout << "y aproksymowane[" << i << "] = " << y_approx << endl;
    }

    double wybrany;
    cout << "W jakim punkcie zaproksymowac?" << endl;
    cin >> wybrany;
    cout << "Aproksymacja w punkcie: " << wybrany << " wynosi: " << aproksymacja(degree, numPoints, wybrany, x, h, y) << endl;

    double x1 = 2.5;
    double x2 = 6.5;
    double approx_x1 = aproksymacja(degree, numPoints, x1, x, h, y);
    double approx_x2 = aproksymacja(degree, numPoints, x2, x, h, y);

    cout << "Aproksymacja w punkcie x = 2.5 wynosi " << approx_x1 << endl;
    cout << "Aproksymacja w punkcie x = 6.5 wynosi " << approx_x2 << endl;

    return 0;
}
