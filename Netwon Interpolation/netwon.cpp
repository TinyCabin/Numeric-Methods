#include <iostream>
#include <fstream>

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
        exit(-1);
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

double* iloraz(double*& wezly, double*& wartosci, int liczba_wezlow) //bk
{
    double* tablica = new double[liczba_wezlow];

    for (int i = 0; i < liczba_wezlow; i++)
        tablica[i] = wartosci[i];

    for (int i = 1; i < liczba_wezlow; i++) {
        for (int j = liczba_wezlow - 1; j >= i; j--) {
            tablica[j] = (tablica[j] - tablica[j - 1]) / (wezly[j] - wezly[j - i]);
        }
    }


    for (int j = 0; j < liczba_wezlow; j++)
        cout << tablica[j] << " | " << endl;

    return tablica;

}


double Interpolacja_Netwona(double wybrany, double*& wartosci, double*& tablica, double liczba_wezlow)
{
    double wynik = tablica[0];

    for (int i = 1; i < liczba_wezlow; i++)
    {
        double iloczyn = 1.0;
        for (int j = 0; j < i; j++)
        {
            iloczyn *= (wybrany - wartosci[j]); //pk
        }
        wynik += tablica[i] * iloczyn;
    }
    return wynik;
}


int main() {
    double* wezly;
    double* wartosci;
    double liczba_wezlow = wczytaj("MN-2-p2.txt", wezly, wartosci);
    cout << endl;

    double x = -1;
    double* tablica = iloraz(wezly, wartosci, liczba_wezlow);
    double wynik = Interpolacja_Netwona(x, wezly, tablica, liczba_wezlow);
    cout << "Dla wezlu "<< x <<" wynik to : " << wynik << endl;

    x = 2;
    wynik = Interpolacja_Netwona(x, wezly, tablica, liczba_wezlow);
    cout << "Dla wezlu " << x << " wynik to : " << wynik << endl;


    delete[] wezly;
    delete[] wartosci;

        
    return 0;
}