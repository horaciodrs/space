#include <iostream>
#include <string>
#include <vector>

#include "pantalla_piloto.hpp"
#include "lib/object.hpp"

const int MAX_ESTRELLAS = 200;


void PantallaPiloto::CrearEstrellas(void){

	bool tipoEstrella = false;

	std::string imgEstrella("img.estrella.1");

	for (int i=0; i<MAX_ESTRELLAS; i++) {
		Ros::Object *itemEstrella = Estrellas.Add("Fondo.Estrella." + std::to_string(i));

		if(itemEstrella == NULL){continue;}

		int vRandY = rand() % App->GetScreenHeight();
		int vRandX = rand() % App->GetScreenWidth();

		itemEstrella->setY(vRandY);
		itemEstrella->setX(vRandX);
		itemEstrella->setImage(App->GetImage(imgEstrella));
		itemEstrella->setApplication(App);

		if(tipoEstrella == false){
			tipoEstrella = true;
			imgEstrella = "img.estrella.2";
		}else{
			tipoEstrella = false;
			imgEstrella = "img.estrella.1";
		}

	}

}

void PantallaPiloto::MoverEstrellas(void){

	for (int i = 0; i < Estrellas.size(); ++i)
	{
		Ros::Object *itemEstrella = Estrellas.Get(i);

		itemEstrella->changeY(1);

		if(itemEstrella->getY() > App->GetScreenHeight()){
			itemEstrella->setY(-5);
		}
	}

}

void PantallaPiloto::DibujarEstrellas(void){

	for (int i = 0; i < Estrellas.size(); ++i)
	{

		Ros::Object *itemEstrella = Estrellas.Get(i);

		itemEstrella->Draw();

	}

}

void PantallaPiloto::Init(void){

    CrearEstrellas();
	
}

void PantallaPiloto::Salir(std::string pPantallaId){

    this->Running = false;
    this->App->SetPantallaActiva(pPantallaId);

}

void PantallaPiloto::EventHandler(void){
 
	
    MoverEstrellas();

    //Procesa el evento tecla ESCAPE.
    
    if(this->isKeyActive[Ros::keyEscape]){
        if(this->CanProcessEscape == true){
            this->Salir("MenuScreen");
            this->CanProcessEscape = false;
        }
    }else{
        this->CanProcessEscape = true;
    }

}

void PantallaPiloto::Render(void){

	DibujarEstrellas();

	this->App->EscribirTexto("ttf.zerovelo", "SPACE", 40, this->App->GetScreenWidth()/2 - 100, 20);
	this->App->EscribirTexto("ttf.zerovelo", "SHOTTER", 50,  this->App->GetScreenWidth()/2 - 180, 80);

}

void PantallaPiloto::OnWindowResize(void){
	for (int i = 0; i < Estrellas.size(); ++i)
	{
		Ros::Object *itemEstrella = Estrellas.Get(i);

		int vRandY = rand() % App->GetScreenHeight();
		int vRandX = rand() % App->GetScreenWidth();

		itemEstrella->setY(vRandY);
		itemEstrella->setX(vRandX);

		itemEstrella->changeY(1);

	}
}

void PantallaPiloto::End(){
    
}

PantallaPiloto::PantallaPiloto(std::string pId, Ros::Application *pApp) : Pantalla(pId, pApp){

    this->CanProcessEscape = true;

}

PantallaPiloto::~PantallaPiloto(){
    End();
}
