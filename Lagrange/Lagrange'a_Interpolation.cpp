#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

void wyswietlanie(double*& wezly, double*& wartosci, double liczba_wezlow)
{
    cout << "Liczba wezlow wynosi: " << liczba_wezlow << endl;
    cout << "Wezly  |   Wartosci    " << endl;
    for (int i = 0; i < liczba_wezlow; i++) {
        cout << wezly[i] << "    |   ";
        cout << wartosci[i] << " " << endl;
    }
}

int wczytaj(string nazwapliku, double*& wezly, double*& wartosci) {
    fstream czytaj;
    czytaj.open(nazwapliku);

    if (!czytaj.is_open()) {
        cout << "Nie można otworzyć pliku do odczytu" << endl;
        return -1;
    }

    int liczba_wezlow;
    czytaj >> liczba_wezlow;

    wezly = new double[liczba_wezlow];
    wartosci = new double[liczba_wezlow];

    for (int i = 0; i < liczba_wezlow; i++) {
        czytaj >> wezly[i];
        czytaj >> wartosci[i];
    }
    czytaj.close();
    wyswietlanie(wezly, wartosci, liczba_wezlow);
    return liczba_wezlow;
}
//ZADANIE 1
void Interpolacja_Lagrange_a(double*& wezly, double*& wartosci, double liczba_wezlow, double wybrany) {

    if (liczba_wezlow == 0) {
        return;
    }

    double wynik = 0;
    for (int i = 0; i < liczba_wezlow; i++) {
        double suma = wartosci[i];
        for (int j = 0; j < liczba_wezlow; j++) {
            if (j != i) {
                suma *= (wybrany - wezly[j]) / (wezly[i] - wezly[j]);
            }
        }
        wynik += suma;
    }
    cout << "Wynik dla wezla " << wybrany << " to " << wynik << endl;

}

void zadanie_2()
{
    //Wprowadzenie danych
    int liczba_wezlow = 4;
    double* wezly = new double[liczba_wezlow];
    int tworzenie = 3;
    for (int i = 0; i < liczba_wezlow; i++) {
        wezly[i] = pow(tworzenie, 3);
        tworzenie++;
    }
    
    double* wartosci = new double[liczba_wezlow];
    double pierwiastek = 1.0 / 3.0;
    for (int i = 0; i < liczba_wezlow; i++) {
        wartosci[i] = pow(wezly[i], pierwiastek);
    }

    wyswietlanie(wezly, wartosci, liczba_wezlow);

    Interpolacja_Lagrange_a(wezly, wartosci, liczba_wezlow, 50);

}

int main() {
    double* wezly;
    double* wartosci;
    int liczba_wezlow = wczytaj("MN-1.txt", wezly, wartosci);

    Interpolacja_Lagrange_a(wezly,wartosci,liczba_wezlow, -1);
    Interpolacja_Lagrange_a(wezly, wartosci, liczba_wezlow, 0.5);
    
    double wybrany;
    cout << "Podaj wezel dla ktorego obliczyc wynik" << endl;
    cin >> wybrany;

    Interpolacja_Lagrange_a(wezly, wartosci, liczba_wezlow, wybrany);

    delete[] wezly;
    delete[] wartosci;

    cout << endl << "ZADANIE 2 F(50) = (50)^1/3" << endl << endl;
    zadanie_2();
    

    return 0;
}