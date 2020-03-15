#include <iostream>
#include <string>
#include <vector>

#include "pantalla_piloto.hpp"
#include "lib/object.hpp"

const int MAX_ESTRELLAS = 200;
const int HEIGHT_POWER_BARS = 15;

void PantallaPiloto::CrearEstrellas(void){

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

void PantallaPiloto::resetSkills(void){
    skillEscudo->setSize(sf::Vector2f(1, HEIGHT_POWER_BARS));
    skillPower->setSize(sf::Vector2f(1, HEIGHT_POWER_BARS));
    skillVelocidad->setSize(sf::Vector2f(1, HEIGHT_POWER_BARS));

    this->mostrandoSkills = true;
    this->terminoEscudo = false;
    this->terminoPower = false;
    this->terminoVelocidad = false;

}

void PantallaPiloto::mostrarSkills(void){

    int maxWidh = 700;
    int maxWidthEscudo = (int) globalPilotos->Get(SelectedOption)->getEscudo() * maxWidh /100;       //Indica hasta donde crece la barra indicadora.
    int maxWidthVelocidad = (int) globalPilotos->Get(SelectedOption)->getVelocidad() * maxWidh /100;
    int maxWidthPower = (int) globalPilotos->Get(SelectedOption)->getPower() * maxWidh /100;

    if(mostrandoSkills == true){

        this->CanProcessLeft = false;
        this->CanProcessRight = false;

        sf::Vector2f currentWidthEscudo = skillEscudo->getSize();
        sf::Vector2f currentWidthVelocidad = skillVelocidad->getSize();
        sf::Vector2f currentWidthPower = skillPower->getSize();

        int newWidthEscudo = 0;
        int newWidthVelocidad = 0;
        int newWidthPower = 0;

        if((currentWidthEscudo.x <= maxWidthEscudo) && (terminoEscudo == false)){
            newWidthEscudo = currentWidthEscudo.x += 40;
        }else{
            terminoEscudo = true;
            newWidthEscudo = maxWidthEscudo;
        }

        if((currentWidthVelocidad.x <= maxWidthVelocidad) && (terminoVelocidad == false)){
            newWidthVelocidad = currentWidthVelocidad.x += 40;
        }else{
            terminoVelocidad = true;
            newWidthVelocidad = maxWidthVelocidad;
        }

        if((currentWidthPower.x <= maxWidthPower) && (terminoPower == false)){
            newWidthPower = currentWidthPower.x += 40;
        }else{
            terminoPower = true;
            newWidthPower = maxWidthPower;
        }

        if((terminoVelocidad == true)  &&(terminoPower == true) &&(terminoEscudo == true)){
            mostrandoSkills = false;
        }

        skillEscudo->setSize(sf::Vector2f(newWidthEscudo, HEIGHT_POWER_BARS));
        skillVelocidad->setSize(sf::Vector2f(newWidthVelocidad, HEIGHT_POWER_BARS));
        skillPower->setSize(sf::Vector2f(newWidthPower, HEIGHT_POWER_BARS));

    }

    this->App->GetRenderWindow()->draw(*skillEscudo);
    this->App->GetRenderWindow()->draw(*skillVelocidad);
    this->App->GetRenderWindow()->draw(*skillPower);

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

    skillEscudo = new sf::RectangleShape(sf::Vector2f(1, 1));
    skillPower = new sf::RectangleShape(sf::Vector2f(1, 1));
    skillVelocidad = new sf::RectangleShape(sf::Vector2f(1, 1));

    skillEscudo->setSize(sf::Vector2f(1, HEIGHT_POWER_BARS));
    skillEscudo->setPosition(sf::Vector2f(150, 400));
    skillEscudo->setFillColor(sf::Color(255, 255, 255, 180));

    skillVelocidad->setSize(sf::Vector2f(1, HEIGHT_POWER_BARS));
    skillVelocidad->setPosition(sf::Vector2f(150, 435));
    skillVelocidad->setFillColor(sf::Color(255, 255, 255, 180));

    skillPower->setSize(sf::Vector2f(1, HEIGHT_POWER_BARS));
    skillPower->setPosition(sf::Vector2f(150, 470));
    skillPower->setFillColor(sf::Color(255, 255, 255, 180));

    CrearEstrellas();

    resetSkills();
	
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
            this->resetSkills();
            App->PlaySound("sound.menu_item", 30, false);
        }
    }else{
        this->CanProcessLeft = true;
    }

    //Procesa el evento tecla UP.

    if(this->isKeyActive[Ros::keyRight]){
        if(this->CanProcessRight == true){
            this->SelectedOption++;
            this->CanProcessRight = false;
            this->resetSkills();
            App->PlaySound("sound.menu_item", 30, false);
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
            App->PlaySound("sound.menu_item_selected", 30, false);
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

    mostrarSkills();

    PilotoSelectionLight->Draw();

	this->App->EscribirTexto("ttf.zerovelo", "SPACE", 40, this->App->GetScreenWidth()/2 - 100, 20);
	this->App->EscribirTexto("ttf.zerovelo", "SHOTTER", 50,  this->App->GetScreenWidth()/2 - 180, 80);

    this->App->EscribirTexto("ttf.arcade", "ESCUDO", 14, 80, 400);
    this->App->EscribirTexto("ttf.arcade", "VELOCIDAD", 14, 55, 435);
    this->App->EscribirTexto("ttf.arcade", "ATAQUE", 14, 80, 470);

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
    this->mostrandoSkills = false;
    this->terminoEscudo = true;
    this->terminoPower = true;
    this->terminoVelocidad = true;
    this->SelectedOption = 0;

}

PantallaPiloto::~PantallaPiloto(){
    End();
}
