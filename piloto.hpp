#ifndef __PILOTO__
#define __PILOTO__

/*
Las caracteristicas de velocidad, escudo y power
serán modificadas con el transcurso del nivel.

Por lo tanto tambien voy a almacenar estos tres
datos en variables auxiliares con los valores iniciales.
*/

class Piloto{

    private:
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
        /**SETTERS**/
        void setCurrentVelocidad(float v){currentVelocidad = v;}
        void setCurrentEscudo(float v){currentEscudo = v;}
        void setCurrentPower(float v){currentPower = v;}
        Piloto(void);
        Piloto(float v, float e, float p);
        ~Piloto();

};

#endif