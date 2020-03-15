#ifndef __PANTALLA_PILOTO__
#define __PANTALLA_PILOTO__

#include "lib/object_manager.hpp"
#include "lib/object.hpp"
#include "lib/pantalla.hpp"

#include "pantalla_menu.hpp"
#include "piloto.hpp"


class PantallaPiloto : public Ros::Pantalla{

    private:
        ObjectManager<Ros::Object> Estrellas;
        int SelectedOption;
        bool CanProcessEscape;
        bool CanProcessLeft;
        bool CanProcessRight;
        bool CanProcessEnter;

        ObjectManager<Piloto> *globalPilotos;
        ObjectManager<Ros::Object> imgPilotos;
        Ros::Object *PilotoSelectionLight;

    public:

        void setGlobalPilotos(ObjectManager<Piloto> *auxGlobalPilotos){globalPilotos = auxGlobalPilotos;}

        void MoverEstrellas(void);
		void CrearEstrellas(void);
		void DibujarEstrellas(void);

        void setSelectedPilot(int p){SelectedOption = p;}

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
