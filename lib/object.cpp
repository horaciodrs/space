#include "object.hpp"

namespace Ros{

	void Object::moveByAngle(int Velocidad){

		calculateDiferencial(Velocidad);

		changeX(dx);
		changeY(dy);

	}

	void Object::calculateDiferencial(int Velocidad){

	    dy = -Velocidad * sin(angle);
	    dx = Velocidad * cos(angle);

	}

	void Object::changeAngle(float increment){

		angle += increment;

		if(angle > 6.28f){
			angle = 0.f;
		}else if(angle < 0.f){
			angle = 6.28f;
		}

	}

	float Object::getDistance(Ros::Object *AnotherObject){
		return sqrt(pow(x-AnotherObject->getX(), 2) + pow(y-AnotherObject->getY(), 2));
	}

	void Object::followObject(Ros::Object *AnotherObject, int Velocidad){

	    int enemigoX = AnotherObject->getX() + AnotherObject->getW()/2;
	    int enemigoY = AnotherObject->getY() + AnotherObject->getH()/2;
        float CO = std::abs(getX() - enemigoX);
        float CA = std::abs(getY() - enemigoY);
	    int dxSigno = 1;
	    int dySigno = 1;

	    if(CA != 0){

	        angle = atan2(CO, CA);

	        int misilDX = Velocidad * sin(angle);
	        int misilDY = Velocidad * cos(angle);
	        dx = misilDX;
	        dy = misilDY;

	        if(enemigoX > getX()
	        && enemigoY < getY()){
	            //si esta en el primer cuadrante
	            angle = 1*angle;
	        }else if(enemigoX < getX()
	        && enemigoY < getY()){
	            //si esta en el segundo cuadrante
	            angle = -1*angle;
	        }else if(enemigoX < getX()
	        && enemigoY > getY()){
	            //si esta en el tercer cuadrante.
	            angle = 3.14+1*angle;
	        }else if(enemigoX > getX()
	        && enemigoY > getY()){
	            //si esta en el cuarto cuadrante.
	            angle = 3.14 - angle;
	        }

	    }

	    if(enemigoX > getX()){dxSigno = -1;}
	    if(enemigoX < getX()){dxSigno = 1;}

	    if(enemigoY > getY()){dySigno = -1;}
	    if(enemigoY < getY()){dySigno = 1;}

	    changeX(-dxSigno*dx);
	    changeY(-dySigno*dy);

	}

	void Object::changeX(int increment){
		x += increment;
	}

	void Object::changeY(int increment){
		y += increment;
	}

	void Object::EventHandler(sf::Event *event){
		//Esta funcion es virtual para poder sobreescribirla
		//en las clases que hereden a object.
	}

	bool Object::CheckCollision(Ros::Object *AnotherObject){

		if(x + getW()/2 > AnotherObject->getX() && x + getW()/2 < AnotherObject->getX() + AnotherObject->getW()){
			if(y + getH()/2 > AnotherObject->getY() && y + getH()/2 < AnotherObject->getY() + AnotherObject->getH()){
				return true;
			}
		}

		return false;

	}

	void Object::setImage(Ros::Image *pImage){

		Image = pImage;

        w = Image->getWidth();
		h = Image->getHeight();

	}

	void Object::Draw(int x, int y, int l, int t, int w, int h){

		if(angle == 0){
			this->Image->Draw(x, y, l, t, w, h);
		}else{
			this->Image->Draw(x, y, angle);
		}

	}

	void Object::Draw(int pX, int pY){

		x = pX;
		y = pY;

		Draw();

	}

	void Object::Draw(){
		this->Image->Draw(x, y, -angle);
	}

	Object::Object(std::string pId) : Id(pId) {
		angle = 0;
	}

	Object::Object(std::string pId, Ros::Application *pApp) : Id(pId), App(pApp) {
		angle = 0;
	}

}
