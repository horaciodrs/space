#ifndef __PANTALLA_PILOTO__
#define __PANTALLA_PILOTO__

#include "lib/object_manager.hpp"
#include "lib/object.hpp"
#include "lib/pantalla.hpp"

class PantallaPiloto : public Ros::Pantalla{

    private:
        ObjectManager<Ros::Object> Estrellas;
        int SelectedOption;
        bool CanProcessEscape;
        bool CanProcessDown;
        bool CanProcessUp;

        Ros::Object *Piloto1;
        Ros::Object *Piloto2;
        Ros::Object *Piloto3;
        Ros::Object *Piloto4;
        Ros::Object *PilotoSelectionLight;

    public:

        void MoverEstrellas(void);
		void CrearEstrellas(void);
		void DibujarEstrellas(void);

        void Init(void);
        void Render(void);
        void EventHandler(void);
        void Salir(std::string pPantallaId);
        void OnWindowResize(void);
        void End(void);
        PantallaPiloto(std::string pId, Ros::Application *pApp);
        ~PantallaPiloto();

};

#endif
