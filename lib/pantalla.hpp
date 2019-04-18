#ifndef __PANTALLA_H__
#define __PANTALLA_H__

#include <string>
#include "image.hpp"
#include "application.hpp"

namespace Ros{
	
	enum Teclas{keyLeft, keyUp, keyRight, keyDown, keySpace, keyEnter, keyEscape};

	class Application;

	class Pantalla{
		protected:
			std::string Id;
			Ros::Application *App;
            bool Running;
            void ResetKeys(void);
		public:
			bool isKeyActive[7];
            bool isKeyUp[6];
			std::string getId(){return Id;}
            void setRunning(bool p){Running = p;}
			void procesarTeclasActivas(sf::Event *event);
			void procesarTeclasUp(sf::Event *event);
            virtual void Init(void);
			virtual void Render(void);
			virtual void Run(void);
            virtual void Salir(std::string pPantallaId);
			virtual void EventHandler();
			virtual void OnWindowResize(void);
            virtual void End(void);
			virtual ~Pantalla();
			Pantalla(std::string pId, Ros::Application *pApp);

	};

}

#endif
