#include "gra.h"
#include <iostream>
#include "bledy.h"
#include <cstdlib>
#include <time.h>

using namespace std;

bool gra::pozostaleRuchy()
{
    //zliczanie pozostalych mozliwych ruchow
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (tab[i][j] == ' ')
                return true;
    return false;
}


int gra::wygrana()
{
    // Sprawdzenie wygranego ruchu poziomo.
    for (int x = 0; x < 3; x++)
    {
        if (tab[x][0] == tab[x][1] && tab[x][1] == tab[x][2])
        {
            if (tab[x][0] == znakAi)
                return +10;
            else if (tab[x][0] == znakGracz)
                return -10;
        }
    }

    // Sprawdzenie wygranego ruchu pionowo.
    for (int y = 0; y < 3; y++)
    {
        if (tab[0][y] == tab[1][y] && tab[1][y] == tab[2][y])
        {
            if (tab[0][y] == znakAi)
                return +10;

            else if (tab[0][y] == znakGracz)
                return -10;
        }
    }

    // Sprawdzanie wygranego ruchu po skosach.
    if (tab[0][0] == tab[1][1] && tab[1][1] == tab[2][2])
    {
        if (tab[0][0] == znakAi)
            return +10;
        else if (tab[0][0] == znakGracz)
            return -10;
    }

    if (tab[0][2] == tab[1][1] && tab[1][1] == tab[2][0])
    {
        if (tab[0][2] == znakAi)
            return +10;
        else if (tab[0][2] == znakGracz)
            return -10;
    }

    // Jezeli remis zwroc 0
    return 0;
}

gra::gra() {
    // wybieranie poprzez losowanie kto jest O a kto X
    int pom = rand() % 2 + 1;
    if (pom == 1) {
        znakGracz = 'O';
        znakAi = 'X';
    }
    else {
        znakGracz = 'X';
        znakAi = 'O';
    }
}

int gra::minimax(int pom1, bool pom2)
{
    int wynik = wygrana();

    // Jezeli komputer wygral zwroc jego wynik

    if (wynik == 10)
        return wynik;

    if (wynik == -10)
        return wynik;

    // Remis
    if (pozostaleRuchy() == false)
        return 0;

    if (pom2)
    {
        int najlepszyRuch = -1000;

        // Sprawdz wszystkie elementy tablicy
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                // Sprawdz czy element tablicy jest pusty
                if (tab[i][j] == ' ')
                {
                    // zrob ruch
                    tab[i][j] = znakAi;

                    // Odwolaj sie do funkcji rekurencyjnie i znajdz najlepszy ruch
                    najlepszyRuch = max(najlepszyRuch, minimax(pom1 + 1, !pom2));

                    // cofnij ruch
                    tab[i][j] = ' ';
                }
            }
        }
        return najlepszyRuch;
    }

    else
    {
        int najlepszyRuch = 1000;

        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                // sprawdz czy element tablicy jest pusty
                if (tab[i][j] == ' ')
                {
                    // zrob ruch
                    tab[i][j] = znakGracz;

                    // Odwolaj sie do funkcji rekurencyjnie i znajdz najlepszy ruch
                    najlepszyRuch = min(najlepszyRuch, minimax(pom1 + 1, !pom2));

                    //cofnij ruch
                    tab[i][j] = ' ';
                }
            }
        }
        return najlepszyRuch;
    }
}

gra::pozycja gra::znajdzRuch()
{
    int najlepszaDec = -1000;
    pozycja najlepszyRuch;
    najlepszyRuch.x = -1;
    najlepszyRuch.y = -1;

    // sprawdz wszystkie elementy tablicy, znajdz puste, wywolaj funkcje minimax i znajdz najlepszy ruch
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            // sprawdz czy element jest pusty
            if (tab[i][j] == ' ')
            {
                // Make the move
                tab[i][j] = znakAi;

                int ruch = minimax(0, false);

                // cofnij ruch
                tab[i][j] = ' ';

                // jezeli znaleziono lepszy ruch zamien go z aktualnym
                if (ruch > najlepszaDec)
                {
                    najlepszyRuch.x = i;
                    najlepszyRuch.y = j;
                    najlepszaDec = ruch;
                }
            }
        }
    }

    return najlepszyRuch;
}


void gra::wpiszAi(pozycja pom) {
    // jezeli ilosc wykonanych ruchow w grze jest rozna od 9 wpisz znak AI
    if (ruch != 9) {
        tab[pom.x][pom.y] = znakAi;
        ruch++;
    }
}


void gra::wys() {
    //wyswietlanie tablicy
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (i == 0 && (j == 1 || j == 2))
                cout << "|";
            if (i == 1 && (j == 1 || j == 2))
                cout << "|";
            if (i == 2 && (j == 1 || j == 2))
                cout << "|";
            cout << tab[i][j];
        }
        cout << endl;
    }
}

void gra::wpisz() {

    //funkcja wpisywania przez gracza

    char pozycja;
    int x, y;
    cin >> pozycja;

    switch (pozycja) {
    case '1':
        x = 0;
        y = 0;
        break;
    case '2':
        x = 0;
        y = 1;
        break;
    case '3':
        x = 0;
        y = 2;
        break;
    case '4':
        x = 1;
        y = 0;
        break;
    case '5':
        x = 1;
        y = 1;
        break;
    case '6':
        x = 1;
        y = 2;
        break;
    case '7':
        x = 2;
        y = 0;
        break;
    case '8':
        x = 2;
        y = 1;
        break;
    case '9':
        x = 2;
        y = 2;
        break;
    default:
        throw bledy::zla_pozycja;
        czyPoprawnyRuch = 0;
        break;
    }

    if (tab[x][y] != ' ') {
        throw bledy::pozycja_zapelniona;
        czyPoprawnyRuch = 0;
    }
    else {
        tab[x][y] = znakGracz;
        ruch++;
        czyPoprawnyRuch = 1;
    }

}



bool gra::zwyciezca() {
    //sprawdzenie wygranego w poziomie
    if (tab[0][0] == tab[0][1] && tab[0][0] != ' ' && tab[0][0] == tab[0][2])
        return 1;
    if (tab[1][0] == tab[1][1] && tab[1][0] != ' ' && tab[1][0] == tab[1][2])
        return 1;
    if (tab[2][0] == tab[2][1] && tab[2][0] != ' ' && tab[2][0] == tab[2][2])
        return 1;
    //sprawdzenie wygranego w pionie
    if (tab[0][0] == tab[1][0] && tab[0][0] != ' ' && tab[0][0] == tab[2][0])
        return 1;
    if (tab[0][1] == tab[1][1] && tab[0][1] != ' ' && tab[0][1] == tab[2][1])
        return 1;
    if (tab[0][2] == tab[1][2] && tab[0][2] != ' ' && tab[0][2] == tab[2][2])
        return 1;
    //sprawdzenie wygranego po skosie
    if (tab[0][0] == tab[1][1] && tab[0][0] != ' ' && tab[0][1] == tab[2][2])
        return 1;
    if (tab[0][2] == tab[1][1] && tab[0][2] != ' ' && tab[0][2] == tab[2][0])
        return 1;

    return 0;

}

bool gra::remis() {
    //sprawdzanie czy jest remis
    if (ruch >= 9 && zwyciezca() == 0)
        return 1;
}

void gra::rozgrywka() { //skrypt obslugujacy cala rozgrywke
    while (true) {

        system("cls");


        if (znakGracz == 'O') {

            try {
                this->wys();
                this->wpisz();
                if (czyPoprawnyRuch == 1)
                    this->wpiszAi(this->znajdzRuch());

            }
            catch (bledy blad) {
                if (blad == bledy::zla_pozycja)
                    cout << "Podales zly znak" << endl;
                if (blad == bledy::pozycja_zapelniona)
                    cout << "Ta pozycja jest juz zajeta" << endl;
                system("pause");
            }


        }
        else {

            try {
                if (ruch == 0)
                    this->wpiszAi(this->znajdzRuch());
                if (czyPoprawnyRuch == 1)
                    this->wpiszAi(this->znajdzRuch());
                if (this->zwyciezca() == 1) {
                    break;
                }
                this->wys();
                this->wpisz();

            }
            catch (bledy blad) {
                if (blad == bledy::zla_pozycja)
                    cout << "Podales zly znak" << endl;
                if (blad == bledy::pozycja_zapelniona)
                    cout << "Ta pozycja jest juz zajeta" << endl;
                system("pause");
            }
        }
        cout << endl;
        if (this->zwyciezca() == 1) {
            break;
        }
        if (this->remis() == 1) {
            break;
        }


    }
    system("cls");
    this->wys();
    if (this->zwyciezca() == 1)
        cout << "wygrana komputera" << endl;

    if (this->remis() == 1)
        cout << "remis" << endl;

}