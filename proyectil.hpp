#ifndef __PROYECTIL__
#define __PROYECTIL__

#include "lib/object.hpp"

class Proyectil : public Ros::Object{
    private:
        bool Girando;
        float AnguloAnterior;
        float AnguloFinal;
    public:
        virtual void Draw(void);
        virtual void EventHandler(void);
        Proyectil(std::string pId, Ros::Application *pApp);
        Proyectil(std::string pId);
        virtual ~Proyectil();
};

#endif
