#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
//---------------------Estrutura Pilha Dinamica---------------------------
typedef struct NoPilha* PtrNoPilha;

typedef struct NoPilha {
  int x;
  PtrNoPilha proximo;
} NoPilha;

typedef struct{
  PtrNoPilha topo; // aponta p um no de pilha qualquer
  int qtde; // qtde de elementos na pilha
} PilhaDinamica ;
//---------------------Inicia Pilha Dinamica------------------------------
void iniciaPilhaDinamica(PilhaDinamica *pilha){
  pilha->qtde = 0;
  pilha->topo = NULL;
}// inicializacao da estrutura
//---------------------Esta Vazia Pilha Dinamica--------------------------
bool estaVaziaPilhaDinamica(PilhaDinamica *pilha) {
//  pilha->qtde == 0
  return(pilha->topo == NULL);
}// esta vazia
//---------------------Tamanho Pilha Dinamica-----------------------------
int tamanhoPilhaDinamica(PilhaDinamica *pilha) {
  return(pilha->qtde);
}// tamanho da pilha
//---------------------Imprime Pilha Dinamica-----------------------------
void imprimirPilhaDinamica(PilhaDinamica *pilha){
  printf("Pilha = [");
  PtrNoPilha var = pilha->topo;
  while(var != NULL) {
    printf("%d ", var->x);
    var = var->proximo;
  }
  printf("]\n");
}// impressao da pilha
//---------------------Empilha Pilha Dinamica-----------------------------
void empilharPilhaDinamica(PilhaDinamica *pilha, int x) {
  // criar o novo no (alocar memoria)
  PtrNoPilha novo = malloc(sizeof(NoPilha));
  // copiar o valor no novo nó
  novo->x = x;
  // atualizar refs
  //    - novo->proximo = topo
  novo->proximo = pilha->topo;
  //    - topo = novo
  pilha->topo = novo;
  // qtde++
  pilha->qtde++;
}// insercao (push)/empilhar
//---------------------Desempilha Pilha Dinamica--------------------------
int desempilharPilhaDinamica(PilhaDinamica *pilha) {
  int ret = -999;
  //  se estiver vazia, nao remove
  if(estaVaziaPilhaDinamica(pilha)) {
    printf("Cara, esta vazia, nao tem o que fazer\n");
  } else {
    // salvar o valor a ser retornado
    ret = pilha->topo->x;
    // Ptr auxiliar
    PtrNoPilha aux = pilha->topo;
    // atualizar o topo
    pilha->topo = pilha->topo->proximo;
    // pilha->topo = aux->proximo;
    // desalocar memoria
    free(aux);
    // qtde--
    pilha->qtde--;
  }  // retornar
  return(ret);
}// remover (pop)/desempilhar
//---------------------Função Confere Caracter Valido---------------------
bool ConfereCaracter(char *caracter){
  char CaracterValido[30] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','+','-','*','/'};
  int valido = 0;

  for (int i = 0; i < 30; i++){
    if (CaracterValido[i] == caracter){
      valido ++;
    }//se for valido
  }//confere se é operando

  if (valido == 1){
    return true; 
  }//retorna valido
  else{
    return false;
  }//retorna falso  
}//função confere se caracter é valido
//---------------------Função Confere Caracter Valido---------------------
bool ConfereOperador(char *caracter){
  char CaracterValido[4] = {'+','-','*','/'};
  int valido = 0;

  for (int i = 0; i < 4; i++){
    if (CaracterValido[i] == caracter){
      valido ++;
    }//se for valido
  }//confere se é operando

  if (valido == 1){
    return true; 
  }//retorna valido
  else{
    return false;
  }//retorna falso  
}//função confere se caracter é valido
//------------------------------------------------------------------------
//-------------------------------MAIN-------------------------------------
//------------------------------------------------------------------------
int main(int argc, char* argv[]) {
//------------------------------Declarações--------------------------------
  PilhaDinamica *Pilha;
  char c;//caracter
  int aux=0;// para começar recebendo um operando
  int conttemp=2;
  char operando[3];
//-----------------------------Testa Arquivos------------------------------
  if (argc > 3 ||argc < 3 ) {
    printf("Error to try read\n");
    exit(1);//finaliza programa
  }//if testa quantidade dos arquivos
//------------------------------Abre Arquivos------------------------------
  FILE *ArqEntrada  = fopen(argv[1], "r");
  FILE *ArqAuxiliar = fopen(argv[1], "r");
  FILE *ArqSaida    = fopen(argv[2], "w");
  printf("Saida %s\n",argv[2]);
  if (ArqEntrada == NULL || ArqSaida == NULL) {
    printf("Error to open the file\n");
    exit(1);//finaliza programa
  }//if testa abertura programas vazios
//---------------------------Primeiros Comandos Pilha Dinamica-------------
  iniciaPilhaDinamica(&Pilha);
//---------------------------Primeiros Comandos----------------------------
  while (!feof(ArqEntrada)){
    if (c=fgetc(ArqAuxiliar)!="\n"){
      if (ConfereCaracter(&c)==true && (aux % 2 != 0)){//confere se o caracter é válido
      operando[0] = c;
        if (ConfereOperador(&c)==true){//confere se o é operador + - * /
          if (estaVaziaPilhaDinamica(&Pilha) == false){
          operando[0] = desempilharPilhaDinamica(&Pilha);
          }// não esta vazia - Pilha chega vazia
          else{
            printf("\n ERRO - QUANTIDADE DE OPERANDO\n");
            fprintf(ArqSaida,"\n ERRO - QUANTIDADE DE OPERANDO\n");
            exit(1);
          }//ERRO
          operando[1] = ' ';
          if (estaVaziaPilhaDinamica(&Pilha) == false){
          operando[2] = desempilharPilhaDinamica(&Pilha);
          }// não esta vazia - Pilha Contem um operando
          else{
            printf("\n ERRO - QUANTIDADE DE OPERANDO\n");
            fprintf(ArqSaida,"\n ERRO - QUANTIDADE DE OPERANDO\n");
            exit(1);
          }//ERRO

          aux = 2;
          if(c == '+'){
            fprintf(ArqSaida,"ADD %c %c\n",operando[0],operando[2]);
          }//operador +
          else if(c == '-'){
            fprintf(ArqSaida,"SUB %c %c\n",operando[0],operando[2]);
          }//operador -
          else if(c == '*'){
            fprintf(ArqSaida,"MUL %c %c\n",operando[0],operando[2]);
          }//operador *
          else if(c == '/'){
            fprintf(ArqSaida,"DIV %c %c\n",operando[0],operando[2]);
          }//operador /

          fprintf(ArqSaida,"STR TEMP%d\n",conttemp-2);
        }//se for operador
        else{
          empilharPilhaDinamica(&Pilha,c);
          if(aux % 2 == 0){
            fprintf(ArqSaida,"LRD %s\n",operando);
          }//aux par
          else{
            conttemp ++;
          }//aux impar 
          aux = 1;
        }// é operando
      // -  Exemplo de entrada = AB+CD+*
      //if (c=fgetc(ArqAuxiliar)!="\n"){

          //Recebe o primeiro char 
          //Se for diferente de + - / *
            //empilha
            // - LDR A 
            // - LDR B
            //
            // - LDR C
            // - LDR D
            // 
            // - LDR TEMP2
            // - LDR TEMP1

          //else 
            // - ADD B A
            // - ADD D C
            //Passa o char capturado e a pilha 
                //desempilha e armazena em N1
                //desempilha e armazena em N2
                //resultado = n1 , char capturado , n2 
                //empilha o resultado na pilha 
                // - STR TEMP1

                // - STR TEMP2

                // - MUL TEMP2 TEMP1
      }//caracter valido
      else{
        printf("\n ERRO - O CARACTER NÂO EH VALIDO \n");
        fprintf(ArqSaida,"\n ERRO - O CARACTER NÂO EH VALIDO \n");
        exit(1);
      }//se há caracter não valido, Adeus
    }// if entrada != \n  
  }// while até acabar entrada
//-----------------------------Fecha Arquivos------------------------------
  fclose(ArqAuxiliar);
  fclose(ArqEntrada);
  fclose(ArqSaida);
  return 0;
}