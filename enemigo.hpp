#ifndef ENEMIGO_H
#define ENEMIGO_H

#include "lib/object.hpp"
#include "player.hpp"

#define ENEMIGO_STATE_BAJANDO 1
#define ENEMIGO_STATE_SUBIENDO 2
#define ENEMIGO_STATE_REINICIANDO 3

#define ENEMIGO_TIPO_MOVIMIENTO_21 1
#define ENEMIGO_TIPO_MOVIMIENTO_12 2

class Enemigo : public Ros::Object{
    private:
        bool Girando;
        bool Vivo;
        float AnguloAnterior;
        float AnguloFinal;
        int Sentido;
        int Vida;
        int TipoMovimiento;
    public:
        friend class Player;
        void addVida(int p){Vida+=p;}
        int getVida(void){return Vida;}
        int getTipoMovimiento(void){return TipoMovimiento;}
        void setSentido(int p){Sentido = p;}
        void setTipoMovimiento(int t){TipoMovimiento = t;}
        void FlyingV21(void);
        void FlyingV12(void);
        void IniciarMovimiento(void);
        virtual void Draw(void);
        virtual void EventHandler(void);
        Enemigo(std::string pId);
        Enemigo(std::string pId, Ros::Application *pApp);
        virtual ~Enemigo();
};

#endif // ENEMIGO_H
