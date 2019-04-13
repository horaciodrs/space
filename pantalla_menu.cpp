#include <iostream>
#include <string>
#include <vector>

#include "pantalla_menu.hpp"
#include "lib/object.hpp"

const int MAX_ESTRELLAS = 200;

void PantallaMenu::CrearOpciones(void){

	Ros::Object *itemOpcion;

	itemOpcion = Opciones.Add("Opciones.Jugar");

	itemOpcion->setY(300);
	itemOpcion->setX(100);
	itemOpcion->setImage(App->GetImage("img.Opciones.Jugar"));
	itemOpcion->setApplication(App);

}

void PantallaMenu::DibujarOpciones(void){

	this->Opciones.Get("Opciones.Jugar")->Draw();

}

void PantallaMenu::CrearEstrellas(void){

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

void PantallaMenu::MoverEstrellas(void){

	for (int i = 0; i < Estrellas.size(); ++i)
	{
		Ros::Object *itemEstrella = Estrellas.Get(i);

		itemEstrella->changeY(1);

		if(itemEstrella->getY() > App->GetScreenHeight()){
			itemEstrella->setY(-5);
		}
	}

}

void PantallaMenu::DibujarEstrellas(void){

	for (int i = 0; i < Estrellas.size(); ++i)
	{

		Ros::Object *itemEstrella = Estrellas.Get(i);

		itemEstrella->Draw();

	}

}

void PantallaMenu::Init(void){

	CrearEstrellas();
	CrearOpciones();

}

void PantallaMenu::EventHandler(void){
	MoverEstrellas();
}

void PantallaMenu::Render(void){

	DibujarEstrellas();
	DibujarOpciones();

	this->App->EscribirTexto("ttf.zerovelo", "SPACE", 40, this->App->GetScreenWidth()/2 - 100, 20);
	this->App->EscribirTexto("ttf.zerovelo", "SHOTTER", 50,  this->App->GetScreenWidth()/2 - 180, 80);

}

void PantallaMenu::OnWindowResize(void){
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

PantallaMenu::PantallaMenu(std::string pId, Ros::Application *pApp) : Pantalla(pId, pApp){

}

PantallaMenu::~PantallaMenu(){

}
