#include "Plansza.hh"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>



using namespace std;
using namespace sf;



void Plansza::zerwowanieWszystkiego()
{
     wielkoscPola = 0;  
     danaDoPola = 0;   
     iloscBic = 0;     
     danaDoBic = 0;    
     wcisniecieMyszki = 0;

}

int Plansza::getPole()
{
  return wielkoscPola;
}

int Plansza::getBicie()
{
  return iloscBic;
}

void Plansza::opoznienie(Clock zegar)
{
  const float timeStep = 1 / 60.f;
  while(zegar.getElapsedTime().asSeconds() < timeStep)
	sleep(milliseconds(50));
  zegar.restart();
    
}

void Plansza::wylaczanieGry(RenderWindow &oknoAplikacji) 
{
  Event zdarzenie;
  while( oknoAplikacji.pollEvent( zdarzenie ) )
    {
      if( zdarzenie.type == Event::Closed )
      oknoAplikacji.close();
    }
}

void Plansza::konstruktorFont()
{
  font.loadFromFile( "arial.ttf");
}

void Plansza::wygladPolaStartowego(RenderWindow &oknoAplikacji)
{
  oknoAplikacji.clear( Color::White );
  RectangleShape szerokoscPola;

  Font font;
  font.loadFromFile( "arial.ttf" );

  Texture tekstura;
  Sprite obrazek;

  //Start
  if(wielkoscPola > 2 && iloscBic > 2)
  {
    tekstura.loadFromFile( "start.png" );
    obrazek.setTexture( tekstura );
    obrazek.setPosition(100, 5);
    oknoAplikacji.draw(obrazek);
  }
  else
  {
  //obrazek tictactoe
    tekstura.loadFromFile( "tictac.png" );
    obrazek.setTexture( tekstura );
    obrazek.setPosition(200, 50);
    obrazek.setScale(0.1,0.1);
    oknoAplikacji.draw(obrazek);

  Text tekst5( "ILOSC POL I BIC MUSI BYC WIEKSZA NIZ 2", font, 24 );
  tekst5.setPosition( 80, 520 );
  tekst5.setColor( sf::Color::Red );
  oknoAplikacji.draw(tekst5);

  }

  Text tekst1( "PODAJ WIELKOSC PLANSZY", font, 20 );
  tekst1.setPosition( 170, 300 );
  tekst1.setColor( sf::Color::Blue );
  oknoAplikacji.draw(tekst1);

  Text tekst2( "PODAJ ILOSC BIC", font, 20 );
  tekst2.setPosition( 220, 400 );
  tekst2.setColor( sf::Color::Blue );
  oknoAplikacji.draw(tekst2);


  

  //ramki na liczby 
  szerokoscPola.setSize(sf::Vector2f(100, 50));
  szerokoscPola.setOutlineColor(sf::Color::Black);
  szerokoscPola.setOutlineThickness(5);
  szerokoscPola.setPosition(250, 330);
  oknoAplikacji.draw(szerokoscPola);

  szerokoscPola.setPosition(250, 430);
  oknoAplikacji.draw(szerokoscPola);
   
   //ilosc bic
  string abc = to_string(iloscBic);
  Text tekst3( abc, font, 50 );
  tekst3.setPosition( 285, 425 );
  tekst3.setColor( sf::Color::Black );
  oknoAplikacji.draw(tekst3);

   //wielkosc pola 
  abc = to_string(wielkoscPola);
  Text tekst4( abc, font, 50 );
  tekst4.setPosition( 285, 320 );
  tekst4.setColor( sf::Color::Black );
  oknoAplikacji.draw(tekst4);


}

void Plansza::daneWielkosc(RenderWindow &oknoAplikacji)
{
  Mouse myszka;

  if(myszka.getPosition(oknoAplikacji).x < 330 && myszka.getPosition(oknoAplikacji).x > 250 && myszka.getPosition(oknoAplikacji).y < 480 && myszka.getPosition(oknoAplikacji).y > 430)
    if(myszka.isButtonPressed(myszka.Left))  
    {
      danaDoBic++;
      wcisniecieMyszki++;
    }

}

void Plansza::daneBic(RenderWindow &oknoAplikacji)
{
  Mouse myszka;


  if(myszka.getPosition(oknoAplikacji).x < 330 && myszka.getPosition(oknoAplikacji).x > 250 && myszka.getPosition(oknoAplikacji).y < 384 && myszka.getPosition(oknoAplikacji).y > 326)
    if(myszka.isButtonPressed(myszka.Left))
    {
      danaDoPola++;
      wcisniecieMyszki++;
    }

}
void Plansza::przejscieDoGry(RenderWindow &oknoAplikacji, int &przejscie)
{
//wcisniecie prawego klawisza myszki na obrazku Start powoduje przejscie do gry
    Mouse myszka;
    if(iloscBic > 2 && wielkoscPola > 2)
     if(myszka.getPosition(oknoAplikacji).x < 400 && myszka.getPosition(oknoAplikacji).x > 200 && myszka.getPosition(oknoAplikacji).y < 200 && myszka.getPosition(oknoAplikacji).y > 100)
        if(myszka.isButtonPressed(myszka.Right))
        {
         przejscie = 1;
        }


}

void Plansza::stronaStartowa(RenderWindow &oknoAplikacji)
{
  Event wczytywanie;

  wygladPolaStartowego(oknoAplikacji);
  daneWielkosc(oknoAplikacji);
  daneBic(oknoAplikacji);

  if(wcisniecieMyszki > 0)
    if (wczytywanie.type == Event::TextEntered)
      {   
        if (wczytywanie.text.unicode < 128)
        {

          char zmienna =  static_cast<char>(wczytywanie.text.unicode);

          if(danaDoPola > 0)
           wielkoscPola = atoi(&zmienna);
 

          if(danaDoBic > 0)
            iloscBic = atoi(&zmienna);
            

          if(danaDoPola || danaDoBic > 0)
           {
            wcisniecieMyszki = 0;
            danaDoPola = 0;
            danaDoBic = 0;
           }
        }
      }

  

  /**/


  oknoAplikacji.display();



}

void Plansza::stronaKoncowa(RenderWindow &oknoAplikacji, int czlowiek, int komputer)
{

  oknoAplikacji.clear( Color::White );
  Font font;
  font.loadFromFile( "arial.ttf" );
  RectangleShape szerokoscPola;

  if(komputer == 1 || czlowiek == 1)
  {
    Text tekst1( "ZWYCIEZCA:", font, 60 );
    tekst1.setPosition( 100, 100 );
    tekst1.setColor( sf::Color::Black );
    oknoAplikacji.draw(tekst1);

    if(komputer == 1)
    {
      Text tekst2( "KOMPUTER", font, 60 );
      tekst2.setPosition( 100, 200 );
      tekst2.setColor( sf::Color::Blue );
      oknoAplikacji.draw(tekst2);
    }

    if(czlowiek == 1)
    {
      Text tekst2( "CZLOWIEK", font, 60 );
      tekst2.setPosition( 100, 200 );
      tekst2.setColor( sf::Color::Blue );
      oknoAplikacji.draw(tekst2);
    }
  }

  if(komputer == 0 && czlowiek == 0)
  {
      Text tekst2( "REMIS", font, 60 );
      tekst2.setPosition( 100, 200 );
      tekst2.setColor( sf::Color::Blue );
      oknoAplikacji.draw(tekst2);

  }

    Text tekst3( "REWANZ", font, 20 );
    tekst3.setPosition( 110, 350 );
    tekst3.setColor( sf::Color::Black );
    oknoAplikacji.draw(tekst3);

    Text tekst4( "WYJSCIE", font, 20 );
    tekst4.setPosition( 410, 350 );
    tekst4.setColor( sf::Color::Black );
    oknoAplikacji.draw(tekst4);


  szerokoscPola.setSize(sf::Vector2f(100, 50));
  szerokoscPola.setOutlineColor(sf::Color::Black);
  szerokoscPola.setOutlineThickness(5);
  szerokoscPola.setPosition(100, 400);
  oknoAplikacji.draw(szerokoscPola);

  szerokoscPola.setPosition(400, 400);
  oknoAplikacji.draw(szerokoscPola);



  oknoAplikacji.display();

}


bool Plansza::rewanz(RenderWindow &oknoAplikacji)
{
  Mouse myszka;

  if(myszka.getPosition(oknoAplikacji).x < 200 && myszka.getPosition(oknoAplikacji).x > 100 && myszka.getPosition(oknoAplikacji).y < 450 && myszka.getPosition(oknoAplikacji).y > 400)
  {
    if(myszka.isButtonPressed(myszka.Left))
      return true;
  }
  return false;
}

bool Plansza::wyjscieZGry(RenderWindow &oknoAplikacji)
{
  Mouse myszka;

  
  if(myszka.getPosition(oknoAplikacji).x < 500 && myszka.getPosition(oknoAplikacji).x > 400 && myszka.getPosition(oknoAplikacji).y < 450 && myszka.getPosition(oknoAplikacji).y > 400)
    {
      if(myszka.isButtonPressed(myszka.Left))
      return true;
    }
    return false;
  

}


