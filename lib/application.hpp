#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include <iostream>
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Graphics/Font.hpp>
#include "image.hpp"
#include "font.hpp"
#include "sound.hpp"
#include "object_manager.hpp"
#include "pantalla.hpp"

namespace Ros{

	class Pantalla;

	class Application{

		private:
			int Width;
			int Height;
			sf::RenderWindow *Window;
			ObjectManager<Ros::Pantalla *> Pantallas;
            ObjectManager<Ros::Image> Images;
            ObjectManager<Ros::Sound> Sounds;
            ObjectManager<Ros::Font> Fonts;
			Ros::Pantalla *PantallaActiva;
		public:
			friend class Ros::Pantalla;
			bool doIt(int prov, int range);
			void UpdateScreenWidth(int w){Width = w;}
			void UpdateScreenHeight(int h){Height = h;}
			int GetScreenWidth(void){return Width;}
			int GetScreenHeight(void){return Height;}
			Ros::Pantalla *GetPantallaActiva(void){return PantallaActiva;}
            Ros::Image *GetImage(std::string pId);
            Ros::Font *GetFont(std::string pId);
            void PlaySound(std::string pId, int volumen, bool loop);
			void StopSound(std::string pId);
			sf::RenderWindow *GetRenderWindow(void){return Window;}
			void SetPantallaActiva(std::string pId);
            void AgregarImagen(std::string pId, std::string pUrl);
            void AgregarSonido(std::string pId, std::string pUrl);
            void AgregarFuente(std::string pId, std::string pUrl);
			void AgregarPantalla(Ros::Pantalla *p);
			void EscribirTexto(std::string fontId, std::string srt, int size, int x, int y);
			void EscribirTexto(std::string fontId, std::string srt, int size, int x, int y, sf::Color color);
			void Init(void);
			void Run(void);
			Application(int w, int h, std::string title);
			~Application();

	};

}

#endif
