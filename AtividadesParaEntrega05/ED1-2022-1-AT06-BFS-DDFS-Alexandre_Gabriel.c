#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

// -----------------------------
// -----------------------------

typedef struct {
  int **matriz;  // por os 0s e 1s
  int vertices;  // qtde de vertices
  int arestas;   // qtde de arestas
  bool dirigido; // se é dirigido ou não
} GrafoMatriz;

// -----------------------------
// -----------------------------

void iniciaGrafoMatriz(GrafoMatriz *g, int V, bool dir) {
  int i, j;

  g->vertices = V;   // vertices
  g->arestas = 0;    // arestas
  g->dirigido = dir; // dirigido

  // alocando memoria da matriz
  g->matriz = malloc(V * sizeof(int*));
  for(i = 0; i < V; i++) {
    g->matriz[i] = malloc(V * sizeof(int));
  }

  // inicializa toda as celulas como 0
  for(i = 0; i < V; i++) {
    for(j = 0; j< V; j++) {
      g->matriz[i][j] = 0;
    }
  }

}

// -----------------------------
// -----------------------------

void imprimeGrafoMatriz(GrafoMatriz *g) {
  int i, j, V;
  V = g->vertices;
  // inicializa toda as celulas como 0
  for(i = 0; i < V; i++) {
    printf("%d: ", i);
    for(j = 0; j< V; j++) {
      printf("%d ", g->matriz[i][j]);
    }
    printf("\n");
  }
}

// -----------------------------
// -----------------------------

void insereArestaGrafoMatriz(GrafoMatriz *g, int v1, int v2) {
  g->matriz[v1][v2] = 1;
  if(!g->dirigido) {
    g->matriz[v2][v1] = 1;
  }
  g->arestas++;
}

// -----------------------------
// -----------------------------

void removeArestaGrafoMatriz(GrafoMatriz *g, int v1, int v2) {

  g->matriz[v1][v2] = 0;
  if(!g->dirigido) {
    g->matriz[v2][v1] = 0;
  }
  g->arestas--;
}

// -----------------------------
// -----------------------------

void destruirGrafoMatriz(GrafoMatriz *g) {
  for(int i = 0; i < g->vertices; i++) {
    free(g->matriz[i]);
  }
  free(g->matriz);
}

// funcao busca em largura
void buscaemlargura(GrafoMatriz *gr, int ini, int *visitado){
    int vert;
    int nv;
    int cont = 1;
    int x = 0;
    int y = 0;
    int *fila;

    for (size_t i = 0; i < gr->vertices; i++)
    {
        visitado[i] = 0;
    }
    nv = gr->vertices;
    fila = (int*)malloc(nv * sizeof(int));
    y++;
    fila[y] = ini;
    visitado[ini] = cont;

    while (x != y){
        x = (x + 1) % nv;
        vert = fila[x];
        cont++;
    }

    for (size_t i = 0; i < gr->arestas; i++)
    {
        if (!visitado[gr->matriz[vert][i]])
        {
            y = (y + 1) % nv;
            fila[y] = gr->matriz[vert][i];
            visitado[gr->matriz[vert][i]] = cont;
        }
        
    }
        free fila;
}

// -----------------------------
// -----------------------------

int main(int argc, const char * argv[]) {
  GrafoMatriz g;
//-----------------------------Testa Arquivos------------------------------
  if (argc > 3 ||argc < 3 ) {
    printf("Error to try read\n");
    //return 0;//finaliza programa
  }//if testa quantidade dos arquivos
//------------------------------Abre Arquivos------------------------------
  FILE *ArqEntrada  = fopen(argv[1], "r");
  FILE *ArqSaida    = fopen(argv[2], "w");

  int num = 0;

  if (ArqEntrada == NULL || ArqSaida == NULL) {
    printf("Error to open the file\n");
    return 0;//finaliza programa
  }//if testa abertura programas vazios
//---------------------------Primeiros Comandos Pilha Dinamica-------------
 //iniciar o grafo com a quantidade de vertices



  return 0;
}

// -----------------------------
// -----------------------------
