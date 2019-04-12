#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include "lib/application.hpp"
#include "mipantalla.hpp"

/*
g++ lib/*.cpp *.cpp -o game  -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
*/

int main(int argc, char const** argv){

	Ros::Application *App = new Ros::Application(1000, 650, "test");
    MiPantalla *MainScreen = new MiPantalla("MainScreen", App);
    Ros::Pantalla *refMainScreen = MainScreen;//

    App->AgregarSonido("sound.Music", "assets/music.ogg");
    App->AgregarSonido("sound.disparo", "assets/disparo.ogg");
    App->AgregarSonido("sound.explosion", "assets/sound/EXPLOSION Bang 04.ogg");
    App->AgregarSonido("sound.premio", "assets/sound/SUCCESS PICKUP Collect Chime 01.ogg");
    App->AgregarSonido("sound.lifequit", "assets/sound/IMPACT Metal Blade Clang 01.ogg");

    App->AgregarImagen("img.Level.Background", "assets/level_background.png");

    App->AgregarImagen("img.Player1On", "assets/player4engineOn.png");
    App->AgregarImagen("img.Player1Off", "assets/player4engineOff.png");

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

    App->AgregarFuente("ttf.arcade", "assets/ARCADE.TTF");

    App->AgregarPantalla(refMainScreen);
    App->SetPantallaActiva("MainScreen");

	App->Init();

    App->PlaySound("sound.Music", 30, true);

	App->Run();

    delete MainScreen;
    delete App;

    return EXIT_SUCCESS;

}
