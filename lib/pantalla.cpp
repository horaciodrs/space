#include "pantalla.hpp"

namespace Ros{
    
    void Pantalla::Init(void){
        //Esta funcion tiene que ser redefinida en las clases que hereden a Pantalla
        //para poder inicializar sus propias caracteristicas.
    }

	void Pantalla::Render(void){
		//dibuja los objetos de la pantalla.
		//esta funcion es virtual, por lo cual puede ser
		//redefinida en la clase hija para
		//dibujar los objetos en pantalla.
	}

	void Pantalla::EventHandler(){
		//procesa los eventos de la pantalla.
		//esta funcion es virtual, por lo cual puede ser
		//redefinida en la clase hija para procesar
		//los eventos de manera personalizada...
	}
	
	void Pantalla::OnWindowResize(){
		//esta funcion se ejecuta cuando la pantalla cambia de tamaño.
		//esta funcion es virtual, por lo cual puede ser
		//redefinida en la clase hija para procesar
		//los eventos de manera personalizada...
	}

	void Pantalla::Run(void){
		
		while (App->Window->isOpen()){
			
			sf::Event event;

			while (App->Window->pollEvent(event)){

				//procesar los flags de las tecla presionadas.
				procesarTeclasActivas(&event);
				
				if (event.type == sf::Event::Resized){
					App->Window->setView(sf::View(sf::FloatRect(0.f, 0.f, static_cast<float>(App->Window->getSize().x),static_cast<float>(App->Window->getSize().y))));
					
					App->UpdateScreenWidth(App->Window->getSize().x);
					App->UpdateScreenHeight(App->Window->getSize().y);
					
					OnWindowResize();
				
				}
			
				if (event.type == sf::Event::Closed) {
					App->Window->close();
				}
			
				if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
					App->Window->close();
				}
				
			}
			
			EventHandler();

			App->Window->clear();
			
			Render();
			
			App->Window->display();

		}

	}
	
	void Pantalla::procesarTeclasActivas(sf::Event *event){
	
		if (event->type == sf::Event::KeyPressed && event->key.code == sf::Keyboard::Left) {
			isKeyActive[keyLeft] = true;
		}else if (event->type == sf::Event::KeyReleased && event->key.code == sf::Keyboard::Left) {
			isKeyActive[keyLeft] = false;
		}
		
		if (event->type == sf::Event::KeyPressed && event->key.code == sf::Keyboard::Up) {
			isKeyActive[keyUp] = true;
		}else if (event->type == sf::Event::KeyReleased && event->key.code == sf::Keyboard::Up) {
			isKeyActive[keyUp] = false;
		}
		
		if (event->type == sf::Event::KeyPressed && event->key.code == sf::Keyboard::Right) {
			isKeyActive[keyRight] = true;
		}else if (event->type == sf::Event::KeyReleased && event->key.code == sf::Keyboard::Right) {
			isKeyActive[keyRight] = false;
		}
		
		if (event->type == sf::Event::KeyPressed && event->key.code == sf::Keyboard::Down) {
			isKeyActive[keyDown] = true;
		}else if (event->type == sf::Event::KeyReleased && event->key.code == sf::Keyboard::Down) {
			isKeyActive[keyDown] = false;
		}
		
		if (event->type == sf::Event::KeyPressed && event->key.code == sf::Keyboard::Space) {
			isKeyActive[keySpace] = true;
		}else if (event->type == sf::Event::KeyReleased && event->key.code == sf::Keyboard::Space) {
			isKeyActive[keySpace] = false;
		}

	}

	Pantalla::Pantalla(std::string pId, Application *pApp) : Id(pId), App(pApp){
		isKeyActive[keyLeft]	= false;
		isKeyActive[keyUp]		= false;
		isKeyActive[keyRight]	= false;
		isKeyActive[keyDown]	= false;
		isKeyActive[keySpace]	= false;
	}

	Pantalla::~Pantalla(){

	}

}