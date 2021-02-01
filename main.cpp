#include <iostream>
#include <algorithm> 
#include "Registros.h"
#include "Sort.h"
#include <random>       // std::default_random_engine
#include <chrono>       // std::chrono::system_clock

using namespace std;

//VARIAVEIS GLOBAIS QUE GUARDAM CAMINHO DO ARQUIVO, QUANTIDADE TOTAL DE REGISTROS E O NUM DE REGISTRO LIDOS
const int quantidadeRegistros = 1431490; // Está no relatório e pode ajudar caso precise ler o arquivo inteiro.
char * caminho;


void embaralha(Registros registro[], int num_registros){
    
    srand(time(NULL)*clock());

    for(int i = 0; i <(num_registros/2); i++){
        int a = rand()%num_registros;
        int b = rand()%num_registros;
        Registros aux = registro[a];
        registro[a] = registro[b];
        registro[b] = aux;
    }
}

void testaSort(int num_registros){  

    Registros * registros = new Registros[258];
    clock_t ti, tf; 

    //Zera variaveis dos sort
    trocaQS = 0;
    trocaIS = 0;
    trocaCS = 0;
    compQS = 0;
    compIS = 0;
    compCS = 0;

    // Guarda o tempo dos algoritmos
    double timeQS = 0.0;
    double timeIS = 0.0;
    double timeCS = 0.0;

    std::cout<<endl;
    std::cout<<"Insertion Sort"<<endl;
    registros->leitura(registros,num_registros,caminho);
    //embaralha(registros,num_registros);
    ti=clock();

    for (int i = 0; i < registros->getTamanho(); i++){
        for(int j = 0; j < 27; j ++){
            for(int k = 0; k < registros[i].estados[j].getNumCidades(); k ++){
                insertionSort(registros[i].estados[j].cidades,registros[i].estados[j].getNumCidades());
            }
        }
    }

    tf=clock();
    timeIS = (tf-ti)/double(CLOCKS_PER_SEC);
    std::cout<<endl<<"Tempo gasto: "<<timeIS<<endl;
    
    std::cout<<endl;
    std::cout<<"Quick Sort"<<endl;
    registros->leitura(registros,num_registros,caminho);
    //embaralha(registros,num_registros);
    
    ti=clock();
     
    for (int i = 0; i < registros->getTamanho(); i++){
        for(int j = 0; j < 27; j ++){
            for(int k = 0; k < registros[i].estados[j].getNumCidades(); k ++){
                quickSort(registros[i].estados[j].cidades, 0 ,registros[i].estados[j].getNumCidades());
            }
        }
    } 
 
    tf=clock();
    timeQS = (tf-ti)/double(CLOCKS_PER_SEC);
    std::cout<<endl<<"Tempo gasto: "<<timeQS<<endl;
    
    std::cout<<endl;
    std::cout<<"Cocktail Sort"<<endl;

    registros->leitura(registros,num_registros,caminho);
    //embaralha(registros,num_registros);

    ti = clock();

    for (int i = 0; i < registros->getTamanho(); i++){
        for(int j = 0; j < 27; j ++){
            for(int k = 0; k < registros[i].estados[j].getNumCidades(); k ++){
                cocktailSort(registros[i].estados[j].cidades,registros[i].estados[j].getNumCidades());
            }
        }
    }

    tf = clock();
    timeCS = (tf-ti)/double(CLOCKS_PER_SEC);  
    std::cout<<endl<<"Tempo gasto: "<<timeCS<<endl;

    std::cout<<"Num Registros: "<<num_registros<<endl;
    std::cout<<"trocaIS: "<<trocaIS<<" compIS: "<<compIS<<endl;
    std::cout<<"trocaQS: "<<trocaQS<<" compMS: "<<compQS<<endl;
    std::cout<<"trocaCS: "<<trocaCS<<" compCS: "<<compCS<<endl;
    std::cout<<endl;

    // Salvando a analise no arquivo de saida
    fstream analise;
    analise.open("AnaliseSorts.txt",std::fstream::app);

    if(analise.is_open()){

        analise<<"Num Registros: "<<num_registros<<endl;
        analise<<"TempoIS: "<<timeIS<<endl;
        analise<<"trocaIS: "<<trocaIS<<" compIS: "<<compIS<<endl;

        analise<<"TempoQS: "<<timeQS<<endl;
        analise<<"trocaQS: "<<trocaQS<<" compQS: "<<compQS<<endl;

        analise<<"TempoCS: "<<timeCS<<endl;
        analise<<"trocaCS: "<<trocaCS<<" compCS: "<<compCS<<endl;
        analise<<endl;
    }
    else{

        cout<<"Não pode salvar o arquivo AnaliseSorts.txt."<<endl;
        exit(1);
    }
}

void menuAux(char a) {
    
    std::cout<<endl;

    switch (a) {

        case '1':
        {   
            
            //Passo 1: leitura dos arquivos corretamente e armazenamento em estrutura apropriada (definida pelo programador);
            //Passo 2: Algoritmo de ordenação: (Estado/Cidade)->Data;
            //Passo 3: Transformar totais acumulados em totais diarios;
            //Passo 4: Armazenar os dados em "brazil_covid19_cities_processado.csv";

            //=============================================PASSO 1=============================================
            cout<<"O caminho: "<<caminho<<" foi recebedio."<<endl;
            Registros*r = new Registros[260];
            r->leitura(r,caminho);

            ofstream saida;
            saida.open("brazil_covid19_cities_processado.csv"); //PREPARANDO PASSO 4

            ofstream out;
            out.open("out.txt");
            for(int i=0;i<r->getTamanho();i++)
            {
                for (int j=0; j<27;j++)
                {
                    for(int k =0; k<r[i].estados[j].getNumCidades();k++)
                    {
                        out<<"Data: "<<r[i].getData()<<", "<<"Estado: "<<r[i].estados[j].getCodEstado()<<", "<<"Cidade: "<<r[i].estados[j].cidades[k].getNome()<<", "<<"Codigo: "<<r[i].estados[j].cidades[k].getCodigo()<<", "<<"Casos: "<<r[i].estados[j].cidades[k].getCasos()<<", "<<"Mortes: "<<r[i].estados[j].cidades[k].getMortes()<<endl;
                    }
                }
            }
            out.close();

            //=============================================PASSO 2=============================================
            for(int i=0;i<r->getTamanho();i++)
            {
                for (int j=0; j<27;j++)
                {
                    insertionSortCidades(r[i].estados[j].cidades,r[i].estados[j].getNumCidades());
                }
                insertionSortEstados(r[i].estados,27);
            }
            insertionSortRegistros(r,r->getTamanho());

            //=============================================PASSOS 3 e 4=============================================
            int c=0,m=0;
            int i=0,j=0,k=0;
            int t=0;
            saida<<"date,state,name,cases,death"<<endl;
            for(i=0;i<27;i++)
            {
                for (j=0;j<r[t].estados[i].getNumCidades();j++)
                {
                    for (k=0;k<r->getTamanho();k++)
                    {
                        if(k==0)
                        {
                            c=r[k].estados[i].cidades[j].getCasos();
                            m=r[k].estados[i].cidades[j].getMortes();
                        }
                        else
                        {
                            c=r[k].estados[i].cidades[j].getCasos()-r[k-1].estados[i].cidades[j].getCasos();
                            m=r[k].estados[i].cidades[j].getMortes()-r[k-1].estados[i].cidades[j].getMortes();
                        }

                        if(c<0) c=0; //O arquivo brazil_covid19_cities.csv deveria apresentar um conjunto acumulativo de dados de casos de morte e infecção por covid 19, no entanto em alguns campos apresenta-se um decressimo de um valor que deveria ser acumulativo...
                        if(m<0) m=0; //... para contornar essa inconsistencia, ela sera considerada um erro. Ou seja, toda vez que o numero acumulado de mortes ou casos seja inferior que o da data anterior, a diferenca sera considerada 0

                        saida<<r[k].getData()<<","<<r[k].estados[i].getCodEstado()<<","<<r[k].estados[i].cidades[j].getNome()<<","<<c<<","<<m<<endl;
                    }
                }
                if(t<r->getTamanho());
            }
            saida.close();

            std::cout<<"Leitura do arquivo terminada, saida gerada."<<endl;
            break;
        }
        case '2':
        {   

            int num_registros [5]= {10000, 50000,100000,500000,1000000};
            for(int k = 0; k < 5; k ++){
                for(int i = 0; i<4; i ++)
                    testaSort(num_registros[i]);
            }
            break;
        }
        case '3':
        {        
            
            std::cout << "\nAguarde... \n";
            std::cout << "\nNada por aqui no momento.\n";
            std::cout << "\nFinalizado! \n";
            break;
        }
        //---------- Usar para Testes ----------
        case '4':
        {
            std::cout << "\nSem testes por aqui no momento. :(\n";
            break;
        }
        default:
            break;
    }
}

void menu() {
    //System("tput reset");
    char menu;

    while (true) {
        std::cout << "\n";
        std::cout << "# Menu principal #\n";
        std::cout << "[1] - Leitura e pré-processamento de todo o arquivo\n";
        std::cout << "[2] - Execução dos Sorts (InsertionSort,QuickSort,CocktailSort)\n";
        std::cout << "[3] - Teste MergeSort\n";
        std::cout << "[4] - Testes\n";
        std::cout << "\n";

        do {
            std::cout << "Digite uma opcao do menu: ";
            std::cin >> menu;
        } while (((menu < '0' || menu > '5') && (menu < 'a' || menu > 'z')) && menu != 'q');

        if (menu == 'q') {
            std::cout << "Saindo...\n";
            std::cout << "Bye\n";
            return;
        }
        menuAux(menu);
    }
}

int main(int arg_t, char ** argv){

    if(arg_t == 2)
        caminho = argv[1];
    else
        exit(1);
    menu();
}