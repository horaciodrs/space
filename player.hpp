#ifndef __PLAYER__
#define __PLAYER__

#include "lib/object_manager.hpp"
#include "lib/object.hpp"
#include "enemigo.hpp"

class Player : public Ros::Object{
	private:
		bool CanShoot;
		bool Vivo;
		int TipoDisparo;
        int Municiones;
		int Life;
		ObjectManager<Ros::Object> Disparos;
		void Disparar(void);
		void MoverDisparos(void);
		void DeleteDisparos(void);
		void BuscarColision(void);
		void BuscarPremio(void);
		void CrearExplosion(int x, int y);
    public:
    	void AddLife(int);
    	int GetLife(void);
        int GetMuniciones(void);
    	virtual void Draw(void);
		virtual void EventHandler();
        Player(std::string pId);
        Player(std::string pId, Ros::Application *pApp);
        ~Player();

};

#endif
