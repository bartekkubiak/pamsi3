#include "Gra.hh"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <ctime>




using namespace std;
using namespace sf;


Gra::Gra()
{
    for(int i = 0; i < 15; i++)
        for(int k = 0; k < 15; k++)
            tab[i][k] = 0;

}

int Gra::getWygranaCzlowieka()
{
    return wygranaCzlowieka;
}

int Gra::getWygranaKomputera()
{
    return wygranaKomputera;
}


void Gra::zerowanieWszystkiego()
{
    for(int i = 0; i < 15; i++)
        for(int k = 0; k < 15; k++)
            tab[i][k] = 0;
    ruchUzytkownika = 1;
    ruchKomputera = 0 ;
    iloscRuchow = 0;
    wygranaCzlowieka = 0;
    wygranaKomputera = 0;

}

void Gra::opoznienie(Clock zegar)
{
  const float timeStep = 1 / 60.f;
  while(zegar.getElapsedTime().asSeconds() < timeStep);
  sleep(milliseconds(100));
  zegar.restart();
}

void Gra::wylaczanieGry(RenderWindow &oknoAplikacji)
{
    Event zdarzenie;
    while( oknoAplikacji.pollEvent( zdarzenie ) )
    {
      if( zdarzenie.type == Event::Closed )
      oknoAplikacji.close();
    }
}

void Gra::przypisanieWielkosci(int pole, int bicie)
{
    wielkoscPola = pole;
    iloscBic = bicie;
}

void  Gra::tworzenieLini(RenderWindow &oknoAplikacji)
{
    RectangleShape liniaPionowa, liniaPozioma;
    Font font;
    font.loadFromFile( "arial.ttf" );

    liniaPionowa.setSize(sf::Vector2f(0, 600));
    liniaPionowa.setOutlineColor(sf::Color::Black);
    liniaPionowa.setOutlineThickness(1);

    liniaPozioma.setSize(sf::Vector2f(600, 0));
    liniaPozioma.setOutlineColor(sf::Color::Black);
    liniaPozioma.setOutlineThickness(1);



    for(int i = 1; i <= wielkoscPola - 1; i++)
    {
        int zmienna = DLUGOSC/wielkoscPola;
        liniaPionowa.setPosition(i*zmienna, 0);
        oknoAplikacji.draw(liniaPionowa);

        liniaPozioma.setPosition(0, i*zmienna);
        oknoAplikacji.draw(liniaPozioma);

    }


}

void Gra::wstawianieZnakowPrzezCzlowieka(RenderWindow &oknoAplikacji)
{
    float Mx = Mouse::getPosition(oknoAplikacji).x;
    float My = Mouse::getPosition(oknoAplikacji).y;
    Font font;
    font.loadFromFile( "arial.ttf" );



    if(ruchUzytkownika == 1)
    for(int i = 0; i < wielkoscPola; i++)
        if((Mx > i*(DLUGOSC/wielkoscPola) && Mx < i*(DLUGOSC/wielkoscPola) + DLUGOSC/wielkoscPola )  )
            for(int k = 0; k < wielkoscPola; k++)
            if( (My > k*(SZEROKOSC/wielkoscPola) && My < k*(SZEROKOSC/wielkoscPola) + SZEROKOSC/wielkoscPola))

        if( Mouse::isButtonPressed( Mouse::Left ) )
            {
                if(tab[i][k] == 0)
                {
                tab[i][k] = -1;
                ruchUzytkownika = 0;
                ruchKomputera = 1;
                iloscRuchow++;
                }
                
            }

    for(int i = 0; i < wielkoscPola; i++)
        for(int k = 0; k < wielkoscPola; k++)
            if(tab[i][k] == -1)
            {
                Text tekst1( "X", font, DLUGOSC/wielkoscPola );
                tekst1.setPosition( i*(DLUGOSC/wielkoscPola), k*(SZEROKOSC/wielkoscPola) );
                tekst1.setColor( sf::Color::Black );
                oknoAplikacji.draw(tekst1);

            

            }


}



void Gra::znajdzNajlepszyRuch(int tab[15][15], int &x,int &y)
{
	int naj = -1000;
	int alpha = -1000;
	int beta = 1000;
    
//cout<< "teraz licze" << endl;

    for(int i = 0; i < wielkoscPola; i++)
        for(int k = 0; k < wielkoscPola; k++)
            if(tab[i][k] == 0)
            {
                tab[i][k] = 1;
//cout<<"robie minmax"<<endl;
                int ruch =miniMax(tab, 0, false, alpha, beta); //****************************************
  //             cout<< "zrobilem minmax"<< endl;
                tab[i][k] = 0;
                if(ruch > naj)
                {
                    x = i;
                    y = k;
                    naj = ruch;
                    
                }

            }

}

int Gra::miniMax(int tab[15][15], int glebokosc, bool gracz, int alpha, int beta)
{



    int wynik = sprawdzenieWygranej();

    if(wynik == 10){
		return wynik - glebokosc;
	}
	if(wynik == -10){
		return wynik + glebokosc;
	}
	if(remis()){
		return 0;
	}

    	if(gracz){
		int najlepsze = -1000;
		for(int i = 0; i < wielkoscPola;i++){
			for(int j = 0;j < wielkoscPola;j++){


				if(tab[i][j] == 0){
					tab[i][j] = 1;
					int val = miniMax(tab,glebokosc + 1 ,false,alpha,beta);
					najlepsze = maxx(najlepsze,val);
					alpha = maxx(najlepsze,alpha);
					tab[i][j] = 0;
					if(beta <= alpha)
						break;
				}
				if(beta <= alpha)
					break;
			}
		}
		return najlepsze;
	}else{
		int najlepsze = 1000;
		for(int i = 0; i < wielkoscPola;i++){
			for(int j = 0;j < wielkoscPola;j++){
				if(tab[i][j] == 0){
					tab[i][j] = -1;
					int val = miniMax(tab,glebokosc + 1 ,true,alpha,beta);
					najlepsze = minx(najlepsze,val);
					beta = minx(najlepsze,beta);
					tab[i][j] = 0;
					if(beta <= alpha)
						break;
				}
				if(beta <= alpha)
					break;
			}
		}

		return najlepsze;
	}







}


void Gra::wstawianieZnakowPrzezKomputer(RenderWindow &oknoAplikacji)
{

    Font font;
    font.loadFromFile( "arial.ttf" );
    int x,y;


    if(ruchKomputera == 1)
    {
        
cout<<"Szukam Ruchu" <<endl;

        znajdzNajlepszyRuch(tab,x,y);

cout<<"->Twoja kolej" <<endl;


        //zajmujacy sie wstawianiem ruchu 
        
            tab[x][y] = 1;
            ruchUzytkownika = 1;
            ruchKomputera = 0;
            iloscRuchow++;
            
            
        


    }
        for(int i = 0; i < wielkoscPola; i++)
        for(int k = 0; k < wielkoscPola; k++)
            if(tab[i][k] == 1)
            {
                Text tekst1( "O", font, DLUGOSC/wielkoscPola );
                tekst1.setPosition( i*(DLUGOSC/wielkoscPola), k*(SZEROKOSC/wielkoscPola) );
                tekst1.setColor( sf::Color::Black );
                oknoAplikacji.draw(tekst1);

          
 	  }


       
    

  
            

}



//funkcja sprawdzajaca czy jest remis 
bool Gra::remis()
{
    for(int i = 0; i < wielkoscPola; i++)
        for(int k = 0; k < wielkoscPola; k++)
            if(tab[i][k]==0)
                return false;
    return true;

}

int Gra::sprawdzenieWygranej()
{
    
    //sprawdzanie wygranej 
    for(int i = 0; i < wielkoscPola; i++)
        for(int  k = 0; k < wielkoscPola; k++)
            {  
                
                     //dla gracza
                     // w poziomie
                    for(int l = 0; l < iloscBic; l++)
                    {      
                        
                        if(tab[i + l][k] == -1)
                        {
                            
                                if(l == iloscBic - 1 )
                                    return -10;
                            
                        }
                        else
                        break;

                    }

                    // w pionie
                    for(int l = 0; l < iloscBic; l++)
                    {
                       if(tab[i][k + l] == -1)
                        {
                            if(l == iloscBic - 1 )
                                    return -10;
                        }
                        else
                        break;


                    }

                    // na skos 
                    for(int l = 0; l < iloscBic; l++)
                    {
                       if(tab[i + l][k + l] == -1)
                        {
                            if(l == iloscBic - 1 )
                                    return -10;
                        }
                        else
                        break;
                    }


                    // drugi skos 
                    for(int l = 0; l < iloscBic; l++)
                    {
                       if(tab[i + l][k - l] == -1)
                        {
                            if(l == iloscBic - 1 )
                                    return -10;
                        }
                        else
                        break;
                    }



                    // dla AI 
                    for(int l = 0; l < iloscBic; l++)
                    {      
                        
                        if(tab[i + l][k] == 1)
                        {
                            
                                if(l == iloscBic - 1 )
                                    return 10;
                            
                        }
                        else
                        break;

                    }

                    // w pionie
                    for(int l = 0; l < iloscBic; l++)
                    {
                       if(tab[i][k + l] == 1)
                        {
                            if(l == iloscBic - 1 )
                                    return 10;
                        }
                        else
                        break;


                    }

                    // na skos 
                    for(int l = 0; l < iloscBic; l++)
                    {
                       if(tab[i + l][k + l] == 1)
                        {
                            if(l == iloscBic - 1 )
                                    return 10;
                        }
                        else
                        break;
                    }


                    // drugi skos 
                    for(int l = 0; l < iloscBic; l++)
                    {
                       if(tab[i + l][k - l] == 1)
                        {
                            if(l == iloscBic - 1 )
                                    return 10;
                        }
                        else
                        break;
                    }
            }

    
 
return 0;

}


int Gra::maxx(int a,int b)
{
	if(a > b){
		return a;
	}
	return b;
}



int Gra::minx(int a,int b)
{
	if(a < b){
		return a;
	}
	return b;
}





void Gra::plansza(RenderWindow &oknoAplikacji, int pole, int bicie)
{
    przypisanieWielkosci(pole, bicie);

    oknoAplikacji.clear( Color::White );

    tworzenieLini(oknoAplikacji);

    

    wstawianieZnakowPrzezCzlowieka(oknoAplikacji);


    
   wstawianieZnakowPrzezKomputer(oknoAplikacji);


oknoAplikacji.display();
}



void Gra::koniecGry(RenderWindow &oknoAplikacji, int &przejscie)
{
    if(sprawdzenieWygranej() == -10 && remis() == false )
    {
        przejscie = 2;
        wygranaCzlowieka = 1;
        wygranaKomputera = 0;
    }

    if(sprawdzenieWygranej() == 10 && remis() == false  )
    {
        przejscie = 2;
        wygranaKomputera = 1;
        wygranaCzlowieka = 0;
 
    }

    if(remis() == true)
    {
        przejscie = 2;
        
    }


}
