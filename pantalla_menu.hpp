#ifndef __PANTALLA_MENU__
#define __PANTALLA_MENU__

#include "lib/object_manager.hpp"
#include "lib/object.hpp"
#include "lib/pantalla.hpp"
#include "mipantalla.hpp"

class PantallaMenu : public Ros::Pantalla{

	private:
		ObjectManager<Ros::Object> Estrellas;
        int SelectedOption;
		int SelectedPilot;
        bool CanProcessDown;
        bool CanProcessUp;
        bool CanProcessOption;

	public:

		void MoverEstrellas(void);
		void CrearEstrellas(void);
		void DibujarEstrellas(void);

		void DibujarOpciones(void);

		void setSelectedPilot(int pilot){SelectedPilot = pilot;}

		int getSelectedPilot(){return SelectedPilot;}

		void Init(void);
		void Render(void);
		void EventHandler(void);
        void Salir(std::string pPantallaId);
		void OnWindowResize(void);
        void End(void);
		PantallaMenu(std::string pId, Ros::Application *pApp);
		~PantallaMenu();

};

#endif
