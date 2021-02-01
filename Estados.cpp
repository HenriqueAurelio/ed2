#include "Estados.h"

Estados::Estados()
{
    this->codigoEstado = " ";
    this->cidades = new Cidades[855];
    this->numCidades=0;
}

Estados::~Estados()
{
    //dtor
}

void Estados::setCodEstado(string codEstado) {this->codigoEstado=codEstado;}


void Estados::setNumCidades(int n) {this->numCidades=n;}

string Estados::getCodEstado() {return this->codigoEstado;}

int Estados::getNumCidades() {return this->numCidades;}
