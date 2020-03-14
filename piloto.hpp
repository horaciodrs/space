#ifndef __PILOTO__
#define __PILOTO__

#include <string>

/*
Las caracteristicas de velocidad, escudo y power
serán modificadas con el transcurso del nivel.

Por lo tanto tambien voy a almacenar estos tres
datos en variables auxiliares con los valores iniciales.
*/

class Piloto{

    protected:
        std::string Id;
        std::string imgPilotoId;   //Imagen del Piloto.
        std::string imgNaveOnId;   //Imagen(Id) con la nave en movimiento.
        std::string imgNaveOffId;  //Imagen(Id) cuando la nave no se mueve.
        float Velocidad;            //Se guarda el valor por defecto.
        float Escudo;
        float Power;
        float currentVelocidad;     //Se guarda el valor actual(en uso).
        float currentEscudo;
        float currentPower;
    public:
        /**GETTERS**/
        float getCurrentVelocidad(void){return currentVelocidad;}
        float getCurrentEscudo(void){return currentEscudo;}
        float getCurrentPower(void){return currentPower;}
        std::string getImgPiloto(){return imgPilotoId;}
        /**SETTERS**/
        void setCurrentVelocidad(float v){currentVelocidad = v;}
        void setCurrentEscudo(float v){currentEscudo = v;}
        void setCurrentPower(float v){currentPower = v;}
        
        void setImagePiloto(std::string pId){imgPilotoId = pId;}
        void setImageNaveOn(std::string pId){imgNaveOnId = pId;}
        void setImageNaveOff(std::string pId){imgNaveOffId = pId;}

        Piloto(std::string pId);
        Piloto(std::string pId, float v, float e, float p);
        ~Piloto();

};

#endif