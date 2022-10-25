#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#define TAMANHO 100
//---------------------Estrutura Pilha------------------------------------
typedef struct {
  // int vetor
  int vetor[TAMANHO]; // 10 elementos
  // topo (int)
  int topo;
} PilhaEstatica;
//------------------------Inicia Pilha------------------------------------
void iniciaPilha(PilhaEstatica *pilha) {
  // atribuir -1 para topo
  pilha->topo = -1;
}//Iniciar Pilha
//--------------------Esta Vazia Pilha------------------------------------
bool estaVaziaPilha(PilhaEstatica *pilha){
//  topo == -1 -> esta vazia
  return(pilha->topo == -1);
}//Pilha Vazia
//--------------------Esta Cheia Pilha------------------------------------
bool estaCheiaPilha(PilhaEstatica *pilha) {
  return (pilha->topo == (TAMANHO-1));
}//Pilha Cheia
//-----------------------Tamanho Pilha------------------------------------
int tamanhoPilha(PilhaEstatica *pilha) {
  return(pilha->topo + 1);
}//Tamanho Pilha
//----------------------Imprimir Pilha------------------------------------
void imprimirPilha(PilhaEstatica *pilha) {
  printf("Pilha = [");
  int i;

  for(i = 0; i <= pilha->topo; i++) {
    printf("%d ", pilha->vetor[i]);
  }
  printf("]\n");
}//IMprimir pilha
//---------------------Empilhar Pilha-------------------------------------
void empilharPilha(PilhaEstatica *pilha, int x){
  // verifica se está cheia
  if(estaCheiaPilha(&pilha)) {
    printf("Warning: elemento nao pode ser inserido. Pilha cheia %d\n");
  } else {
  // false: posso inserir
    //  topo++
    pilha->topo++;
    //  vetor[topo] = x;
    pilha->vetor[pilha->topo] = x;
  }//if else
}//função empilhar
//------------------Desempilhar Pilha-------------------------------------
int desempilharPilha(PilhaEstatica *pilha) {
  int aux = -9999;
  // Se a pilha nao estiver vazia:
  if(estaVaziaPilha(pilha) == false) {
    // aux = salva ultimo valor valido da pilha
    aux = pilha->vetor[pilha->topo];
    // decrementar o topo
    pilha->topo--;
  } else {
    printf("Warning: não pode remover\n");
  }
    printf("Desempilhado %d\n",aux);
  return(aux);
}//função desempilhar
//----------------------Reinicia Pilha-------------------------------------
void ReiniciaPilha(PilhaEstatica *pilha){
  pilha->topo = -1;
}//reiniciar pilha
//------------------Função Inteiro para Binario----------------------------
void ConverteIntToBin(PilhaEstatica *Pilha,int NumIntEntrada){
  int RestoDividido;
  int IntParaBin;

  RestoDividido = NumIntEntrada;
//------------------Faz a conta do Binário------------------------------------
  while (NumIntEntrada!=1 && NumIntEntrada!=0){
    IntParaBin = RestoDividido % 2;     // = 0,0,0 
    NumIntEntrada = NumIntEntrada / 2;  // = 4,2,1
    empilharPilha(Pilha, IntParaBin);  // [1,0,0,0]
    RestoDividido = NumIntEntrada;      // = 4,2,1
  }//while divisão
  if (NumIntEntrada==1){
    empilharPilha(Pilha,1);
  }//if se for 1
  else if (NumIntEntrada==0){
    empilharPilha(Pilha,0);
  }//if se for 1
}//converte inteiro para binário e empilha
//=========================================================================
//                              MAIN
//=========================================================================
int main(int argc, char const *argv[]){
//------------------------------Declarações--------------------------------
  PilhaEstatica *Pilha;
  PilhaEstatica *PilhaAuxiliar;
  int NumArqEntrada;
  char c;//caracter
  int TamanhoPilha;
  int NumEscreverSaida;
//------------------------------Abre Arquivos------------------------------
  FILE *ArqEntrada  = fopen(argv[1], "r");
  FILE *ArqAuxiliar = fopen(argv[1], "r");
  FILE *ArqSaida    = fopen(argv[2], "w");
  printf("Saida %s\n",argv[2]);
//-----------------------------Testa Arquivos------------------------------
  if (argc > 3 ||argc < 3 ) {
    printf("Error to try read\n");
    exit(1);//finaliza programa
  }//if testa quantidade dos arquivos
  if (ArqEntrada == NULL || ArqSaida == NULL) {
    printf("Error to open the file\n");
    exit(1);//finaliza programa
  }//if testa abertura programas vazios
//---------------------------Primeiros Comandos----------------------------
  iniciaPilha(&Pilha);
  imprimirPilha(&Pilha);
  if(estaVaziaPilha(&Pilha)){
    printf("ESTA VAZIA\n");
  }//if esta vazia
//enquanto entrada não for fim
//chama a função para converter
  while (!feof(ArqEntrada)){
    ReiniciaPilha(&Pilha);//iniciar "nova pilha"
    if (c=fgetc(ArqAuxiliar)!="\n"){
      fscanf(ArqEntrada,"%d",&NumArqEntrada);
      printf("Numero do Arquivo de entrada - %d\n",NumArqEntrada);
      ConverteIntToBin(&Pilha, NumArqEntrada);   //0001
      imprimirPilha(&Pilha);
      //--------Desempilhando a pilha e escrevendo na Saída----------------
      TamanhoPilha = tamanhoPilha(&Pilha);
      printf("TamanhoPilha %d\n",TamanhoPilha);
      for (int x = 0; x < TamanhoPilha; x++){
          NumEscreverSaida = desempilharPilha(&Pilha);
          fprintf(ArqSaida,"%d",NumEscreverSaida);
      }//desempilhando e escrevendo saida
    }//se não for \n
    fprintf(ArqSaida,"\n");
  }// while até acabar entrada
//-----------------------------Fecha Arquivos------------------------------
  fclose(ArqAuxiliar);
  fclose(ArqEntrada);
  fclose(ArqSaida);
return 0;
}//main