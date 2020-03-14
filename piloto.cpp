#include "piloto.hpp"

Piloto::Piloto(std::string pId){
    Id = pId;
}

Piloto::Piloto(std::string pId, float v, float e, float p){
    Id = pId;
    Velocidad = v;
    Escudo = e;
    Power = p;
}

Piloto::~Piloto(){
    return;
}
