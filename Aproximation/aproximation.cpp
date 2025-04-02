#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>

using namespace std;

void showMatrix(int rozmiar, const vector<vector<double>>& M) {
    for (int i = 0; i < rozmiar; i++) {
        cout << endl;
        for (int j = 0; j < rozmiar + 1; j++) {
            cout << "  " << setw(5) << M[i][j] << setprecision(3) << "  ";
        }
    }
    cout << endl;
}

void prepData(vector<vector<double>>&g, vector<double>&F, vector<double>&w, vector<double> &x,vector<double> &y , int numPoints, int n)
{
    for (int i = 0; i < numPoints; i++) {
        for (int j = 0; j < n; j++) {
            F[j] += pow(x[i], j) * y[i] * w[i];
            for (int k = 0; k < n; k++) {
                g[j][k] += pow(x[i], k) * pow(x[i], j) * w[i];
            }
        }
    }
}

void Gauss(int rozmiar, vector<vector<double>>& M, vector<double>& x) {
    //showMatrix(rozmiar, M);
    double mnoznik = 0.0;
    for (int i = 0; i < rozmiar - 1; i++) {
        for (int j = i + 1; j < rozmiar; j++) {
            if (M[i][i] == 0) {
                break;
            }
            mnoznik = M[j][i] / M[i][i];
            for (int k = 0; k < rozmiar + 1; k++) {
                M[j][k] = M[j][k] - M[i][k] * mnoznik;
            }
        }
    }
    vector<double> wynik(rozmiar, 0);
    int komorka = rozmiar - 1;

    for (int i = 0; i < rozmiar; i++) {
        wynik[i] = M[i][rozmiar];
    }

    wynik[komorka] = M[komorka][rozmiar] / M[komorka][komorka];

    double suma;
    for (int i = komorka; i >= 0; i--) {
        suma = 0;
        for (int j = i + 1; j <= komorka; j++) {
            suma += M[i][j] * wynik[j];
        }
        wynik[i] = (M[i][rozmiar] - suma) / M[i][i];
    }

    cout << "Wyniki to:" << endl;
    for (int i = 0; i < rozmiar; i++) {
        cout << "x" << i << ":  "  << wynik[i] << endl;

    }
    cout << endl;

    x = wynik;
}

void swap_Lines(int line1, int line2, int n, vector<vector<double>>& M) {
    vector<double> temp(n + 1);
    for (int i = 0; i < n + 1; i++) {
        temp[i] = M[line1][i];
        M[line1][i] = M[line2][i];
        M[line2][i] = temp[i];
    }
}

pair<double, int> find_highest_in_column(int line, int column, int n, vector<vector<double>>& M) {
    double highest = M[line][column];
    int highest_line = line;
    for (int i = line; i < n; i++) {
        if (abs(highest) < abs(M[i][column])) {
            highest = M[i][column];
            highest_line = i;
        }
    }
    return make_pair(highest, highest_line);
}

void prep_Lines(int rozmiar, vector<vector<double>>& M) {
    for (int i = 0; i < rozmiar - 1; i++) {
        auto result = find_highest_in_column(i, i, rozmiar, M);
        double highest = result.first;
        int line = result.second;
        if (i != line) {
            swap_Lines(i, line, rozmiar, M);
        }
    }
}

void BetterGaussI(int rozmiar, vector<vector<double>>& g, vector<double>& F, vector<double>& a) {
    vector<vector<double>> M(rozmiar, vector<double>(rozmiar + 1, 0));
    for (int i = 0; i < rozmiar; i++) {
        for (int j = 0; j < rozmiar; j++) {
            M[i][j] = g[i][j];
        }
        M[i][rozmiar] = F[i];
    }
    prep_Lines(rozmiar, M);
    Gauss(rozmiar, M, a);
}

int main()
{
    int degree = 2;
    int numPoints = 8;
    int n = degree + 1;
    vector<double> x = { 1,2,3,4,5,6,7,8 };
    vector<double> y = { 2,4,3,5,6,9,11,11 };
    vector<double> w(numPoints, 1);

    vector<vector<double>>g(n, vector<double>(n, 0));
    vector<double>F(n, 0);
    vector<double>a(n, 0);


    prepData(g, F, w, x, y, numPoints, n);
    BetterGaussI(n, g, F, a);

    cout << "Liczba wezlow: " << numPoints << endl;
    cout << "Wspolczynniki wielomianu aproksymujacego:" << endl;
    for (int i = 0; i < n; i++) {
        cout << "a[" << i << "] = " << a[i] << endl;
    }

    cout << "Wezly aproksymacji:" << endl;
    for (int i = 0; i < numPoints; i++) {
        cout << "x[" << i << "] = " << x[i] << endl;
    }

    cout << "Wartosci w wezlach aproksymacji:" << endl;
    for (int i = 0; i < numPoints; i++) {
        cout << "y[" << i << "] = " << y[i] << endl;
    }

    cout << "Wartosci aproksymowane: " << endl;
    for (int i = 0; i < numPoints; i++) {
        double y_approx = 0;
        for (int j = 0; j < n; j++) {
            y_approx += a[j] * pow(x[i], j);
        }
        cout << "y aproksymowane[" << i << "] = " << y_approx<< endl;
    }

    return 0;
}