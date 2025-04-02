#include <iostream>
#include <fstream>

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
                cout << "  " << M[i][j] << "  ";
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
                    cout << "0 na przek" << endl;
                    break;
                }
                mnoznik = M[j][i] / M[i][i];
                for (int k = 0; k < rozmiar + 1; k++) {
                    M[j][k] = M[j][k] - M[i][k] * mnoznik;

                }
            }
            showMatrix();
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
            cout << "x" << i <<":  " << wynik[i] << endl;
        }
        cout << endl;
    }

};


int main()
{
    Matrix ukladrownan("RURL_dane1.txt");
    ukladrownan.showMatrix();

    ukladrownan.Gauss();

}