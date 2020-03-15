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

    for(int i=0; i < globalPilotos->size(); i++){
        Ros::Object *newPiloto = new Ros::Object("Piloto" + std::to_string(i));
        newPiloto->setApplication(App);
        newPiloto->setImage(App->GetImage(globalPilotos->Get(i)->getImgPiloto()));
        newPiloto->setX(200 + i*150);
        newPiloto->setY(300);

        imgPilotos.Add(*newPiloto);
    }

    PilotoSelectionLight = new Ros::Object("PilotoSelectionLight", App);
	PilotoSelectionLight->setImage(App->GetImage("img.piloto.selection.light"));
    PilotoSelectionLight->setX(200);
	PilotoSelectionLight->setY(300);

    CrearEstrellas();
	
}

void PantallaPiloto::Salir(std::string pPantallaId, int pSelectedPilot){

    PantallaMenu *pantallaMenu;

    this->Running = false;
    this->App->SetPantallaActiva(pPantallaId);

    pantallaMenu =  static_cast<PantallaMenu*>(this->App->GetPantallaActiva());

    pantallaMenu->setSelectedPilot(pSelectedPilot);

}

void PantallaPiloto::EventHandler(void){
 
	
    MoverEstrellas();

    //Procesa el evento tecla DOWN.
    
    if(this->isKeyActive[Ros::keyLeft]){
        if(this->CanProcessLeft == true){
            this->SelectedOption--;
            this->CanProcessLeft = false;
        }
    }else{
        this->CanProcessLeft = true;
    }

    //Procesa el evento tecla UP.

    if(this->isKeyActive[Ros::keyRight]){
        if(this->CanProcessRight == true){
            this->SelectedOption++;
            this->CanProcessRight = false;
        }
    }else{
        this->CanProcessRight = true;
    }

    if(this->SelectedOption > 3){
        this->SelectedOption = 0;
    }

    if(this->SelectedOption < 0){
        this->SelectedOption = 3;
    }

    //Resaltar el piloto seleccionado...
    this->PilotoSelectionLight->setX(200 + this->SelectedOption*150);

    //Procesa el evento tecla ESCAPE.
    
    if(this->isKeyActive[Ros::keyEscape]){
        if(this->CanProcessEscape == true){
            this->Salir("MenuScreen", this->SelectedOption);
            this->CanProcessEscape = false;
        }
    }else{
        this->CanProcessEscape = true;
    }

    //Procesa el evento tecla ENTER.
    
    if(this->isKeyActive[Ros::keyEnter]){
        if(this->CanProcessEnter == true){
            this->Salir("MenuScreen", this->SelectedOption);
            this->CanProcessEnter = false;
        }
    }else{
        this->CanProcessEnter = true;
    }

}

void PantallaPiloto::Render(void){

	DibujarEstrellas();

    for(int i=0; i<imgPilotos.size(); i++){
        imgPilotos.Get(i)->Draw();
    }

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
    this->CanProcessLeft = true;
    this->CanProcessRight = true;
    this->CanProcessEnter = true;
    this->SelectedOption = 0;

}

PantallaPiloto::~PantallaPiloto(){
    End();
}
