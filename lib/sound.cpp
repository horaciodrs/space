#include <iostream>
#include "sound.hpp"

namespace Ros{

    void Sound::Play(int volume, bool loop){

        Sonido->setVolume(volume);
        Sonido->setLoop(loop);

        Sonido->play();

    }

    Sound::Sound(std::string pId, std::string pUrl) : Id(pId), Url(pUrl){
        
        bufSonido = new sf::SoundBuffer();

        if(!bufSonido->loadFromFile(pUrl)){
            Sonido = NULL;
        }else{
            Sonido = new sf::Sound();
            Sonido->setBuffer(*bufSonido);
        }

        //delete bufSonido;
    		
    }

    Sound::Sound(){

    }

    Sound::~Sound(){
        
    }

}
