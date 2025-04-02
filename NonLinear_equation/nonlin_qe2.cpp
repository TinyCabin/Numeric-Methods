#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>

using namespace std;

double cos_fun(double x) { return cos((x * x * x) - (2 * x)); }

double fun(double x) {return -x * x * x + 10 * x + 5;}

double poch_fun(double x) { return -3 * x * x + 10; }

double example(double x) { return x * x + 5*x + 1; }

double poch_example(double x) { return 2*x + 5; }

void statyczne(double x0, int iterations, double(*fun)(double),double(*prime_fun)(double)) {
    double x = x0;
    cout << "Metoda stycznych" <<endl;
    cout << "Iteracja\t x\t\t f(x)" << endl;
    for (int i = 0; i < iterations; i++) {
        cout << i + 1 << "\t\t  " << x << "\t" << fun(x) << endl;
        x = x - fun(x) / prime_fun(x);
    }
    cout << "Znalezione przyblizenie: x = " << x << endl;
}

void sieczna(double x0, double x1, int iterations, double(*fun)(double)) {
    double xk_1 = x0;
    double xk = x1;
    cout << "Metoda sieczna" << endl;
    cout << "Iteracja\t x\t\t f(x)" << endl;
    for (int i = 0; i < iterations; i++) {
        cout << i + 1 << "\t\t" << xk << "\t" << fun(xk) << endl;
        double xk1 = xk - fun(xk) * (xk - xk_1) / (fun(xk) - fun(xk_1));
        xk_1 = xk;
        xk = xk1;
    }
    cout << "Znalezione przyblizenie: x = " << xk << endl;
}

double bisekcji(double a, double b, double eps, double(*cos_fun)(double)) {
    double x0 = (a + b) / 2;
    if (cos_fun(x0) == 0.0)
        return x0;
    while (abs(cos_fun(x0)) >= eps) {
        cout << "a: " << a << " b: " << b << " f(a): " << cos_fun(a) << " f(b): " << cos_fun(b) << " x0: " << x0 << " f(x0): " << cos_fun(x0) << " f(a)*f(x0): " << cos_fun(a) * cos_fun(b) <<endl;
        if (cos_fun(x0) == 0.0)
            break;
        else if (cos_fun(a) * cos_fun(x0) < 0)
            b = x0;
        else if (cos_fun(x0) * cos_fun(b)< 0)
            a = x0;
        else {
            cout << "Nie znaleziono miejsca 0" << endl;
            return x0;
        }

        x0 = (a + b) / 2;
    }
    return x0;
}

double false_line(double a, double b, double epsilon, double(*funkcja)(double)) {
    while (true) {
        double x1 = a - ((funkcja(a) * (b - a)) / (funkcja(b) - funkcja(a)));
        cout << "x1: " << x1 << ", f(x1): " << funkcja(x1) << endl;
        double fun = abs(funkcja(x1));
        if (fun < epsilon) {
            return x1;
        }
        if ((funkcja(x1) * funkcja(a)) < 0) {
            b = x1;
        }
        else {
            a = x1;
        }
    }

}
int main() {
    double a;
    double b;
    double eps;

    double x0;
    int iterations;

  
    cout << "Podaj punkt startowy a: ";
    cin >> a;
    cout << "Podaj punkt startowy b: ";
    cin >> b;
    cout << "Podaj liczbę epsilon: ";
    cin >> eps;
    
    cout << "Rozwiazanie rownania f(x) = cos(x^3 - 2x) = 0 metoda bisekcji:\n";
    double wynikBisekcji = bisekcji(a,b,eps,cos_fun);
    cout << "Wynik " << wynikBisekcji << endl;

    cout << "Rozwiazanie rownania f(x) = cos(x^3 - 2x) = 0 metoda falszywej linii:\n";
    double wynikFalseline = false_line(a, b, eps, cos_fun);
    cout << "Wynik " << wynikFalseline << endl;


    return 0;

}