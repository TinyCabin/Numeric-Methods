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

    double getRozmiar() {
        return rozmiar;
    }

    double getElement(int i, int j) {
        return M[i][j];
    }

    //JACOBIN
    void Tab_A_into_3(double** A, double**& L, double**& U, double**& D)
    {
        double suma = 0;
        for (int i = 0; i < rozmiar; i++) {
            for (int j = 0; j < rozmiar; j++) {
                if (i < j)
                    U[i][j] = A[i][j];
                else if (i > j)
                    L[i][j] = A[i][j];
            }
            D[i][i] = A[i][i];
        }
    }

    bool if_dominant(double** A) {
        bool min_1_wiekszy = false;
        for (int i = 0; i < rozmiar; i++) {
            double suma = 0;
            double diagonalna = abs(A[i][i]);
            for (int j = 0; j < rozmiar; j++) {
                if (i != j) {
                    suma += abs(A[i][j]);
                }
            }
            if (diagonalna < suma) {
                cout << "Nie jest slabo dominujaca diagonalnie " << endl;
                return false;
            }
            if (diagonalna > suma) {
                min_1_wiekszy = true;
            }
        }
        if (min_1_wiekszy == true) {
            cout << "Jest Slabo Dominujaca" << endl;
            return true;
        }
        return false;
    }

    void macierz_odwrotna_diagonalna(double**& D)
    {
        for (int i = 0; i < rozmiar; i++) {
            if (D[i][i] == 0) {
                cout << endl << "Macierz nie odwracalna " << endl; return;
            }
        }
        for (int i = 0; i < rozmiar; i++)
            D[i][i] = (1.0 / D[i][i]);
    }

    void oblicz_Jacobina(double** L, double** U, double** D_inverse, double* B, double* x, int maxIteration, double epsilon)
    {
        cout << endl << "Przyjety blad(epsilon) = " << epsilon << endl;
        double* wynik = new double[rozmiar];
        double* temp = new double[rozmiar];
        double* bledy = new double[rozmiar];

        for (int iteracja = 0; iteracja < maxIteration; ++iteracja) {
            for (int i = 0; i < rozmiar; ++i) {
                temp[i] = B[i]; //  B
                for (int j = 0; j < rozmiar; ++j) {
                    if (i != j) {
                        temp[i] -= (L[i][j] + U[i][j]) * x[j];
                    }
                }
                temp[i] *= D_inverse[i][i];
            }
            //Liczenie bledu stopu
            bool stop = true;
            for (int i = 0; i < rozmiar; i++){
                bledy[i] = abs(temp[i] - x[i]);
                if (bledy[i] >= epsilon) {
                    stop = false;
                    break;
                }
            }


            if (stop) {
                cout << "Uzyskano dokladnosc stopu po " << iteracja + 1 << " iteracjach.";
                cout << endl << "Wynik: " << endl;
                for (int i = 0; i < rozmiar; ++i) {
                    cout << "x[" << i << "] wynosi: "<<setw(4)<<setprecision(6) << x[i] << endl;
                }
                cout << endl << "Bledy dla x: " << endl;
                for (int i = 0; i < rozmiar; ++i) {
                    cout << "x[" << i << "] blad wynosi: " << bledy[i] << endl;
                }
                return;
            }

            for (int i = 0; i < rozmiar; ++i) {
                x[i] = temp[i];
            }
        }

        cout << endl << "Wynik: " << endl;
        for (int i = 0; i < rozmiar; ++i) {
            cout << "x[" << i << "] wynosi: " << x[i] << endl;
        }

        delete[] wynik;
        delete[] temp;
    }

    void Jacobian(int maxIteration,double epsilon) {

        showMatrix();
        double** A;
        double* B;
        splitMatrix(A, B);

        //cout << endl;
        //printMatrix(A);
        //cout << endl;
        //printVector(B);

        if (!if_dominant(A))
            return;

        double** L = new double* [rozmiar];
        double** U = new double* [rozmiar];
        double** D = new double* [rozmiar];
        double* x = new double[rozmiar];
        for (int i = 0; i < rozmiar; i++) {
            L[i] = new double[rozmiar];
            U[i] = new double[rozmiar];
            D[i] = new double[rozmiar];
            x[i] = 0;
            for (int j = 0; j < rozmiar; j++) {
                L[i][j] = 0;
                U[i][j] = 0;
                D[i][j] = 0;
            }
        }

        Tab_A_into_3(A, L, U, D);

        cout << endl << "Macierz L" << endl;
        printMatrix(L);
        cout << "Macierz U" << endl;
        printMatrix(U);
        cout << "Macierz D" << endl;
        printMatrix(D);
        cout << endl;
        macierz_odwrotna_diagonalna(D);
        cout << endl; printMatrix(D);

        oblicz_Jacobina(L, U, D, B, x, maxIteration, epsilon);
    }

};

int main()
{
    Matrix ukladrownan1("RURL_dane1.txt");
    ukladrownan1.Jacobian(100, 0.000001);

    return 0;
}