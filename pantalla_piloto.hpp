#ifndef __PANTALLA_PILOTO__
#define __PANTALLA_PILOTO__

#include "lib/object_manager.hpp"
#include "lib/object.hpp"
#include "lib/pantalla.hpp"

#include "pantalla_menu.hpp"


class PantallaPiloto : public Ros::Pantalla{

    private:
        ObjectManager<Ros::Object> Estrellas;
        int SelectedOption;
        bool CanProcessEscape;
        bool CanProcessLeft;
        bool CanProcessRight;
        bool CanProcessEnter;

        Ros::Object *Piloto1;
        Ros::Object *Piloto2;
        Ros::Object *Piloto3;
        Ros::Object *Piloto4;
        Ros::Object *PilotoSelectionLight;

        PilotoSkills skillPiloto[4];

    public:

        void MoverEstrellas(void);
		void CrearEstrellas(void);
		void DibujarEstrellas(void);

        void Init(void);
        void Render(void);
        void EventHandler(void);
        void Salir(std::string pPantallaId, int pSelectedPilot);
        void OnWindowResize(void);
        void End(void);
        PantallaPiloto(std::string pId, Ros::Application *pApp);
        ~PantallaPiloto();

};

#endif
