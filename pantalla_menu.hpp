#ifndef __PANTALLA_MENU__
#define __PANTALLA_MENU__

#include "lib/object_manager.hpp"
#include "lib/object.hpp"
#include "lib/pantalla.hpp"

class PantallaMenu : public Ros::Pantalla{

	private:
		ObjectManager<Ros::Object> Estrellas;
		ObjectManager<Ros::Object> Opciones;

	public:

		void MoverEstrellas(void);
		void CrearEstrellas(void);
		void DibujarEstrellas(void);

		void CrearOpciones(void);
		void DibujarOpciones(void);

		void Init(void);
		void Render(void);
		void EventHandler(void);
		void OnWindowResize(void);
		PantallaMenu(std::string pId, Ros::Application *pApp);
		~PantallaMenu();

};

#endif