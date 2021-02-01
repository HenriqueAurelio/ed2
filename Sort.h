#include <iostream>
#include <string.h>
#include <vector>
#include "Registros.h"
#include "Cidades.h"
 
using namespace std;

// Variaveis de troca e comparação dos algoritmos
long trocaQS;
long compQS;
long trocaIS;
long compIS;
long trocaCS;
long compCS;
long trocaMS;
long compMS;

//Variaveis de controle da ordenação Pre-Processamento
int trocaR=0;
int trocaE=0;
int trocaC=0;

int comparacao(string a, string b)//Funcao auxiliar para facilitar a organização do codigo
{
    return strncmp(a.c_str(),b.c_str(),min(a.length(),b.length()));  
}

void insertionSort(Cidades * c, int tam){
    Cidades pivo;
    int j;
    for(int i=0;i<tam;i++)
    {
        pivo=c[i];
        j=i-1;
        while(j >= 0 && c[j].getCasos()>pivo.getCasos()){

            c[j+1]=c[j];
            j--;
            trocaIS++;
            compIS++;
        }
        c[j+1]=pivo;
        trocaIS++;
    }
}

void insertionSortCidades(Cidades * c,int tam)
//Insertion sort, cidades
{
    Cidades pivo;
    int j;
    for(int i=0;i<tam;i++)
    {  
        pivo = c[i];
        j=i-1;
        while(j >= 0 && (comparacao(c[j].getNome(),pivo.getNome())) > 0)
        {
            c[j+1]=c[j];
            j--;
            trocaC++;
        }
        c[j+1]=pivo;
        trocaC++;
    }
}

void insertionSortEstados(Estados* e,int tam)
//Insertion sort, estados
{
    Estados pivo;
    int j;
    for(int i=0;i<tam;i++)
    {
        pivo=e[i];
        j=i-1;
        while(j >= 0 && (comparacao(e[j].getCodEstado(),pivo.getCodEstado())) > 0)
        {
            e[j+1]=e[j];
            j--;
            trocaE++;
        }
        e[j+1]=pivo;
        trocaE++;
    }
}

void insertionSortRegistros(Registros* r,int tam)
//Insertion sort, registros
{
    Registros pivo;
    int j;
    for(int i=0;i<tam;i++)
    {
        pivo=r[i];
        j=i-1;
        while(j>=0&&(comparacao(r[j].getData(),pivo.getData()))>0)
        {
            r[j+1]=r[j];
            j--;
            trocaR++;
        }
        r[j+1]=pivo;
        trocaR++;
    }
}


// Chave de ordenação o número de casos confirmados

void troca(Cidades * a,Cidades * b)
{
    Cidades t = *a;
    *a=*b;
    *b=t;
    trocaQS++;
}

int particao(Cidades vet[], int inicio, int fim)//particionamento de Livro por conta do id
{   
    int meio = (inicio+fim)/2;
    // Seta o pivo e move para o final da particao
    Cidades pivo = vet[meio];
    troca(&vet[meio],&vet[fim]);

    // Move os elementos menor que o pivo para a posição do contador i
    int i = inicio-1;
    for (int j = inicio;j<=fim;j++)
    {
        if (vet[j].getCasos()<pivo.getCasos())
        {
            i++;
            troca(&vet[i],&vet[j]);
        }
        compQS++;
    }
    troca(&vet[i+1],&vet[fim]);

    return i+1;
}

void quickSort(Cidades vet[],int inicio,int fim){
    if (inicio<fim-1){
        int part = particao(vet,inicio,fim-1);
        quickSort(vet,inicio,part);
        quickSort(vet,part+1,fim-1);
    }
}

// ------------- MERGESORT -------------

/*
    Passo 1: Divida o vetor ao meio
    Passo 2: Ordenar as duas metade
    Passo 3: intercalar as duas metades. 
*/

void merge(int vet[], int inicio, int meio, int fim, int aux[]) {

    // Não precisa de 2 vetores auxiliares apenas um resolve
    // Separa as partições
    int a = inicio;
    int b = meio;

    for (int i = inicio; i < fim; ++i) {
        // Se ainda existe algum numero na partição A não usado
        if (a < meio) {
            // Se o valor de A for < que o valor de B ou se os valores de B já foram completamente usado
            if((vet[a] < vet[b]) || (b >= fim)){
                aux[i] = vet[a];
                trocaMS++;
                a++;
            }
            else {
                aux[i] = vet[b];
                b++;
            }
            compMS++;
        }
        else {
            aux[i] = vet[b];
            ++b;
        }
        compMS++;
    }

    // Copia as alterações de aux para vet
    for (int i = inicio; i < fim; ++i)
        vet[i] = aux[i];
}

void mergeSort(int vet[], int inicio, int fim, int aux[]) {

    if(inicio < fim-1){
        int meio = (inicio + fim)/2;
        mergeSort(vet, inicio, meio, aux);
        mergeSort(vet, meio, fim, aux);
        merge(vet, inicio, meio, fim, aux);
    }
}

void cocktailSort(Cidades vet[],int tam)
{
    bool troca = true;
    int inicio = 0;
    int fim = tam -1;
    while(troca)
    {
        //Vetor desordenado e o algoritmo irá buscar o maior e ir comparando o maior com o proximo até o maior chegar na última posição
        troca = false;
        for(int i = inicio; i < fim; ++i)
        {
            compCS++;
            if(vet[i].getCasos() >vet[i + 1].getCasos())
            {
                //Troca caso o valor no indice i seja maior que no valor no indice i +1
                swap(vet[i],vet[i + 1]);
                troca = true;
                trocaCS++;
            }
        }
        if(!troca)
        {
            break;
        }

        //O maior já esta no ultimo lugar do array então andaremos de trás para frente exceto o último
        fim = fim -1;
        for(int i = fim - 1; i >= inicio; --i)
        {
            compCS++;
            if(vet[i].getCasos() >vet[i + 1].getCasos())
            {
                //Troca caso o valor no indice i seja maior que no valor no indice i +1
                swap(vet[i],vet[i + 1]);
                troca = true;
                trocaCS++;
            }
        }
         //aumenta o inicio porque o menor valor já está na primeira posição
        inicio = inicio + 1;
    }
}
