#ifndef CIDADES_H
#define CIDADES_H

#include <iostream>
#include <fstream>
#include <stdlib.h>

using namespace std;

class Cidades
{
    public:
        Cidades();
        ~Cidades();

        void setNome(string nome);
        void setCodigo(string codigo);
        void setCasos(int casos);
        void setMortes(int mortes);

        string getNome();
        string getCodigo();
        int getCasos();
        int getMortes();

    protected:

    private:
        string nome;
        string codigo;
        int casos;
        int mortes;
        int registroID;
        int estadoID;
};

#endif // CIDADES_H
