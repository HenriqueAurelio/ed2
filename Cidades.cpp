#include "Cidades.h"

Cidades::Cidades()
{
    this->nome = " ";
    this->codigo = " ";
    this->casos=0;
    this->mortes=0;
}

Cidades::~Cidades()
{
    //dtor
}

void Cidades::setNome(string nome)
{
    this->nome=nome;
}

void Cidades::setCodigo(string codigo)
{
    this->codigo=codigo;
}

void Cidades::setCasos(int casos)
{
    this->casos=casos;
}

void Cidades::setMortes(int mortes)
{
    this->mortes=mortes;
}

string Cidades::getNome() {return this->nome;}

string Cidades::getCodigo() {return this->codigo;}

int Cidades::getCasos() {return this->casos;}

int Cidades::getMortes() {return this->mortes;}

