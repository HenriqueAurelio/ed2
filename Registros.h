#ifndef REGISTROS_H
#define REGISTROS_H

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <sstream>
#include <string.h>
#include <math.h>

#include "Estados.h"

using namespace std;

class Registros
{
    public:
        Registros();
        virtual ~Registros();

        void setData(string data);
        void leitura (Registros* r, char* caminho);
        void leitura (Registros* r,int num_registros, char* caminho);
        void setTamanho(int t);

        void imprimir(Registros* r);

        string getData();
        int getTamanho();

        Estados* estados;

    protected:

    private:
        string data;
        int tamanho;
};


#endif // REGISTROS_H
