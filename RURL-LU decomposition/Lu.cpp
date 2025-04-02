#include <iostream>
#include <fstream>
#include <iomanip>

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

    void splitMatrix(double**& A, double*& B) {
        A = new double* [rozmiar];
        B = new double[rozmiar];
        for (int i = 0; i < rozmiar; i++) {
            A[i] = new double[rozmiar];
            for (int j = 0; j < rozmiar; j++)
                A[i][j] = M[i][j];
            B[i] = M[i][rozmiar];
        }
    }

    void printMatrix(double** matrix) {
        for (int i = 0; i < rozmiar; i++) {
            for (int j = 0; j < rozmiar; j++)
                cout << "  " << setw(5) << matrix[i][j] << setprecision(3) << "  ";
            cout << endl;
        }
    }

    void printVector(double* vector) {
        for (int i = 0; i < rozmiar; i++) {
            cout << "  " << setw(5) << vector[i] << setprecision(3) << "  ";
        }
        cout << endl;
    }

    void showMatrix() { //Drukuje macierz A|B
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

    void Tab_L_and_U(double**& L, double**& U, double** A)
    {
        double suma = 0;
        for (int i = 0; i < rozmiar; i++) {
            for (int j = 0; j < rozmiar; j++) {
                if (i == j) {
                    L[i][j] = 1;
                }
                if (i <= j)
                {
                    for (int k = 0; k < i; k++) {
                        suma += L[i][k] * U[k][j];
                    }
                    U[i][j] = A[i][j] - suma;
                    suma = 0;
                }
                else if (i > j)
                {
                    for (int k = 0; k < j; k++) {
                        suma += L[i][k] * U[k][j];
                    }
                    L[i][j] = (1 / U[j][j]) * (A[i][j] - suma);
                    suma = 0;
                }
            }
        }
    }

    void tablicaY(double*& Y, double* B, double** L)
    {
        Y[0] = B[0];
        double suma = 0;
        for (int i = 0; i < rozmiar; i++)
        {
            for (int j = 0; j < i; j++) {
                suma += L[i][j] * Y[j];
            }
            Y[i] = B[i] - suma;
            suma = 0;

        }
        cout << endl << "Tab Y: " << endl;
        printVector(Y);
    }

    void scal(double** U, double* Y) {
        for (int i = 0; i < rozmiar; i++)
            for (int j = 0; j < rozmiar; j++)
                M[i][j] = U[i][j];

        for (int i = 0; i < rozmiar; i++) {
            M[i][rozmiar] = Y[i];
        }

        showMatrix();
    }

    void oblicz() {
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

    void LU() {
        double** A;
        double* B;
        double** L;
        double** U;

        splitMatrix(A, B);
        cout<<endl<<"Macierz A:" << endl;
        printMatrix(A);
        cout<<"Macierz B:" << endl;
        printVector(B);

        cout << endl;

        L = new double* [rozmiar];
        U = new double* [rozmiar];
        for (int i = 0; i < rozmiar; i++) {
            L[i] = new double[rozmiar];
            U[i] = new double[rozmiar];
            for (int j = 0; j < rozmiar; j++) {
                L[i][j] = 0;
                U[i][j] = 0;
            }
        }

        Tab_L_and_U(L, U, A);
        cout << endl << "Macierz L:" << endl;
        printMatrix(L);
        cout << "Macierz U:" << endl;
        printMatrix(U);

        double* Y = new double[rozmiar];
        tablicaY(Y, B, L);
        scal(U, Y);
        oblicz();
    }
};


int main()
{
    Matrix ukladrownan("RURL_dane1.txt");
    ukladrownan.showMatrix();
    ukladrownan.LU();

    return 0;
}