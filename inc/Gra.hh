#ifndef GRA_HH
#define GRA_HH
#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

static unsigned int DLUGOSC = 600;
static unsigned int SZEROKOSC = 600;



class Gra
 {  

     int wielkoscPola;
     int iloscBic;
     int tab[15][15];
     int ruchUzytkownika = 1;
     int ruchKomputera = 0 ;
     int iloscRuchow = 0;
     int wygranaCzlowieka = 0;
     int wygranaKomputera = 0;
      


     public:

     Gra();
     void zerowanieWszystkiego();
     void wylaczanieGry(RenderWindow &);
     void opoznienie(Clock);
     void plansza(RenderWindow &, int, int);
     void przypisanieWielkosci(int , int );
     void tworzenieLini(RenderWindow &);
     void wstawianieZnakowPrzezCzlowieka(RenderWindow &);
     void wstawianieZnakowPrzezKomputer(RenderWindow &);
     int sprawdzenieWygranej();
     bool remis();
     void znajdzNajlepszyRuch(int [15][15],int &, int &);
     int miniMax(int [15][15], int , bool , int , int );
     int maxx(int a,int b);
     int minx(int , int );
     void koniecGry(RenderWindow &, int &);
     int getWygranaCzlowieka();
     int getWygranaKomputera();
     
    
   

    
 };

 #endif


