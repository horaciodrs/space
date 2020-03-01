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

    Piloto1 = new Ros::Object("Piloto1", App);
	Piloto1->setImage(App->GetImage("img.piloto0"));
    Piloto1->setX(200);
	Piloto1->setY(300);

    Piloto2 = new Ros::Object("Piloto2", App);
	Piloto2->setImage(App->GetImage("img.piloto1"));
    Piloto2->setX(350);
	Piloto2->setY(300);

    Piloto3 = new Ros::Object("Piloto3", App);
	Piloto3->setImage(App->GetImage("img.piloto2"));
    Piloto3->setX(500);
	Piloto3->setY(300);

    Piloto4 = new Ros::Object("Piloto4", App);
	Piloto4->setImage(App->GetImage("img.piloto3"));
    Piloto4->setX(650);
	Piloto4->setY(300);

    PilotoSelectionLight = new Ros::Object("PilotoSelectionLight", App);
	PilotoSelectionLight->setImage(App->GetImage("img.piloto.selection.light"));
    PilotoSelectionLight->setX(200);
	PilotoSelectionLight->setY(300);

    CrearEstrellas();
	
}

void PantallaPiloto::Salir(std::string pPantallaId){

    this->Running = false;
    this->App->SetPantallaActiva(pPantallaId);

}

void PantallaPiloto::EventHandler(void){
 
	
    MoverEstrellas();

    //Procesa el evento tecla DOWN.
    
    if(this->isKeyActive[Ros::keyDown]){
        if(this->CanProcessDown == true){
            this->SelectedOption++;
            this->CanProcessDown = false;
        }
    }else{
        this->CanProcessDown = true;
    }

    //Procesa el evento tecla UP.

    if(this->isKeyActive[Ros::keyUp]){
        if(this->CanProcessUp == true){
            this->SelectedOption--;
            this->CanProcessUp = false;
        }
    }else{
        this->CanProcessUp = true;
    }

    if(this->SelectedOption > 3){
        this->SelectedOption = 0;
    }

    if(this->SelectedOption < 0){
        this->SelectedOption = 3;
    }

    switch(this->SelectedOption){
        case 0:
            this->PilotoSelectionLight->setX(200);
            break;
        case 1:
            this->PilotoSelectionLight->setX(350);
            break;
        case 2:
            this->PilotoSelectionLight->setX(500);
            break;
        case 3:
            this->PilotoSelectionLight->setX(650);
            break;
    }

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

    Piloto1->Draw();
    Piloto2->Draw();
    Piloto3->Draw();
    Piloto4->Draw();

    PilotoSelectionLight->Draw();

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
    this->CanProcessDown = true;
    this->CanProcessUp = true;
    this->SelectedOption = 0;

}

PantallaPiloto::~PantallaPiloto(){
    End();
}
