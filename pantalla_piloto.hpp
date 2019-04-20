#ifndef __PANTALLA_PILOTO__
#define __PANTALLA_PILOTO__

#include "lib/object_manager.hpp"
#include "lib/object.hpp"
#include "lib/pantalla.hpp"

class PantallaPiloto : public Ros::Pantalla{

    private:
        int SelectedOption;
    public:
        void Init(void);
        void Render(void);
        void EventHandler(void);
        void Salir(std:string pPantallaId);
        void OnWindowResize(void);
        void End(void);
        PantallaPiloto(std::string pId, Ros::Application *pApp);
        ~PantallaPiloto();

};

#endif
