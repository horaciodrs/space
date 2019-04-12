#ifndef __GAME_OBJECT__
#define __GAME_OBJECT__

#include <iostream>
#include <math.h>
#include "image.hpp"

namespace Ros{

	class Application;

	class Object{

		protected:
			std::string Id;			//Id para colecion de Objectos.
			int x;					//Posicion x.
			int y;					//Posicion y.
			int w;					//Ancho del objeto.
			int h;					//Alto del objeto.
			int dx;
			int dy;
			float angle;			//Angulo de la imagen.
			Ros::Image *Image;		//Puntero al Asset;
			Ros::Application *App;	//Puntero a la aplicacion.
		public:
			/*SETTERS*/
			void setImage(Ros::Image *pImage);
			void setX(int pX){x = pX;}
			void setY(int pY){y = pY;}
			void setApplication(Ros::Application *pApp){App = pApp;}
			void setAngle(float pAngle){angle = pAngle;}
			/*GETTERS*/
			Ros::Image *getImage(void){return Image;}
			std::string getId(void){return Id;}
			std::string getImageId(void){return Image->getId();}
			int getX(){return x;}
			int getY(){return y;}
			int getW(){return w;}
			int getH(){return h;}
			float getAngle(){return angle;}
			float getDistance(Ros::Object *AnotherObject);
			/*CHANGE POSITION*/
			void changeX(int increment);
			void changeY(int increment);
			void changeAngle(float increment);
			void calculateDiferencial(int Velocidad);
			void moveByAngle(int Velocidad);
			bool CheckCollision(Ros::Object *AnotherObject);
			void followObject(Ros::Object *AnotherObject, int Velocidad);
			void Draw(int x, int y);
			void Draw(int x,int y,int l,int t,int w,int h);
			virtual void EventHandler(sf::Event *event);
			virtual void Draw();
			Object(std::string pId);
			Object(std::string pId, Ros::Application *pApp);
			virtual ~Object(){};

	};

}

#endif
