#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

//--------------------------------------------------------
//----------------Estrutura Fila Dinamica-----------------
//--------------------------------------------------------
typedef struct NoFila* PtrNoFila;

typedef struct NoFila{
  int pagina;
  char *palavra;
  PtrNoFila proximo;
} NoFila;

typedef struct {
  PtrNoFila inicio;
  PtrNoFila fim;
  int qtde;
} FilaDinamica;
//--------------------------------------------------------
//-----------------Funções Fila Dinamica------------------
//--------------------------------------------------------
void iniciaFilaDinamica(FilaDinamica *fila) {
  fila->inicio = NULL;
  fila->fim = NULL;
  fila->qtde = 0;
}//Iniciar Fila Dinamica

bool estaVaziaFilaDinamica(FilaDinamica *fila) {
  return(fila->qtde == 0);
  // return(fila->inicio == NULL);
}//Esta Vazia Fila Dinamica

int tamanhoFilaDinamica(FilaDinamica *fila) {
  return(fila->qtde);
}//Tamanho Fila Dinamica

void imprimirFilaDinamica(FilaDinamica *fila,FILE *Saida) {
  printf("Fila = [");
  // logica
  // laço repetição (inicio), proximo valor de um axiliar == NULL
  //   - printf aux->x
  PtrNoFila aux;
  //  for(<inicial>, <parada>, incremento)
  for(aux = fila->inicio; aux != NULL; aux = aux->proximo) {
    //printf("Cheguei Aqui \n");
    printf(", %d", aux->pagina);
    fprintf(Saida, ",%d", aux->pagina);
  }
  printf("]\n");
}//Imprime Fila Dinamica

void enfileirarFilaDinamica(FilaDinamica * fila, int valor) {
if(estaVaziaFilaDinamica(fila) || fila->fim->pagina != valor){
  PtrNoFila novo = malloc(sizeof(NoFila));
// - criar um novo no, alocar memoria
  printf("-Enfileirando-\n");
// - copiar o numero no novo no
  novo->pagina = valor;
// - proximo do novo no é null
  novo->proximo = NULL;
  //printf("Palavra igual - PG %d\n",novo->pagina); //valor do pg vindo correto até aqui
// 1a insercao
  if(estaVaziaFilaDinamica(fila)) {
    // - inicio aponta p novo no
    fila->inicio = novo;
    // - fim aponta p novo no
    fila->fim = novo;
  } else {
  //printf("Ultimo fila %d > valor %d\n",fila->fim->pagina,valor);
  // 2a ou + insercoes
    //  - proximo do fim (44) apontar p novo (13)
    fila->fim->proximo = novo;
    //  - atualizar o fim: fim recebe novo, ou fim = fim->proximo
    fila->fim = novo;
    // fila->fim = fila->fim->proximo;
  }
  fila->qtde++;} //conferencia para inserir somente 1 vez a pagina ou quando é a primeira pagina da fila
}
//inserção fila dinamica

void desenfileirarFilaDinamica(FilaDinamica *fila) {
  // se ! estiver vazia:
  if(!estaVaziaFilaDinamica(fila)) {
  //   criar aux e   aux = inicio
    PtrNoFila aux = fila->inicio;
  // se for fila de tam 1:
    if(tamanhoFilaDinamica(fila) == 1) {
  //   inicio = fim = null
      fila->inicio = NULL;
      fila->fim = NULL;
    } else {
      // tem mais elementos
      fila->inicio = fila->inicio->proximo;
    }
    free(aux);
    fila->qtde--;
  } else {
    printf("Warning: fila vazia!\n");
  }
}//remoção fila dinamica
//--------------------------------------------------------
//--------------------Funções Criadas---------------------
//--------------------------------------------------------
void Estruturaindice(FilaDinamica *Fila,int  pagina, char *palavra){

}//função para estruturar a saída
//--------------------------------------------------------
//----------------Estrutura Arvore Binaria----------------
//--------------------------------------------------------
typedef struct NoArvore *PtrNoArvore;

typedef struct NoArvore
{
    char chave[100];
    FilaDinamica paginas;
    PtrNoArvore direita;
    PtrNoArvore esquerda;
} NoArvore;
//--------------------------------------------------------
//-----------------Funções Arvore Binaria-----------------
//--------------------------------------------------------
void iniciaArvore(PtrNoArvore *arvore) {
  *arvore = NULL;
}//Iniciar arvore binaria

bool arvoreVazia(PtrNoArvore *arvore) {
  return (*arvore == NULL);
}//Arvore esta vazia?

bool inserearvore(PtrNoArvore *arvore, char *x){
  char aux;
  aux = x[0];

  if (*arvore == NULL)
  {
    (*arvore) = malloc(sizeof(NoArvore));
    (*arvore)->direita = NULL;
    (*arvore)->esquerda = NULL;
    strcpy((*arvore)->chave,x);
    iniciaFilaDinamica(&(*arvore)->paginas);
  return true;
  }//se arvorw wsriver vazia
  if (strcmp((*arvore)->chave, x) == 0)
  {
    return false;
  }//se a palavra ja estiver na arvore
  if ((*arvore)->chave[0] > aux)
  {
    return (inserearvore(&(*arvore)->esquerda, x));
  }//palavra maior
  else
  {
    return (inserearvore(&(*arvore)->direita, x));
  }//palavra menor
}//Inserir na arvore

void impressaoEmOrdem(PtrNoArvore *no) {
  if((*no) == NULL) return;
  impressaoEmOrdem(&(*no)->esquerda);
  printf("%s ", (*no)->chave);
  impressaoEmOrdem(&(*no)->direita);
}// Em ordem

bool procuraArvore(PtrNoArvore *arvore, char *x,int pg){
  if (*arvore == NULL)
    return false;

  if (strcmp((*arvore)->chave, x) == 0){
    enfileirarFilaDinamica(&(*arvore)->paginas,pg);
    return true;
  }

  if ((*arvore)->chave[0] > x[0]){
    return (procuraArvore(&(*arvore)->esquerda, x, pg));
  }//vai pra esq
  else{
    return (procuraArvore(&(*arvore)->direita, x, pg));
  }//vai pra esq
}//Procurar na arvore

void EmOrdemPrincipal (PtrNoArvore* arvore,FILE *Saida){
  //impressaoEmOrdem(&*arvore);

    if((*arvore) == NULL) return;
  EmOrdemPrincipal(&(*arvore)->esquerda,Saida);
  fprintf(Saida, "%s", (*arvore)->chave);
  printf("%s", (*arvore)->chave);
  imprimirFilaDinamica(&(*arvore)->paginas,Saida);
  fprintf(Saida, "\n");

  EmOrdemPrincipal(&(*arvore)->direita,Saida);
}
//--------------------------------------------------------
//-------------------------MAIN---------------------------
//--------------------------------------------------------
int main(int argc, char *argv[]){
  FILE *Entrada = fopen(argv[1], "r");
  FILE *Saida = fopen(argv[2], "w");

  char palavras[100];
  char *PalavraAuxiliar;
  char Lendo[100];
  int NumPagina = 0;
  char *tabela[10];

  PtrNoArvore Termos;
  iniciaArvore(&Termos);

  FilaDinamica FilaTermos;
  iniciaFilaDinamica(&FilaTermos);
//============================Teste de Arquivos===============================
  // checar erros de abertura de arquivo
  if (argc > 3 || argc < 3 ) {
    printf("Error to try read\n");
    return 1;//finaliza programa
  }//if testa quantidade dos arquivos

  if(Entrada == NULL || Saida == NULL) {
     printf("Erro: algum dos arquivos não pode ser criado corretamente\n");
     return 0;
  }//if Arquivo de entrada ou saida
//=============================Desenvolvimento================================
  fscanf(Entrada, "<termos:%s", Lendo);
  PalavraAuxiliar = strtok(strlwr(Lendo), ",>");//uso do "strlwr(Lendo)", para não haver engano em minuscula e maiuscula

  while (PalavraAuxiliar != NULL)
  {   //insere os termos na arvore
      inserearvore(&Termos, PalavraAuxiliar);
      PalavraAuxiliar = strtok(NULL, ",>");
  }//insere os termos
  printf("-------------------------------------------------------\n");
  printf("Termos na arvore : ");
  impressaoEmOrdem(&Termos);
  printf("\n-------------------------------------------------------\n");
  //Verifica se as palavras estão na arvore e conta as paginas
  while (EOF != fscanf(Entrada, "%s", Lendo))
  {
    PalavraAuxiliar = strtok(strlwr(Lendo), "<,.:()>");//uso do "strlwr(Lendo)", para não haver engano em minuscula e maiuscula

    while (PalavraAuxiliar != NULL)
    {
      if (strcmp(PalavraAuxiliar, "page") == 0)
      {
        NumPagina++;
      }//se for nova pagina
      if (procuraArvore(&Termos, PalavraAuxiliar,NumPagina)){
        printf("%s , Na pagina %d\n", PalavraAuxiliar, NumPagina);
      }//se estiver na arvore
      PalavraAuxiliar = strtok(NULL, "<,.:()>");
    }//PalavraAuxiliar diferente de null
  }//enquanto não for fim de arquivo
  printf("=========ARQ SAIDA=========\n");
  EmOrdemPrincipal(&Termos,Saida);
  printf("===========================\n");
//============================Liberando Arquivos==============================
  free(Entrada);
  free(Saida);
}//main