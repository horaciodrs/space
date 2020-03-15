#include <iostream>
#include <string>
#include <vector>

#include "pantalla_menu.hpp"
#include "lib/object.hpp"

const int MAX_ESTRELLAS = 200;


void PantallaMenu::DibujarOpciones(void){

    sf::Color textColor = sf::Color(255,255,255,255);
    sf::Color textColorSelected = sf::Color(255, 0, 0, 255);

    switch(this->SelectedOption){
    
        case 0:
            this->App->EscribirTexto("ttf.arcade", "Play",  30, 100, 230, textColorSelected);
            this->App->EscribirTexto("ttf.arcade", "Select Pilot",  30, 100, 270, textColor);
            this->App->EscribirTexto("ttf.arcade", "Historical Points",  30, 100, 310, textColor);
            this->App->EscribirTexto("ttf.arcade", "Exit",  30, 100, 350, textColor);
            break;
        case 1:
            this->App->EscribirTexto("ttf.arcade", "Play",  30, 100, 230, textColor);
            this->App->EscribirTexto("ttf.arcade", "Select Pilot",  30, 100, 270, textColorSelected);
            this->App->EscribirTexto("ttf.arcade", "Historical Points",  30, 100, 310, textColor);
            this->App->EscribirTexto("ttf.arcade", "Exit",  30, 100, 350, textColor);
            break;
         case 2:
            this->App->EscribirTexto("ttf.arcade", "Play",  30, 100, 230, textColor);
            this->App->EscribirTexto("ttf.arcade", "Select Pilot",  30, 100, 270, textColor);
            this->App->EscribirTexto("ttf.arcade", "Historical Points",  30, 100, 310, textColorSelected);
            this->App->EscribirTexto("ttf.arcade", "Exit",  30, 100, 350, textColor);
            break;
         case 3:
            this->App->EscribirTexto("ttf.arcade", "Play",  30, 100, 230, textColor);
            this->App->EscribirTexto("ttf.arcade", "Select Pilot",  30, 100, 270, textColor);
            this->App->EscribirTexto("ttf.arcade", "Historical Points",  30, 100, 310, textColor);
            this->App->EscribirTexto("ttf.arcade", "Exit",  30, 100, 350, textColorSelected);
            break;
 
    }

}

void PantallaMenu::CrearEstrellas(void){

	bool tipoEstrella = false;

	std::string imgEstrella("img.estrella.1");

    if(Estrellas.size() > 0){
        return;
    }

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

	this->SelectedOption = 0;
    this->CanProcessDown = true;
    this->CanProcessUp = true;
    this->CanProcessOption = true;

    CrearEstrellas();
	
}

void PantallaMenu::Salir(std::string pPantallaId){

    this->Running = false;
    this->App->SetPantallaActiva(pPantallaId);

    if(pPantallaId == "MainScreen"){
        MiPantalla *pantallaPrincipal;
        pantallaPrincipal =  static_cast<MiPantalla*>(this->App->GetPantallaActiva());
        pantallaPrincipal->setSelectedPilot(SelectedPilot);
        App->StopSound("sound.MusicMenuPiloto");
        App->PlaySound("sound.Music", 30, true);
    }
}

void PantallaMenu::EventHandler(void){
 
	
    MoverEstrellas();

    //Procesa el evento tecla DOWN.
    
    if(this->isKeyActive[Ros::keyDown]){
        if(this->CanProcessDown == true){
            this->SelectedOption++;
            this->CanProcessDown = false;
            App->PlaySound("sound.menu_item", 30, false);
        }
    }else{
        this->CanProcessDown = true;
    }

    //Procesa el evento tecla UP.

    if(this->isKeyActive[Ros::keyUp]){
        if(this->CanProcessUp == true){
            this->SelectedOption--;
            this->CanProcessUp = false;
            App->PlaySound("sound.menu_item", 30, false);
        }
    }else{
        this->CanProcessUp = true;
    }

    //Corrige la opción elegida en caso de que haga falta.

    if(this->SelectedOption > 3){
        this->SelectedOption = 0;
    }

    if(this->SelectedOption < 0){
        this->SelectedOption = 3;
    }

    //Procesa el evento tecla ENTER

    if(this->isKeyActive[Ros::keyEnter]){
        if(this->CanProcessOption == true){
            
            //procesar opcion elegida...
            switch(this->SelectedOption){
                case 0:
                    this->Salir("MainScreen");
                    break;
                case 1:
                    this->Salir("PilotoScreen");
                    break;
                case 3:
                    this->Salir("");
                    break; 
            }

            App->PlaySound("sound.menu_item_selected", 30, false);

            this->CanProcessOption = false;
        }
    }else{
        this->CanProcessOption = true;
    }


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

void PantallaMenu::End(){
    
}

PantallaMenu::PantallaMenu(std::string pId, Ros::Application *pApp) : Pantalla(pId, pApp){

    this->SelectedOption = 0;
    this->CanProcessDown = true;
    this->CanProcessUp = true;
    this->CanProcessOption = true;

}

PantallaMenu::~PantallaMenu(){
    End();
}
