#ifndef __PANTALLA_H__
#define __PANTALLA_H__

#include <string>
#include "image.hpp"
#include "application.hpp"

namespace Ros{
	
	enum Teclas{keyLeft, keyUp, keyRight, keyDown, keySpace, keyEnter};

	class Application;

	class Pantalla{
		protected:
			std::string Id;
			Ros::Application *App;
		public:
			bool isKeyActive[6];
            bool isKeyUp[6];
			std::string getId(){return Id;}
			void procesarTeclasActivas(sf::Event *event);
			void procesarTeclasUp(sf::Event *event);
            virtual void Init(void);
			virtual void Render(void);
			virtual void Run(void);
			virtual void EventHandler();
			virtual void OnWindowResize(void);
			virtual ~Pantalla();
			Pantalla(std::string pId, Ros::Application *pApp);

	};

}

#endif
