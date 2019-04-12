#ifndef __SOUND_HPP__
#define __SOUND_HPP__

#include <SFML/Audio.hpp>

namespace Ros{

    class Sound{
        
        private:
            std::string Id;
            std::string Url;
            sf::SoundBuffer *bufSonido;
            sf::Sound *Sonido;
        public:
            std::string getId(){return Id;}
            std::string getUrl(){return Url;}
            sf::Sound* getSound(void){return Sonido;}
            void Play(int volumen, bool loop);
            Sound(std::string pId, std::string pUrl);
            Sound();
            ~Sound();

    };

}

#endif
