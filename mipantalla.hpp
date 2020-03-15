#ifndef __MI_PANTALLA_HPP__
#define __MI_PANTALLA_HPP__

#include "lib/object_manager.hpp"
#include "lib/object.hpp"
#include "lib/animation.hpp"
#include "lib/pantalla.hpp"
#include "player.hpp"
#include "enemigo.hpp"
#include "proyectil.hpp"
#include "piloto.hpp"

#define TIPO_PREMIO_DISPARO1 1
#define TIPO_PREMIO_DISPARO2 2
#define TIPO_PREMIO_DISPARO3 3
#define TIPO_PREMIO_DISPARO_MISIL 4

class MiPantalla : public Ros::Pantalla{
	private:
		int SelectedPilot;
		int Puntos;
        Player *Nave;
		Ros::Object *imgSelectedPilot;
        ObjectManager<Enemigo> Enemigos;
		ObjectManager<Ros::Object> Estrellas;
		ObjectManager<Ros::Object> PremioDisparo1;
		ObjectManager<Ros::Object> PremioDisparo2;
		ObjectManager<Ros::Object> PremioDisparoMisil;
		ObjectManager<Ros::Animation> Explosiones;
		ObjectManager<Proyectil> DisparosEnemigo;
		Ros::Object *Background;
		Ros::Object *Lifebar;
        Ros::Object *WeaponBar;
        bool CanProcessEscape;
	public:
		ObjectManager<Piloto> *globalPilotos;
	    friend class Player;
	    friend class Enemigo;
		void setSelectedPilot(int pilot){SelectedPilot = pilot;}
		void setGlobalPilotos(ObjectManager<Piloto> *auxPilotos){globalPilotos = auxPilotos;}
	    int GetCantidadDisparosEnemigo(void);
	    void SumaPuntos(int p);
		void MoverEstrellas(void);
		void MoverPremios(void);
		void MoverDisparoEnemigo(void);
		void CrearEstrellas(void);
		void CrearEnemigos(void);
		void CrearPremio(int x, int y);
		void CrearDisparoEnemigo(int x, int y);
		void DibujarEstrellas(void);
		void DibujarLife(void);
        void DibujarWeaponBar(void);
		void DibujarPremios(void);
		void DibujarDisparoEnemigo(void);
		void BorrarExplosionesInactivas(void);
		void BorrarPremiosInactivos(void);
		void BorrarDisparoEnemigosInactivos(void);
        void Init(void);
		void Render(void);
		void EventHandler();
        void Salir(std::string pPantallaId);
		void OnWindowResize(void);
        void End(void);
		MiPantalla(std::string pId, Ros::Application *pApp);
		~MiPantalla();
};

#endif
