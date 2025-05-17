#include <stdio.h>
#include <stdlib.h>
#include "list.h"


typedef struct{
   int sudo[9][9];
}Node;

Node* createNode(){
  Node* n=(Node*) malloc(sizeof(Node));
  return n;
}

Node* copy(Node* n){
    Node* new=(Node*) malloc(sizeof(Node));
    *new = *n;
    return new;
}

Node* read_file (char* file_name){
  Node* n = createNode();
  FILE* file = fopen (file_name, "r");
  int i,j;
  for(i=0;i<9;i++){
       for(j=0;j<9;j++){
          if(!fscanf (file, "%d", &n->sudo[i][j]))
            printf("failed to read data!");
       }
  }

  fclose (file);
  return n;
}

void print_node(Node* n){
    int i,j;
    for(i=0;i<9;i++){
       for(j=0;j<9;j++)
          printf("%d ", n->sudo[i][j]);
       printf("\n");
    }
    printf("\n");
}

int is_valid(Node* n){
    int i, j, k;
    int fil[9][10] = {0};
    int col[9][10] = {0};
    int subMat[3][3][10] = {0};

    for (i = 0; i < 9; i++) {
        for (j = 0; j < 9; j++) {
            if (n -> sudo[i][j] != 0) {
                k = n -> sudo[i][j];
                if (fil[i][k] || col[j][k] || subMat[i / 3][j / 3][k]) {
                    return 0;
                }
                fil[i][k] = col[j][k] = subMat[i / 3][j / 3][k] = 1; //asigno encadenadamente (me lo recomendo GPT)
            }
        }
    }
  return 1;
}


List* get_adj_nodes(Node* n){
    List* list=createList();
    int filaVacia = -1;
    int colVacia = -1;
    int encontradoVacio = 0;

    for (int i = 0; i < 9 && !encontradoVacio; i++) {
        for (int j = 0; j < 9 && !encontradoVacio; j++) {
            if (n->sudo[i][j] == 0) {
                filaVacia = i;
                colVacia = j;
                encontradoVacio = 1;
                break;
            }
        }
        if (encontradoVacio) {
            break;
        }
    }

    if (filaVacia == -1 || colVacia == -1) { // Todas las casillas llenas
        return list;
    }

    for(int i = 1; i <= 9; i++) {
        Node* newNode = copy(n);
        newNode->sudo[filaVacia][colVacia] = i;

        if (is_valid(newNode)) {
            pushBack(list, newNode);
        } else {
            free(newNode);
        }
    }

    return list;
}


int is_final(Node* n){
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      if (n -> sudo[i][j] == 0) {
        return 0;
      }
    }
  }
  return 1;
}
/*
Node* DFS(Node* initial, int* cont){
  Stack* stack = createStack();
  if (stack == NULL) {
    if (cont != NULL) *cont = 0;
    free(initial);
    return NULL;
  }

  push(stack, initial);
  if (cont != NULL) *cont = 0;

  Node* current = NULL;
  List* adj = NULL;

  while (!is_empty(stack)) {
    current = top(stack);

    if (cont != NULL) (*cont)++;

    if (is_final(current)) {
      if (is_valid(current)) {
        clean(stack);
        return current;
      }
    }

    adj = get_adj_nodes(current);
    if (adj == NULL) {
      pop(stack);
      free(current);
      return NULL;
    }

    void *it = first(adj);
    while(it != NULL) {
      push(stack, it);
      it = next(adj);
    }

    free(current);
    clean(adj);
    return NULL;
}
*/


/*
int main( int argc, char *argv[] ){

  Node* initial= read_file("s12a.txt");;

  int cont=0;
  Node* final = DFS(initial, &cont);
  printf("iterations:%d\n",cont);
  print_node(final);

  return 0;
}*/