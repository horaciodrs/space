#include "proyectil.hpp"

void Proyectil::Draw(void){

    Ros::Object::Draw();

}

void Proyectil::EventHandler(void){

    if(Girando == false){
        Girando = true;
        angle = 0;
        AnguloFinal = angle + 3.14;
    }else{

        if(angle >= AnguloFinal){
            //angle = AnguloFinal;
            angle += 0.01f;
            //Girando = false;
        }else{
            angle += 0.03f;
        }

    }

    moveByAngle(3);

}

Proyectil::Proyectil(std::string pId, Ros::Application *pApp) : Ros::Object(pId, pApp){
    Girando = false;
}

Proyectil::Proyectil(std::string pId) : Ros::Object(pId){
    Girando = false;
}

Proyectil::~Proyectil(){

}
