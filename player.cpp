#include "lib/animation.hpp"
#include "player.hpp"
#include "enemigo.hpp"
#include "lib/pantalla.hpp"
#include "mipantalla.hpp"

const int VELOCIDAD_NAVE = 10;
const int VELOCIDAD_DISPARO = 25;
const int VELOCIDAD_DISPARO_MISIL = 15;

long int DISPARO_ID = 0;

void Player::AddLife(int l){

	Life += l;

	if(Life < 0){
		Life = 0;
		Vivo = false;
		CrearExplosion(this->getX(), this->getY());
	}else if(Life > 100){
		Life = 100;
	}

}

int Player::GetLife(void){
	return Life;
}

int Player::GetMuniciones(void){
    return Municiones;
}

void Player::BuscarPremio(void){

    MiPantalla *Pantalla = static_cast<MiPantalla*>(this->App->GetPantallaActiva());

    for(int i=0; i<Pantalla->PremioDisparo1.size(); i++){
        Ros::Object *itemPremio = Pantalla->PremioDisparo1.Get(i);
        if(itemPremio->CheckCollision(this) == true){
            Pantalla->PremioDisparo1.DeleteById(itemPremio->getId());
            this->App->PlaySound("sound.premio", 100, false);
            TipoDisparo = TIPO_PREMIO_DISPARO2;
            Municiones = 100;
            break;
        }
    }

    for(int i=0; i<Pantalla->PremioDisparo2.size(); i++){
        Ros::Object *itemPremio = Pantalla->PremioDisparo2.Get(i);
        if(itemPremio->CheckCollision(this) == true){
            Pantalla->PremioDisparo2.DeleteById(itemPremio->getId());
            this->App->PlaySound("sound.premio", 100, false);
            TipoDisparo = TIPO_PREMIO_DISPARO3;
            Municiones = 100;
            break;
        }
    }

    for(int i=0; i<Pantalla->PremioDisparoMisil.size(); i++){
        Ros::Object *itemPremio = Pantalla->PremioDisparoMisil.Get(i);
        if(itemPremio->CheckCollision(this) == true){
            Pantalla->PremioDisparoMisil.DeleteById(itemPremio->getId());
            this->App->PlaySound("sound.premio", 100, false);
            TipoDisparo = TIPO_PREMIO_DISPARO_MISIL;
            Municiones = 100;
            break;
        }
    }

}

void Player::Disparar(void){

	if(Vivo == false){
		return;
	}

	DISPARO_ID++;

	Ros::Object *itemDisparo = Disparos.Add("Nave.Disparo" + std::to_string(DISPARO_ID));

	itemDisparo->setX(this->getX());
	itemDisparo->setY(this->getY());
	itemDisparo->setAngle(this->getAngle());

	switch(TipoDisparo){
        case TIPO_PREMIO_DISPARO1:
            itemDisparo->setImage(this->App->GetImage("img.disparo.1"));
            break;
        case TIPO_PREMIO_DISPARO2:
            itemDisparo->setImage(this->App->GetImage("img.disparo.2"));
            Municiones-=5;
            break;
        case TIPO_PREMIO_DISPARO3:
            itemDisparo->setImage(this->App->GetImage("img.disparo.3"));
            Municiones-=5;
            break;
        case TIPO_PREMIO_DISPARO_MISIL:
            itemDisparo->setImage(this->App->GetImage("img.disparo.4"));
            Municiones-=5;
            break;
	}

    if(Municiones < 0){
        TipoDisparo = TIPO_PREMIO_DISPARO1;
        Municiones = 0;
    }

	itemDisparo->setApplication(this->App);

	this->App->PlaySound("sound.disparo", 80, false);

}

void Player::DeleteDisparos(void){

	std::vector<std::string> idToDelete;

	if(Disparos.size() == 0){
		DISPARO_ID = 0;
		return;
	}

	//Buscamos los disparos que se salieron de la pantalla para
	//guardar sus ids y despues poder borrarlos.

	for(int i=0; i<Disparos.size(); i++){
		Ros::Object *itemDisparo = Disparos.Get(i);
		if(itemDisparo->getY() < 0
		|| itemDisparo->getX() < 0
		|| itemDisparo->getY() > this->App->GetScreenHeight()
		|| itemDisparo->getX() > this->App->GetScreenWidth()
		){
			idToDelete.push_back(itemDisparo->getId());
		}
	}

	for (int i = 0; i < idToDelete.size(); ++i){
		Disparos.DeleteById(idToDelete[i]);
	}

}

void Player::MoverDisparos(void){

	if(Vivo == false){
		return;
	}

    MiPantalla *Pantalla = static_cast<MiPantalla*>(this->App->GetPantallaActiva());

    std::vector<std::string> idToDelete;
    std::vector<std::string> idToDeleteEnemigo;

	//Mover los disparos
	for(int i=0; i<Disparos.size(); i++){
		Ros::Object *itemDisparo = Disparos.Get(i);

		if(itemDisparo->getImageId() == "img.disparo.4"){
            itemDisparo->followObject(Pantalla->Enemigos.Get(0), VELOCIDAD_DISPARO_MISIL);
		}else{
		    itemDisparo->moveByAngle(VELOCIDAD_DISPARO);
		}

		for(int x=0; x<Pantalla->Enemigos.size(); x++){
            if(itemDisparo->CheckCollision(Pantalla->Enemigos.Get(x)) == true){
                //El enemigo es alcanzado por un disparo.
                //Hay que borrar el disparo y descontarle vida al enemigo

                Enemigo *itemEnemigo = Pantalla->Enemigos.Get(x);

                idToDelete.push_back(itemDisparo->getId());

                if(itemEnemigo->Vivo == false){continue;}

                if(itemDisparo->getImageId() == "img.disparo.4"){
                    itemEnemigo->addVida(-100);
                }else if(itemDisparo->getImageId() == "img.disparo.3"){
                    itemEnemigo->addVida(-50);
                    Pantalla->SumaPuntos(1);
                }else if(itemDisparo->getImageId() == "img.disparo.2"){
                    itemEnemigo->addVida(-34);
                    Pantalla->SumaPuntos(4);
                }else{
                    itemEnemigo->addVida(-20);
                    Pantalla->SumaPuntos(6);
                }

                if(itemEnemigo->getVida() <= 0){
                	itemEnemigo->Vivo = false;
                	idToDeleteEnemigo.push_back(itemEnemigo->getId());
                	CrearExplosion(itemEnemigo->getX(), itemEnemigo->getY());
                	Pantalla->SumaPuntos(10);
                	if(this->App->doIt(30, 100) == true){
                        Pantalla->CrearPremio(itemEnemigo->getX(), itemEnemigo->getY());
                	}
                }

            }
		}

	}

	//borrar los disparos
	for(int i=0; i<idToDelete.size(); i++){
        Disparos.DeleteById(idToDelete[i]);
	}

	//borrar los enemigos muertos
	for(int i=0; i<idToDeleteEnemigo.size(); i++){
		Pantalla->Enemigos.DeleteById(idToDeleteEnemigo[i]);
	}

}

void Player::Draw(void){

	//dibujar los disparos...

	for(int i=0; i<Disparos.size(); i++){
		Ros::Object *itemDisparo = Disparos.Get(i);
		itemDisparo->Draw();
	}

	if(Vivo == false){
		return;
	}

	Ros::Object::Draw();

}

void Player::CrearExplosion(int x, int y){

	MiPantalla *Pantalla = static_cast<MiPantalla*>(this->App->GetPantallaActiva());

	Ros::Animation itemExplosion("explosion.Nave.GameOver", 96, this->App);

	itemExplosion.setImage(this->App->GetImage("img.explosion"));
	itemExplosion.setX(x);
	itemExplosion.setY(y);
	itemExplosion.Begin();

	Pantalla->Explosiones.Add(itemExplosion);

	this->App->PlaySound("sound.explosion", 40, false);

}

void Player::BuscarColision(void){

	if(Vivo == false){
		return;
	}

	MiPantalla *Pantalla = static_cast<MiPantalla*>(this->App->GetPantallaActiva());

	for (int i = 0; i < Pantalla->Enemigos.size(); ++i)
	{
		if(Pantalla->Enemigos.Get(i)->CheckCollision(this) == true){
			AddLife(-5);
		}
	}

}

void Player::EventHandler(){

	MiPantalla *Pantalla = static_cast<MiPantalla*>(this->App->GetPantallaActiva());

	MoverDisparos();
	DeleteDisparos();
	BuscarColision();
	BuscarPremio();

	Pantalla->CrearEnemigos();

	if(Pantalla->isKeyActive[Ros::keySpace] == true){
		if(CanShoot == true){
			Disparar();
			CanShoot = false;
		}
	}else{
		CanShoot = true;
	}

	if (Pantalla->isKeyActive[Ros::keyLeft] == true){
		this->changeAngle(0.05f);
	}

	if (Pantalla->isKeyActive[Ros::keyRight] == true){
		this->changeAngle(-0.05f);
	}

	if (Pantalla->isKeyActive[Ros::keyUp] == true){
		this->setImage(this->App->GetImage("img.Player1On"));
		this->moveByAngle(VELOCIDAD_NAVE);
	}else{
		this->setImage(this->App->GetImage("img.Player1Off"));
	}

	if (Pantalla->isKeyActive[Ros::keyDown] == true){
		this->moveByAngle(-VELOCIDAD_NAVE);
	}

	if(this->getX() > this->App->GetScreenWidth()){
		this->setX(this->App->GetScreenWidth());
	}

	if(this->getY() > this->App->GetScreenHeight()){
		this->setY(this->App->GetScreenHeight());
	}

	if(this->getY() < 0){
		this->setY(0);
	}

	if(this->getX() < 0){
		this->setX(0);
	}

}

Player::Player(std::string pId) : Ros::Object(pId){
    angle = 3.14/2;
	CanShoot = true;
	Vivo = true;
	TipoDisparo = TIPO_PREMIO_DISPARO1;
	Life = 100;
    Municiones = 0;
}

Player::Player(std::string pId, Ros::Application *pApp) : Ros::Object(pId, pApp){
    angle = 3.14/2;
	CanShoot = true;
	Vivo = true;
	TipoDisparo = TIPO_PREMIO_DISPARO1;
	Life = 100;
    Municiones = 0;
}

Player::~Player(){

}
