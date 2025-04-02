#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

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

int main() {
    double x0;
    int iterations;

  
    cout << "Podaj punkt startowy x0: ";
    cin >> x0;
    cout << "Podaj liczbę iteracji: ";
    cin >> iterations;
    statyczne(x0, iterations, example, poch_example);

    double x1 = x0 - 0.1;
    sieczna(x1, x0, iterations, example);

    return 0;

//falszywej lini i dysercji
}