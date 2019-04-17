#include <iostream>
#include <string>
#include <vector>
#include "mipantalla.hpp"
#include "lib/object.hpp"

const int MAX_ESTRELLAS = 200;
const int MAX_ENEMIGOS = 6;
const int VELOCIDAD_PREMIOS = 2;

long int DISPARO_ENEMIGO_ID = 0;

int MiPantalla::GetCantidadDisparosEnemigo(void){
    return DisparosEnemigo.size();
}

void MiPantalla::SumaPuntos(int p){

    Puntos += p;

}

void MiPantalla::BorrarDisparoEnemigosInactivos(void){

    std::vector<std::string> idDeleteProyectiles;

    for(int i=0; i<DisparosEnemigo.size(); i++){
        if(DisparosEnemigo.Get(i)->getY() > App->GetScreenHeight()
        || DisparosEnemigo.Get(i)->getX() > App->GetScreenWidth()
        || DisparosEnemigo.Get(i)->getY() < 0
        || DisparosEnemigo.Get(i)->getX() < 0){
            idDeleteProyectiles.push_back(DisparosEnemigo.Get(i)->getId());
        }
        if(DisparosEnemigo.Get(i)->CheckCollision(Nave) == true){
            Nave->AddLife(-10);
            App->PlaySound("sound.lifequit", 50, false);
            
            idDeleteProyectiles.push_back(DisparosEnemigo.Get(i)->getId());
        }
    }

    for(int i=0; i<idDeleteProyectiles.size(); i++){
        DisparosEnemigo.DeleteById(idDeleteProyectiles[i]);
    }

}

void MiPantalla::MoverDisparoEnemigo(void){

    for(int i=0; i<DisparosEnemigo.size(); i++){
        DisparosEnemigo.Get(i)->EventHandler();

    }

}

void MiPantalla::DibujarDisparoEnemigo(void){

    for(int i=0; i<DisparosEnemigo.size(); i++){
        DisparosEnemigo.Get(i)->Draw();
    }

}

void MiPantalla::CrearDisparoEnemigo(int x, int y){

    Proyectil itemProyectil("Disparo.Enemigo." + std::to_string(DISPARO_ENEMIGO_ID), App);

    itemProyectil.setX(x);
    itemProyectil.setY(y);
    itemProyectil.setImage(App->GetImage("img.Disparo.Enemigo"));

    DisparosEnemigo.Add(itemProyectil);

    DISPARO_ENEMIGO_ID++;

}

void MiPantalla::CrearPremio(int x, int y){

    int posX = x;
    int posY = y;
    int randomTipo = rand() % 900;

    if(x <= 0){
        posX = rand() % App->GetScreenWidth();
    }

    Ros::Object itemPremio("premio", App);

    itemPremio.setX(posX);
    itemPremio.setY(posY);

    if(randomTipo >= 0 && randomTipo < 500){
        itemPremio.setImage(App->GetImage("img.Premio1"));
        PremioDisparo1.Add(itemPremio);
    }

    if(randomTipo >= 500 && randomTipo < 800){
        itemPremio.setImage(App->GetImage("img.Premio2"));
        PremioDisparo2.Add(itemPremio);
    }

    if(randomTipo >= 800 && randomTipo < 900){
        itemPremio.setImage(App->GetImage("img.Premio3"));
        PremioDisparoMisil.Add(itemPremio);
    }

}

void MiPantalla::MoverPremios(void){

    for(int i=0; i<PremioDisparo1.size(); i++){
        PremioDisparo1.Get(i)->changeY(VELOCIDAD_PREMIOS);
    }

    for(int i=0; i<PremioDisparo2.size(); i++){
        PremioDisparo2.Get(i)->changeY(VELOCIDAD_PREMIOS);
    }

    for(int i=0; i<PremioDisparoMisil.size(); i++){
        PremioDisparoMisil.Get(i)->changeY(VELOCIDAD_PREMIOS);
    }

}

void MiPantalla::DibujarPremios(void){

    for(int i=0; i<PremioDisparo1.size(); i++){
        PremioDisparo1.Get(i)->Draw();
    }

    for(int i=0; i<PremioDisparo2.size(); i++){
        PremioDisparo2.Get(i)->Draw();
    }

    for(int i=0; i<PremioDisparoMisil.size(); i++){
        PremioDisparoMisil.Get(i)->Draw();
    }

}

void MiPantalla::BorrarPremiosInactivos(void){

    std::vector<std::string> idDeleteDisparo1;
    std::vector<std::string> idDeleteDisparo2;
    std::vector<std::string> idDeleteDisparoMisil;

    for(int i=0; i<PremioDisparo1.size(); i++){
        if(PremioDisparo1.Get(i)->getY() > App->GetScreenHeight()){
            idDeleteDisparo1.push_back(PremioDisparo1.Get(i)->getId());
        }
    }

    for(int i=0; i<PremioDisparo2.size(); i++){
        if(PremioDisparo2.Get(i)->getY() > App->GetScreenHeight()){
            idDeleteDisparo2.push_back(PremioDisparo2.Get(i)->getId());
        }
    }

    for(int i=0; i<PremioDisparoMisil.size(); i++){
        if(PremioDisparoMisil.Get(i)->getY() > App->GetScreenHeight()){
            idDeleteDisparoMisil.push_back(PremioDisparoMisil.Get(i)->getId());
        }
    }

    for(int i=0; i<idDeleteDisparo1.size(); i++){
        PremioDisparo1.DeleteById(idDeleteDisparo1[i]);
    }

    for(int i=0; i<idDeleteDisparo2.size(); i++){
        PremioDisparo2.DeleteById(idDeleteDisparo2[i]);
    }

    for(int i=0; i<idDeleteDisparoMisil.size(); i++){
        PremioDisparoMisil.DeleteById(idDeleteDisparoMisil[i]);
    }

}

void MiPantalla::MoverEstrellas(void){

	for (int i = 0; i < Estrellas.size(); ++i)
	{
		Ros::Object *itemEstrella = Estrellas.Get(i);

		itemEstrella->changeY(1);

		if(itemEstrella->getY() > App->GetScreenHeight()){
			itemEstrella->setY(-5);
		}
	}

}

void MiPantalla::DibujarEstrellas(void){

	for (int i = 0; i < Estrellas.size(); ++i)
	{

		Ros::Object *itemEstrella = Estrellas.Get(i);

		itemEstrella->Draw();

	}

}

void MiPantalla::DibujarLife(void){

    Lifebar->setImage(App->GetImage("img.lifebar" + std::to_string(Nave->GetLife())));

}

void MiPantalla::CrearEstrellas(void){

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

void MiPantalla::CrearEnemigos(void){

	if(Enemigos.size() > 0){
		return;
	}

	for(int i=0; i<MAX_ENEMIGOS;i++){

        Enemigo itemEnemigo("Enemigo.A."+std::to_string(i), App);

        if(App->doIt(50, 100) == true){
            itemEnemigo.setTipoMovimiento(ENEMIGO_TIPO_MOVIMIENTO_12);
            itemEnemigo.setImage(App->GetImage("img.enemigo." + std::to_string(rand() % 3)));
            itemEnemigo.setX(App->GetScreenWidth() + 150*i + itemEnemigo.getW() * i);
            itemEnemigo.setY(-150*i - itemEnemigo.getH()* i);
            itemEnemigo.setAngle(5*3.14/4);
            itemEnemigo.setSentido(ENEMIGO_STATE_BAJANDO);
        }else{
            itemEnemigo.setTipoMovimiento(ENEMIGO_TIPO_MOVIMIENTO_21);
            itemEnemigo.setImage(App->GetImage("img.enemigo." + std::to_string(rand() % 3)));
            itemEnemigo.setX(-150*i - itemEnemigo.getW() * i);
            itemEnemigo.setY(-150*i - itemEnemigo.getH()* i);
            itemEnemigo.setAngle(7*3.14/4);
            itemEnemigo.setSentido(ENEMIGO_STATE_BAJANDO);
        }

        Enemigos.Add(itemEnemigo);

    }

}

void MiPantalla::Init(void){
  
	Background = new Ros::Object("Background", App);
	Background->setImage(App->GetImage("img.Level.Background"));
	Background->setX(Background->getW()/2);
	Background->setY(Background->getH()/2);

    Lifebar = new Ros::Object("Lifebar", App);
    Lifebar->setImage(App->GetImage("img.lifebar100"));
    Lifebar->setX(280);
    Lifebar->setY(28);

	CrearEstrellas();

    Nave = new Player("Nave.Player1", App);

    Nave->setImage(App->GetImage("img.Player1Off"));
    Nave->setX(App->GetScreenWidth()/2);
    Nave->setY(App->GetScreenHeight() - Nave->getH());

    CrearEnemigos();

}

void MiPantalla::Render(void){

	Background->Draw();
    Lifebar->Draw();

	DibujarEstrellas();
	DibujarPremios();
    DibujarLife();
    DibujarDisparoEnemigo();

	Nave->Draw();

	for(int i=0; i<Enemigos.size(); i++){
        Enemigos.Get(i)->Draw();
	}

	BorrarExplosionesInactivas();
	BorrarPremiosInactivos();
	BorrarDisparoEnemigosInactivos();

	for(int i=0; i<Explosiones.size(); i++){
        Explosiones.Get(i)->Draw();
	}

    this->App->EscribirTexto("ttf.arcade", "Puntaje: " + std::to_string(Puntos), 22, 570, 20);

}

void MiPantalla::BorrarExplosionesInactivas(void){

	std::vector<std::string> idToDelete;

	for(int i=0; i<Explosiones.size(); i++){
		if(Explosiones.Get(i)->isRuning() == false){
			idToDelete.push_back(Explosiones.Get(i)->getId());
		}
	}

	for(int i=0; i < idToDelete.size(); i++){
		Explosiones.DeleteById(idToDelete[i]);
	}

}

void MiPantalla::OnWindowResize(void){

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

void MiPantalla::EventHandler(){

	//sf::RenderWindow *Window = App->GetRenderWindow();

	MoverEstrellas();
	MoverPremios();
	MoverDisparoEnemigo();

	Nave->EventHandler();

	for(int i=0; i<Enemigos.size(); i++){
        Enemigos.Get(i)->EventHandler();
	}

	if (this->isKeyActive[Ros::keyEscape] == true){
	    this->Running = false;
        this->App->SetPantallaActiva("MenuScreen");
        this->App->GetPantallaActiva()->Init();
        this->App->GetPantallaActiva()->Run();

	}


}

MiPantalla::MiPantalla(std::string pId, Ros::Application *pApp) : Pantalla(pId, pApp){
    Puntos = 0;
}

MiPantalla::~MiPantalla(){

	delete Nave;
	delete Background;
    delete Lifebar;

}
