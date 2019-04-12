#ifndef __FONT_HPP__
#define __FONT_HPP__

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Font.hpp>

namespace Ros{

    class Font{
        
        private:
            std::string Id;
            std::string Url;
            sf::Font *Fuente;
            sf::RenderWindow *Window;
        public:
            std::string getId(){return Id;}
            std::string getUrl(){return Url;}
            sf::Font* getFont(void){return Fuente;}
            void Draw(std::string, int size, int x, int y);
            void Draw(std::string, int size, int x, int y, float angle);
            Font(std::string pId, std::string pUrl, sf::RenderWindow *pWindow);
            Font();
            ~Font();

    };

}

#endif
