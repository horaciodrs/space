#ifndef __IMAGE_HPP__
#define __IMAGE_HPP__

#include <SFML/Graphics.hpp>

namespace Ros{

    class Image{
        
        private:
            std::string Id;
            std::string Url;
            sf::Texture *Imagen;
            sf::RenderWindow *Window;
        public:
            std::string getId(){return Id;}
            std::string getUrl(){return Url;}
            int getWidth(){return Imagen->getSize().x;}
            int getHeight(){return Imagen->getSize().y;}
            sf::Texture* getImage(void){return Imagen;}
            void Draw(int x, int y);
            void Draw(int x, int y, float angle);
            void Draw(int x, int y, int l, int t, int w, int h);
            Image(std::string pId, std::string pUrl, sf::RenderWindow *pWindow);
            Image();
            ~Image();

    };

}

#endif
