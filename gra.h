#pragma once
class gra {

private:
    struct pozycja // struktura potrzebna dla AI do wykonania ruchu
    {
        int x, y;
    };
    //tablica do gry
    char tab[3][3] = { ' ', ' ', ' ',
                       ' ', ' ', ' ',
                       ' ', ' ', ' ' }; 
    char znakGracz; //znak gracza
    char znakAi; //znak AI
    int ruch = 0; //licznik ruchów
    bool czyPoprawnyRuch = 0; //
public:
    gra();  //konstruktor wybiera kto jest O a kto X
    ~gra() {}; //destruktor

    void wys(); //wyswietlanie 
    void wpisz(); // wpisywanie przez gracza
    bool zwyciezca(); //sprawdzanie zwyciezcy
    bool remis(); //sprawdzanie remisu
    bool pozostaleRuchy(); //sprawdzanie jakie ruchy zostaly
    int wygrana(); //najlepsze ruchy dla komputera
    int minimax(int pom1, bool pom2); //skrypt AI minimax
    pozycja znajdzRuch(); //znajduje najlepszy ruch do wykonania dla komputera
    void wpiszAi(pozycja); //wpisywanie ruchu AI do tablicy
    void rozgrywka(); // funkcja rozgrywki


};
