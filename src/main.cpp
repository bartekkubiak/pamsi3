#include <iostream>
#include "Plansza.hh"
#include "Gra.hh"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>


using namespace std;
using namespace sf;


 int main()
 {

    Plansza x;
    Gra gra;
    int przejscie = 0;

    RenderWindow oknoAplikacji( VideoMode( SZEROKOSC, DLUGOSC ), "Kolko Krzyzyk" );
    Clock clock;
    
    while( oknoAplikacji.isOpen() )
    {
        if(przejscie == 0)
        {

        //x.opoznienie(clock);
        x.wylaczanieGry(oknoAplikacji);
        x.stronaStartowa(oknoAplikacji);
        x.przejscieDoGry(oknoAplikacji, przejscie);
        
        }
        else if(przejscie == 1)
        {
        //gra.opoznienie(clock);
        gra.wylaczanieGry(oknoAplikacji);
        gra.plansza(oknoAplikacji, x.getPole(),x.getBicie()  );
        gra.koniecGry(oknoAplikacji, przejscie);
        
        }
        else if (przejscie == 2)
        {
           // x.opoznienie(clock);
            x.wylaczanieGry(oknoAplikacji);
            x.stronaKoncowa(oknoAplikacji, gra.getWygranaCzlowieka(), gra.getWygranaKomputera() );
            if(x.rewanz(oknoAplikacji))
            {   
                gra.zerowanieWszystkiego();
                x.zerwowanieWszystkiego();
                przejscie = 0;
            }
            if(x.wyjscieZGry(oknoAplikacji))
            {
                break;
            }
            
        }


 
 

            








    }
    
     

 }
 
 
