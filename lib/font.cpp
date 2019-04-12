#include <iostream>
#include "font.hpp"

namespace Ros{

    void Font::Draw(std::string str, int size, int x, int y){

        Draw(str, size, x, y, 0);

    }

    void Font::Draw(std::string str, int size, int x, int y, float angle){

        sf::Text text;

        text.setFont(*Fuente);
        text.setString(str);
        text.setCharacterSize(size);
        text.setFillColor(sf::Color::White);
        text.setStyle(sf::Text::Bold | sf::Text::Underlined);
        text.setPosition(x, y);

        sf::Vector2f centro;
        
        //centro.x = text.getLocalBounds().width / 2.f;
        //centro.y = text.getLocalBounds().height / 2.f;

        //text.setPosition(centro.x - text.getLocalBounds().width / 2.f
        //               , centro.y + text.getLocalBounds().height / 2.f);

        //text.setOrigin(centro);

        if(angle != 0){
           text.rotate(angle*180/3.14);
        }

        Window->draw(text);
        
    }

    Font::Font(std::string pId, std::string pUrl, sf::RenderWindow *pWindow) : Id(pId), Url(pUrl), Window(pWindow){
        
        Fuente = new sf::Font();

    	if(!Fuente->loadFromFile(pUrl)){
    		Fuente = NULL;
    	}
    		
    }

    Font::Font(){

    }

    Font::~Font(){

    }

}
