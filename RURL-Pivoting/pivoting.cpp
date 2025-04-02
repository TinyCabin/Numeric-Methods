#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>

using namespace std;


class Matrix {
private:
    int rozmiar;
    double** M;

public:
    Matrix(string filename) {
        ifstream czytaj;
        czytaj.open(filename);
        if (!czytaj) {
            cout << "Nie mozna odtworzyc pliku: " << filename << endl;
            exit(EXIT_FAILURE);
        }

        czytaj >> rozmiar;

        M = new double* [rozmiar];
        for (int i = 0; i < rozmiar; i++)
            M[i] = new double[rozmiar + 1];

        for (int i = 0; i < rozmiar; i++)
            for (int j = 0; j < rozmiar + 1; j++)
                czytaj >> M[i][j];

        czytaj.close();
    }

    ~Matrix() {
        for (int i = 0; i < rozmiar; i++) {
            delete[] M[i];
        }
        delete[] M;
    }

    void showMatrix() {
        for (int i = 0; i < rozmiar; i++) {
            cout << endl;
            for (int j = 0; j < rozmiar + 1; j++) {
                //printf("%5.1lf", M[i][j]);
                cout << "  " << setw(5) << M[i][j] << setprecision(3) << "  ";
                //cout << "  " << setw(3) << M[i][j] << "  ";
            }
        }
        cout << endl;
    }

    double getRozmiar() {
        return rozmiar;
    }

    double getElement(int i, int j) {
        return M[i][j];
    }

    void Gauss()
    {
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
            //showMatrix();
        }
        cout << endl;

        double* wynik = new double[rozmiar];
        int komorka = rozmiar - 1;

        for (int i = 0; i < rozmiar; i++) {
            wynik[i] = M[i][rozmiar];
        }

        wynik[komorka] = M[komorka][rozmiar] / M[komorka][komorka];


        double  suma;
        for (int i = komorka; i >= 0; i--) {
            suma = 0;
            for (int j = i + 1; j <= komorka; j++) {
                suma += M[i][j] * wynik[j];
            }
            wynik[i] = (M[i][rozmiar] - suma) / M[i][i];
        }


        cout << "Wyniki to:" << endl;
        for (int i = 0; i < rozmiar; i++) {
            cout << "x" << i << ":  " << wynik[i] << endl;
        }
        cout << endl;
        delete[] wynik;
    }
    // PIVOITNG
    void BetterGaussI()
    {
        prep_Lines();
        Gauss();
    }

    void swap_Lines(int line1, int line2) {
        double* temp = new double[rozmiar + 1];
        for (int i = 0; i < rozmiar + 1; i++) {
            temp[i] = M[line1][i];
            M[line1][i] = M[line2][i];
            M[line2][i] = temp[i];
        }
        delete[] temp;

    }

    pair<double, int> find_highest_in_column(int line, int column)
    {
        double highest = M[line][column];
        for (int i = line; i < rozmiar; i++) {
            if (abs(highest) < abs(M[i][column])) {
                highest = M[i][column];
                line = i;
            }
        }
        return make_pair(highest, line);
    }

    void prep_Lines() {
        for (int i = 0; i < rozmiar - 1; i++) {
            auto result = find_highest_in_column(i, i);
            double highest = result.first;
            int line = result.second;
            if (M[i][i] != highest)
                swap_Lines(i, line);
        }
    }
    //Powyzej do PIVOTING'u

    // DO Gaussa-Croutasa
    pair<double, int> find_highest_in_line(int line, int column)
    {
        double highest = M[line][column];
        for (int i = column; i < rozmiar; i++) {
            if (abs(highest) < abs(M[line][i])) {
                highest = M[line][i];
                column = i;
            }
        }
        //cout << "naj: " << highest << endl;
        //cout << "column: " << column << endl << endl;
        return make_pair(highest, column);
    }

    void GaussCrout()
    {
        for (int i = 0; i < rozmiar; i++) {
            double maxval = 0;
            for (int j = 0; j < rozmiar; j++) {
                if (abs(M[i][j]) > maxval) {
                    maxval = abs(M[i][j]);
                }
            }
            for (int j = 0; j < rozmiar + 1; j++) {
                M[i][j] /= maxval;
            }
        }
        showMatrix();

        int* wektor = new int[rozmiar];
        for (int i = 0; i < rozmiar; i++) {
            wektor[i] = i;
            //cout << "komorka[" << i << "] =  " << wektor[i] << endl;
        }

        for (int i = 0; i < rozmiar; i++) {
            auto result = find_highest_in_line(i, i);
            double highest = result.first;
            int column = result.second;

            if (M[i][i] != highest) {
                int temp = wektor[i];
                wektor[i] = wektor[column];
                wektor[column] = temp;
                //cout << "komorka[" << i << "] =  " << wektor[i] << endl;
                //cout << "komorka[" << column << "] =  " << wektor[column] << endl << endl;
            }
        }
        cout << endl << "Tablica przesuniec po zmianach: " << endl;
        for (int i = 0; i < rozmiar; i++) {
            cout << "komorka[" << i << "] =  " << wektor[i] << endl;
        }
        cout << endl;

        //Gauss modified
        double mnoznik;
        for (int i = 0; i < rozmiar - 1; i++) {
            for (int j = i + 1; j < rozmiar; j++) {
                if (M[i][wektor[i]] == 0) {
                    break;
                }
                mnoznik = M[j][wektor[i]] / M[i][wektor[i]];
                for (int k = 0; k < rozmiar + 1; k++) {
                    M[j][k] = M[j][k] - M[i][k] * mnoznik;
                }
            }
            //showMatrix();
        }

        double* wynik = new double[rozmiar];
        int komorka = rozmiar - 1;

        for (int i = 0; i < rozmiar; i++) {
            wynik[i] = M[i][rozmiar];
        }

        wynik[komorka] = M[komorka][rozmiar] / M[komorka][komorka];

        double suma;
        for (int i = komorka; i >= 0; i--) {
            suma = 0;
            for (int j = i + 1; j <= komorka; j++) {
                suma += M[i][wektor[j]] * wynik[j];
            }
            wynik[i] = (M[i][rozmiar] - suma) / M[i][wektor[i]];
        }

        cout << "Wyniki to:" << endl;
        for (int i = 0; i < rozmiar; i++) {
            cout << "x" << wektor[i] << ":  " << wynik[i] << endl;
        }

        delete[] wektor;
        delete[] wynik;
    }

};


int main()
{
    Matrix ukladrownan("RURL_dane3.txt");
    ukladrownan.showMatrix();
    ukladrownan.BetterGaussI();
    ukladrownan.showMatrix();

    //cout << endl;

    Matrix ukladrownan2("RURL_dane2.txt");
    ukladrownan2.showMatrix();

    ukladrownan2.GaussCrout();
    ukladrownan2.showMatrix();

    return 0;
}