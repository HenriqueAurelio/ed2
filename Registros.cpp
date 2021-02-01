#include "Registros.h"

Registros::Registros()
{
    this->data = " ";
    this->estados = new Estados[27];
    tamanho=0;
}

Registros::~Registros()
{
    //dtor
}

void Registros::setData(string data) {this->data=data;}
void Registros::setTamanho(int t) {this->tamanho=t;}

string Registros::getData() {return this->data;}
int Registros::getTamanho() {return this->tamanho;}

void Registros::leitura(Registros* r,int num_registros, char* caminho)
{
    ifstream arquivo;
    arquivo.open(caminho);

    if(num_registros <= 0)
        exit(1);

    if(arquivo.is_open())
    {
        cout<<"O arquivo "<<caminho<<" foi aberto com sucesso."<<endl;

        string aux; //variavel auxiliar de leitura de texto
        getline(arquivo,aux,'\n');//Lendo a primeira linha

        int auxInt;//Variavel auxiliar de conversao de texto em inteiros

        //Leitura dos primeiros elementos
        getline(arquivo,aux,',');
        r[0].setData(aux);

        string _data,estado;//Variaveis de controle da etapa de leitura
        _data = aux;//Ajustando a variavel de controle dos registros

        getline(arquivo,aux,',');
        r[0].estados[0].setCodEstado(aux);
        estado = aux;//Ajustando a variavel de controle dos estados

        getline(arquivo,aux,',');
        r[0].estados[0].cidades[0].setNome(aux);

        getline(arquivo,aux,',');
        r[0].estados[0].cidades[0].setCodigo(aux);

        getline(arquivo,aux,',');
        istringstream(aux)>>auxInt;
        r[0].estados[0].cidades[0].setCasos(auxInt);

        getline(arquivo,aux,'\n');
        istringstream(aux)>>auxInt;
        r[0].estados[0].cidades[0].setMortes(auxInt);

        int c=1;

        int i=0;
        int j=0;
        int k=0;
        while(!arquivo.eof() && c<num_registros)
        {
            getline(arquivo,aux,',');//Lendo o campo da data
            if(!(abs(strncmp(aux.c_str(),_data.c_str(),min(aux.length(),_data.length()))))) //strncmp retorna valores diferentes de zero se as strings forem diferentes, e igual a zero se forem iguais. If reconhece verdadeiro se diferente de zero e falso se igual a zero, portanto e valido usar a funcao desta forma.
            {//ainda em r[i]
                getline(arquivo,aux,',');
                if(!(abs(strncmp(aux.c_str(),estado.c_str(),min(aux.length(),estado.length())))))
                {//ainda em estados[j];
                    k++;//Com isso, as cidades variam

                    getline(arquivo,aux,',');//Lendo o nome da cidade
                    r[i].estados[j].cidades[k].setNome(aux);

                    getline(arquivo,aux,',');//Lendo o codigo da cidade
                    r[i].estados[j].cidades[k].setCodigo(aux);

                    getline(arquivo,aux,',');//Lendo a quantidade de casos naquela cidade, naquele dia
                    istringstream(aux)>>auxInt;
                    r[i].estados[j].cidades[k].setCasos(auxInt);

                    getline(arquivo,aux,'\n');//Lendo a quantidade de mortes naquela cidade, naquele dia
                    istringstream(aux)>>auxInt;
                    r[i].estados[j].cidades[k].setMortes(auxInt);
                }
                else
                {//Mudan�a no codigo do estado, deve passar para o proximo estado

                    r[i].estados[j].setNumCidades(k+1); //Atualizando o numero de cidades do estado anterior. Nao e preciso mudar essa grandeza quando i !=0, pois isso ja tera sido feito na primeira iteracao de i.
                    
                    estado=aux;//Definindo o novo estados[j]

                    j++;k=0;
                    
                    //Iniciando as informacoes do novo estados[j]
                    r[i].estados[j].setCodEstado(aux);

                    //Dados da primeira cidade do novo estados[j]
                    getline(arquivo,aux,',');
                    r[i].estados[j].cidades[k].setNome(aux);

                    getline(arquivo,aux,',');
                    r[i].estados[j].cidades[k].setCodigo(aux);

                    getline(arquivo,aux,',');
                    istringstream(aux)>>auxInt;
                    r[i].estados[j].cidades[k].setCasos(auxInt);

                    getline(arquivo,aux,'\n');
                    istringstream(aux)>>auxInt;
                    r[i].estados[j].cidades[k].setMortes(auxInt);
                }
            }
            else
            {//Deve passar para o proximo r[i]

                _data=aux;//Definindo o novo r[i]
                if(r[i].estados[j].getNumCidades()==0) {r[i].estados[j].setNumCidades(k+1);}
                i++;j=0;k=0;//Atualizando as posicoes de i,j,k

                r[i].setData(aux);//Atualizando as informacoes de r[i]

                getline(arquivo,aux,',');
                estado=aux;//Definindo o novo estados[j]
                r[i].estados[j].setCodEstado(aux);//Atualizando as informacoes de estados[j]

                //Atualizando as informacoes da primeira cidade
                getline(arquivo,aux,',');
                r[i].estados[j].cidades[k].setNome(aux);

                getline(arquivo,aux,',');
                r[i].estados[j].cidades[k].setCodigo(aux);

                getline(arquivo,aux,',');
                istringstream(aux)>>auxInt;
                r[i].estados[j].cidades[k].setCasos(auxInt);

                getline(arquivo,aux,'\n');
                istringstream(aux)>>auxInt;
                r[i].estados[j].cidades[k].setMortes(auxInt);
            }
            c++;
            //cout<<c<<endl;
        }
        r[0].setTamanho(i+1);//Desconsidera a ultima linha
        if(r[i].estados[j].getNumCidades()==0) {r[i].estados[j].setNumCidades(k+1);}
        cout<<"Arquivos lidos com sucesso."<<endl;
    }
    else
        cout<<"Erro ao abrir o arquivo"<<endl;
}


void Registros::leitura(Registros* r, char* caminho)
{
    ifstream arquivo;
    //ofstream saida;

    //saida.open("C:\\Users\\WINDOWS\\Desktop\\PROGRAMA��O\\intro C e C++\\ED2_2020-3_ERE_1\\bin\\Debug\\saida.txt");
    arquivo.open(caminho);

    if(arquivo.is_open())
    {
        cout<<"O arquivo "<<caminho<<" foi aberto com sucesso."<<endl;
        //Posicionando o ponteiro de leitura
        arquivo.seekg(0,arquivo.end);
        int tamanho = arquivo.tellg();
        arquivo.seekg(0,arquivo.beg);

        string aux; //variavel auxiliar de leitura de texto
        getline(arquivo,aux,'\n');//Lendo a primeira linha

        int auxInt;//Variavel auxiliar de conversao de texto em inteiros

        //Leitura dos primeiros elementos
        getline(arquivo,aux,',');
        r[0].setData(aux);

        string _data,estado;//Variaveis de controle da etapa de leitura
        _data = aux;//Ajustando a variavel de controle dos registros

        getline(arquivo,aux,',');
        r[0].estados[0].setCodEstado(aux);
        estado = aux;//Ajustando a variavel de controle dos estados

        getline(arquivo,aux,',');
        r[0].estados[0].cidades[0].setNome(aux);

        getline(arquivo,aux,',');
        r[0].estados[0].cidades[0].setCodigo(aux);

        getline(arquivo,aux,',');
        istringstream(aux)>>auxInt;
        r[0].estados[0].cidades[0].setCasos(auxInt);

        getline(arquivo,aux,'\n');
        istringstream(aux)>>auxInt;
        r[0].estados[0].cidades[0].setMortes(auxInt);

        int c=1;

        int i=0;
        int j=0;
        int k=0;
        while(!arquivo.eof()&&c<1431491)
        {
            getline(arquivo,aux,',');//Lendo o campo da data
            if(!(abs(strncmp(aux.c_str(),_data.c_str(),min(aux.length(),_data.length()))))) //strncmp retorna valores diferentes de zero se as strings forem diferentes, e igual a zero se forem iguais. If reconhece verdadeiro se diferente de zero e falso se igual a zero, portanto e valido usar a funcao desta forma.
            {//ainda em r[i]
                getline(arquivo,aux,',');
                if(!(abs(strncmp(aux.c_str(),estado.c_str(),min(aux.length(),estado.length())))))
                {//ainda em estados[j];
                    k++;//Com isso, as cidades variam

                    getline(arquivo,aux,',');//Lendo o nome da cidade
                    r[i].estados[j].cidades[k].setNome(aux);

                    getline(arquivo,aux,',');//Lendo o codigo da cidade
                    r[i].estados[j].cidades[k].setCodigo(aux);

                    getline(arquivo,aux,',');//Lendo a quantidade de casos naquela cidade, naquele dia
                    istringstream(aux)>>auxInt;
                    r[i].estados[j].cidades[k].setCasos(auxInt);

                    getline(arquivo,aux,'\n');//Lendo a quantidade de mortes naquela cidade, naquele dia
                    istringstream(aux)>>auxInt;
                    r[i].estados[j].cidades[k].setMortes(auxInt);
                }
                else
                {//Mudan�a no codigo do estado, deve passar para o proximo estado

                    r[i].estados[j].setNumCidades(k+1); //Atualizando o numero de cidades do estado anterior. Nao e preciso mudar essa grandeza quando i !=0, pois isso ja tera sido feito na primeira iteracao de i.
                    
                    estado=aux;//Definindo o novo estados[j]

                    j++;k=0;
                    
                    //Iniciando as informacoes do novo estados[j]
                    r[i].estados[j].setCodEstado(aux);

                    //Dados da primeira cidade do novo estados[j]
                    getline(arquivo,aux,',');
                    r[i].estados[j].cidades[k].setNome(aux);

                    getline(arquivo,aux,',');
                    r[i].estados[j].cidades[k].setCodigo(aux);

                    getline(arquivo,aux,',');
                    istringstream(aux)>>auxInt;
                    r[i].estados[j].cidades[k].setCasos(auxInt);

                    getline(arquivo,aux,'\n');
                    istringstream(aux)>>auxInt;
                    r[i].estados[j].cidades[k].setMortes(auxInt);
                }
            }
            else
            {//Deve passar para o proximo r[i]

                _data=aux;//Definindo o novo r[i]
                if(r[i].estados[j].getNumCidades()==0) {r[i].estados[j].setNumCidades(k+1);}
                i++;j=0;k=0;//Atualizando as posicoes de i,j,k

                r[i].setData(aux);//Atualizando as informacoes de r[i]

                getline(arquivo,aux,',');
                estado=aux;//Definindo o novo estados[j]
                r[i].estados[j].setCodEstado(aux);//Atualizando as informacoes de estados[j]

                //Atualizando as informacoes da primeira cidade
                getline(arquivo,aux,',');
                r[i].estados[j].cidades[k].setNome(aux);

                getline(arquivo,aux,',');
                r[i].estados[j].cidades[k].setCodigo(aux);

                getline(arquivo,aux,',');
                istringstream(aux)>>auxInt;
                r[i].estados[j].cidades[k].setCasos(auxInt);

                getline(arquivo,aux,'\n');
                istringstream(aux)>>auxInt;
                r[i].estados[j].cidades[k].setMortes(auxInt);
            }
            c++;
            //cout<<c<<endl;
        }
        r[0].setTamanho(i+1);//Desconsidera a ultima linha
        if(r[i].estados[j].getNumCidades()==0) {r[i].estados[j].setNumCidades(k+1);}
        cout<<"Arquivos lidos com sucesso."<<endl;
    }
    else
        cout<<"Erro ao abrir o arquivo"<<endl;
}

void Registros::imprimir(Registros* r)
{
    for(int i=0;i<r->getTamanho();i++)
    {
        for (int j=0; j<27;j++)
        {
            for(int k=0;k<r[i].estados[j].getNumCidades();k++)
            {
                cout<<"Data: "<<r[i].getData()<<", "<<"Estado: "<<r[i].estados[j].getCodEstado()<<", "<<"Cidade: "<<r[i].estados[j].cidades[k].getNome()<<", "<<"Codigo: "<<r[i].estados[j].cidades[k].getCodigo()<<", "<<"Casos: "<<r[i].estados[j].cidades[k].getCasos()<<", "<<"Mortes: "<<r[i].estados[j].cidades[k].getMortes()<<endl;
            }
        }
    }
}
