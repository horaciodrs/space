#include "enemigo.hpp"
#include "lib/pantalla.hpp"
#include "mipantalla.hpp"

const int VELOCIDAD_ENEMIGO = 3;
const int MAX_DISPAROS_ENEMIGO = 5;

void Enemigo::Draw(void){

    Ros::Object::Draw();

}

void Enemigo::FlyingV12(void){

    //Esta funcion hace que el enemigo se mueva en V
    //desde el cuadrante 2 hacia el cuadrante 1.

    MiPantalla *Pantalla = static_cast<MiPantalla*>(this->App->GetPantallaActiva());

    if(Sentido == ENEMIGO_STATE_BAJANDO){

        //se mueve desde arriba hacia abajo

        if(this->getY() > this->App->GetScreenHeight() - this->getH()*2){

            if(Girando == false){
                Girando = true;
                AnguloAnterior = angle;
                AnguloFinal = 3*3.14/4;
            }else{
                changeAngle(-0.03f);
                if(angle < AnguloFinal){
                    angle = AnguloFinal;
                    Sentido = ENEMIGO_STATE_SUBIENDO;
                    Girando = false;
                }
            }

        }

    }else if(Sentido == ENEMIGO_STATE_SUBIENDO){

        if(this->getY() < this->getH()*2){

            if(Girando == false){
                Girando = true;
                AnguloAnterior = angle;
                AnguloFinal = 0.f;
            }else{
                changeAngle(-0.05f);
                if(angle == AnguloFinal || angle == 6.28f){
                    angle = AnguloFinal;
                    Sentido = ENEMIGO_STATE_REINICIANDO;
                    Girando = false;
                }
            }

        }

    }else if(Sentido == ENEMIGO_STATE_REINICIANDO){

        if(this->getX() > this->App->GetScreenWidth() - getW()*2){

            if(Girando == false){
                Girando = true;
                AnguloAnterior = angle;
                AnguloFinal = 5*3.14/4;
            }else{
                changeAngle(-0.05f);
                if(angle < AnguloFinal){
                    angle = AnguloFinal;
                    Sentido = ENEMIGO_STATE_BAJANDO;
                    Girando = false;
                }
            }

        }

    }

    this->moveByAngle(VELOCIDAD_ENEMIGO);

    if(App->doIt(10, 1000) == true){
        if(Pantalla->GetCantidadDisparosEnemigo() < MAX_DISPAROS_ENEMIGO){
            Pantalla->CrearDisparoEnemigo(this->getX(), this->getY());
        }
    }

}

void Enemigo::FlyingV21(void){

    //Esta funcion hace que el enemigo se mueva en V
    //desde el cuadrante 2 hacia el cuadrante 1.

    MiPantalla *Pantalla = static_cast<MiPantalla*>(this->App->GetPantallaActiva());

    if(Sentido == ENEMIGO_STATE_BAJANDO){

        //se mueve desde arriba hacia abajo

        if(this->getY() > this->App->GetScreenHeight() - this->getH()*2){

            if(Girando == false){
                Girando = true;
                AnguloAnterior = angle;
                AnguloFinal = 3.14/4;
            }else{
                changeAngle(0.05f);
                if(angle > AnguloFinal && angle < 3.14/2){
                    angle = AnguloFinal;
                    Sentido = ENEMIGO_STATE_SUBIENDO;
                    Girando = false;
                }
            }

        }

    }else if(Sentido == ENEMIGO_STATE_SUBIENDO){

        if(this->getY() < this->getH()*2
        || this->getX() > this->App->GetScreenWidth() - this->getW()*2){

            if(Girando == false){
                Girando = true;
                AnguloAnterior = angle;
                AnguloFinal = 3.14f;
            }else{
                changeAngle(0.05f);
                if(angle > AnguloFinal){
                    angle = AnguloFinal;
                    Sentido = ENEMIGO_STATE_REINICIANDO;
                    Girando = false;
                }
            }

        }

    }else if(Sentido == ENEMIGO_STATE_REINICIANDO){

        if(this->getX() < this->getW()*2){

            if(Girando == false){
                Girando = true;
                AnguloAnterior = angle;
                AnguloFinal = 7*3.14/4;
            }else{
                changeAngle(0.05f);
                if(angle > AnguloFinal){
                    angle = AnguloFinal;
                    Sentido = ENEMIGO_STATE_BAJANDO;
                    Girando = false;
                }
            }

        }

    }

    this->moveByAngle(VELOCIDAD_ENEMIGO);

    if(App->doIt(10, 1000) == true){
        if(Pantalla->GetCantidadDisparosEnemigo() < MAX_DISPAROS_ENEMIGO){
            Pantalla->CrearDisparoEnemigo(this->getX(), this->getY());
        }
    }

}

void Enemigo::EventHandler(void){

    if(TipoMovimiento == ENEMIGO_TIPO_MOVIMIENTO_21){
        FlyingV21();
    }else if(TipoMovimiento == ENEMIGO_TIPO_MOVIMIENTO_12){
        FlyingV12();
    }


}

Enemigo::Enemigo(std::string pId) : Object(pId){
    AnguloAnterior = 0;
    AnguloFinal = 0;
    Girando = false;
    Vida = 100;
    Vivo = true;
}

Enemigo::Enemigo(std::string pId, Ros::Application *pApp) : Object(pId, pApp){
    AnguloAnterior = 0;
    AnguloFinal = 0;
    Girando = false;
    Vida = 100;
    Vivo = true;
}

Enemigo::~Enemigo()
{

}
