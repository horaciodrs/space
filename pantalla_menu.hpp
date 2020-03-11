#ifndef __PANTALLA_MENU__
#define __PANTALLA_MENU__

#include "lib/object_manager.hpp"
#include "lib/object.hpp"
#include "lib/pantalla.hpp"

struct PilotoSkills{
    int Velocidad;     //Velocidad de la nave.
    float Escudo;      //Porcentaje de daño que recibe la nave soportar un ataque.
    float Power;       //Porcentaje de daño que recibe un enemigo al soportar un ataque del piloto.
};

class PantallaMenu : public Ros::Pantalla{

	private:
		ObjectManager<Ros::Object> Estrellas;
        int SelectedOption;
		int SelectedPilot;
		PilotoSkills SelectedPilotSkills;
        bool CanProcessDown;
        bool CanProcessUp;
        bool CanProcessOption;

	public:

		void MoverEstrellas(void);
		void CrearEstrellas(void);
		void DibujarEstrellas(void);

		void DibujarOpciones(void);

		void setSelectedPilot(int pilot, PilotoSkills skills){SelectedPilot = pilot; SelectedPilotSkills = skills;}

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
