#include "application.hpp"

namespace Ros{

    bool Application::doIt(int prov, int range){

        int sorteo = rand() % range;

        if(prov > sorteo){
            return true;
        }

        return false;

    }

	void Application::PlaySound(std::string pId, int volumen, bool loop){

		Sounds.Get(pId)->Play(volumen, loop);

	}

	void Application::EscribirTexto(std::string fontId, std::string str, int size, int x, int y){

		Ros::Font *Fnt = this->Fonts.Get(fontId);

		Fnt->Draw(str, size, x, y);

	}

	void Application::SetPantallaActiva(std::string pId){

		PantallaActiva = Pantallas.Get(pId);

	}

    Ros::Image* Application::GetImage(std::string pId){

        return Images.Get(pId);

    }

    Ros::Font* Application::GetFont(std::string pId){

        return Fonts.Get(pId);

    }

    void Application::AgregarImagen(std::string pId, std::string pUrl){

        Ros::Image i(pId, pUrl, Window);

        Images.Add(i);

    }

    void Application::AgregarFuente(std::string pId, std::string pUrl){

        Ros::Font i(pId, pUrl, Window);

        Fonts.Add(i);

    }

    void Application::AgregarSonido(std::string pId, std::string pUrl){

        Ros::Sound s(pId, pUrl);

        Sounds.Add(s);

    }

	void Application::AgregarPantalla(Ros::Pantalla *p){

		Pantallas.Add(p);

	}

	void Application::Run(void){

		if(PantallaActiva != NULL){
            PantallaActiva->Init();
			PantallaActiva->Run();
		}

	}

	void Application::Init(void){


	}

	Application::Application(int w, int h, std::string title){

		Width = w;
		Height = h;

		Window = new sf::RenderWindow(sf::VideoMode(w, h), title);

		Window->setFramerateLimit(60);
		Window->setVerticalSyncEnabled(true);

		PantallaActiva = NULL;

	}

	Application::~Application(){
		delete Window;
	}

}
