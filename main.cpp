#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include "lib/application.hpp"
#include "mipantalla.hpp"
#include "pantalla_menu.hpp"
#include "pantalla_piloto.hpp"

#include "lib/object_manager.hpp"
#include "piloto.hpp"

/*
	COMPILAR:
	=========
	(LINUX) g++ lib/*.cpp *.cpp -o game  -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
	(WINDOWS) g++ -LC:\SFML-2.5.1\lib lib/*.cpp *.cpp -o game  -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

	
	CLONAR EL PROYECTO POR PRIMERA VEZ
	==================================
	git clone  https://github.com/horaciodrs/space.git
	git config --global user.name "Horacio Daniel Ros"
	git config --global user.email "horaciodrs@gmail.com"
	sudo apt install build-essential libsfml-dev 
 
	SUBIR CAMBIOS
	=============
	git add .
	git commit -m "Mensaje...."
	git push -u origin master

	
	CLONAR UN BRACH:
	================
	git clone -b Menu --single-branch https://github.com/horaciodrs/space.git

*/

ObjectManager<Piloto> Pilotos;

int main(int argc, char const** argv){

	Ros::Application *App = new Ros::Application(1000, 650, "test");

	//Creo la pantalla del Juego...
	MiPantalla *MainScreen = new MiPantalla("MainScreen", App);
	Ros::Pantalla *refMainScreen = MainScreen;

	//Creo la pantalla del Menu...
	PantallaMenu *MenuScreen = new PantallaMenu("MenuScreen", App);
	Ros::Pantalla *refMenuScreen = MenuScreen;

	//Creo la pantalla de Seleccion del Piloto...
	PantallaPiloto *PilotoScreen = new PantallaPiloto("PilotoScreen", App);
	Ros::Pantalla *refPilotoScreen = PilotoScreen;

	//Creao la base de datos de los pilotos.
	Piloto *auxPiloto;

	float auxPilotoVelocidad[] 	= {1.50, 1.00, 1.25, 0.90};
	float auxPilotoEscudo[] 	= {0.80, 0.50, 0.75, 0.40};
	float auxPilotoPower[] 		= {1.40, 0.80, 1.10, 0.70};

	for(int i=0; i<=3;i++){

		auxPiloto = new Piloto("Piloto." + std::to_string(i));
		auxPiloto->setImagePiloto("img.piloto" + std::to_string(i));
		auxPiloto->setImageNaveOn("img.Player" + std::to_string(i + 1) + "On");
		auxPiloto->setImageNaveOn("img.Player" + std::to_string(i + 1) + "Off");
		auxPiloto->setCurrentVelocidad(auxPilotoVelocidad[i]);
		auxPiloto->setCurrentEscudo(auxPilotoEscudo[i]);
		auxPiloto->setCurrentPower(auxPilotoPower[i]);

		Pilotos.Add(*auxPiloto);

	}

	PilotoScreen->setGlobalPilotos(&Pilotos);

	App->AgregarSonido("sound.Music", "assets/music.ogg");
	App->AgregarSonido("sound.disparo", "assets/disparo.ogg");
	App->AgregarSonido("sound.explosion", "assets/sound/EXPLOSION Bang 04.ogg");
	App->AgregarSonido("sound.premio", "assets/sound/SUCCESS PICKUP Collect Chime 01.ogg");
	App->AgregarSonido("sound.lifequit", "assets/sound/IMPACT Metal Blade Clang 01.ogg");

	App->AgregarImagen("img.Level.Background", "assets/level_background.png");

	App->AgregarImagen("img.Player1On", "assets/player4engineOn.png");
	App->AgregarImagen("img.Player1Off", "assets/player4engineOff.png");
	App->AgregarImagen("img.Player2On", "assets/player6engineOn.png");
	App->AgregarImagen("img.Player2Off", "assets/player6engineOff.png");
	App->AgregarImagen("img.Player3On", "assets/player7engineOn.png");
	App->AgregarImagen("img.Player3Off", "assets/player7engineOff.png");
	App->AgregarImagen("img.Player4On", "assets/player8engineOn.png");
	App->AgregarImagen("img.Player4Off", "assets/player8engineOff.png");

	App->AgregarImagen("img.estrella.1", "assets/estrella1.png");
	App->AgregarImagen("img.estrella.2", "assets/estrella2.png");

	App->AgregarImagen("img.disparo.1", "assets/disparo2.png");
	App->AgregarImagen("img.disparo.2", "assets/disparo3.png");
	App->AgregarImagen("img.disparo.3", "assets/disparo4.png");
	App->AgregarImagen("img.disparo.4", "assets/misil.png");
	App->AgregarImagen("img.Disparo.Enemigo", "assets/disparo_enemigo.png");

	App->AgregarImagen("img.enemigo.0", "assets/enemigo1.png");
	App->AgregarImagen("img.enemigo.1", "assets/enemigo_amarillo.png");
	App->AgregarImagen("img.enemigo.2", "assets/player3small.png");

	App->AgregarImagen("img.explosion", "assets/explosion3.png");

	App->AgregarImagen("img.Premio1", "assets/recompensa.png");
	App->AgregarImagen("img.Premio2", "assets/recompensa2.png");
	App->AgregarImagen("img.Premio3", "assets/recompensa3.png");

	App->AgregarImagen("img.lifebar0", "assets/lifebar0.png");
	App->AgregarImagen("img.lifebar5", "assets/lifebar5.png");
	App->AgregarImagen("img.lifebar10", "assets/lifebar10.png");
	App->AgregarImagen("img.lifebar15", "assets/lifebar15.png");
	App->AgregarImagen("img.lifebar20", "assets/lifebar20.png");
	App->AgregarImagen("img.lifebar25", "assets/lifebar25.png");
	App->AgregarImagen("img.lifebar30", "assets/lifebar30.png");
	App->AgregarImagen("img.lifebar35", "assets/lifebar35.png");
	App->AgregarImagen("img.lifebar40", "assets/lifebar40.png");
	App->AgregarImagen("img.lifebar45", "assets/lifebar45.png");
	App->AgregarImagen("img.lifebar50", "assets/lifebar50.png");
	App->AgregarImagen("img.lifebar55", "assets/lifebar55.png");
	App->AgregarImagen("img.lifebar60", "assets/lifebar60.png");
	App->AgregarImagen("img.lifebar65", "assets/lifebar65.png");
	App->AgregarImagen("img.lifebar70", "assets/lifebar70.png");
	App->AgregarImagen("img.lifebar75", "assets/lifebar75.png");
	App->AgregarImagen("img.lifebar80", "assets/lifebar80.png");
	App->AgregarImagen("img.lifebar85", "assets/lifebar85.png");
	App->AgregarImagen("img.lifebar90", "assets/lifebar90.png");
	App->AgregarImagen("img.lifebar95", "assets/lifebar95.png");
	App->AgregarImagen("img.lifebar100", "assets/lifebar100.png");


	App->AgregarImagen("img.weaponbar100", "assets/weaponbar100.png");
	App->AgregarImagen("img.weaponbar95", "assets/weaponbar95.png");
	App->AgregarImagen("img.weaponbar90", "assets/weaponbar90.png");
	App->AgregarImagen("img.weaponbar85", "assets/weaponbar85.png");
	App->AgregarImagen("img.weaponbar80", "assets/weaponbar80.png");
	App->AgregarImagen("img.weaponbar75", "assets/weaponbar75.png");
	App->AgregarImagen("img.weaponbar70", "assets/weaponbar70.png");
	App->AgregarImagen("img.weaponbar65", "assets/weaponbar65.png");
	App->AgregarImagen("img.weaponbar60", "assets/weaponbar60.png");
	App->AgregarImagen("img.weaponbar55", "assets/weaponbar55.png");
	App->AgregarImagen("img.weaponbar50", "assets/weaponbar50.png");
	App->AgregarImagen("img.weaponbar45", "assets/weaponbar45.png");
	App->AgregarImagen("img.weaponbar40", "assets/weaponbar40.png");
	App->AgregarImagen("img.weaponbar35", "assets/weaponbar35.png");
	App->AgregarImagen("img.weaponbar30", "assets/weaponbar30.png");
	App->AgregarImagen("img.weaponbar25", "assets/weaponbar25.png");
	App->AgregarImagen("img.weaponbar20", "assets/weaponbar20.png");
	App->AgregarImagen("img.weaponbar15", "assets/weaponbar15.png");
	App->AgregarImagen("img.weaponbar10", "assets/weaponbar10.png");
	App->AgregarImagen("img.weaponbar5", "assets/weaponbar5.png");
	App->AgregarImagen("img.weaponbar0", "assets/weaponbar0.png");

	App->AgregarImagen("img.piloto0", "assets/piloto1circle.png");
	App->AgregarImagen("img.piloto1", "assets/piloto2circle.png");
	App->AgregarImagen("img.piloto2", "assets/piloto3circle.png");
	App->AgregarImagen("img.piloto3", "assets/piloto4circle.png");
	App->AgregarImagen("img.piloto.selection.light", "assets/piloto_selection_light.png");


	//App->AgregarImagen("img.Opciones.Jugar", "assets/lifebar100.png");

	App->AgregarFuente("ttf.arcade", "assets/ARCADE.TTF");
	App->AgregarFuente("ttf.zerovelo", "assets/zerovelo.ttf");

	App->AgregarPantalla(refMainScreen);
	App->AgregarPantalla(refMenuScreen);
	App->AgregarPantalla(refPilotoScreen);
	App->SetPantallaActiva("MenuScreen");

	App->Init();

	App->PlaySound("sound.Music", 30, true);

	App->Run();

	delete MainScreen;
	delete MenuScreen;
	delete PilotoScreen;
	delete App;

	return EXIT_SUCCESS;

}
