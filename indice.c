#include <stdio.h>
#include <stdlib.h>


void verificar_int(int a, int b, char *teste){
  if(a != b)
    printf("  Erro de verificacao no %s: %d != %d \n", teste, a, b);
}

void verificar_str(char *a, char *b, char *teste){
  if(a == NULL || b == NULL || strcmp(a, b) != 0)
    printf("  Erro de verificacao no %s: %s != %s \n", teste, a, b);
}

void verificar_arranjo(int n, unsigned int *a, unsigned int *b, char *teste){
  int i;
  for(i = 0; i < n; i++){
    if(a[i] != b[i]){
      printf("  Erro de verificacao no %s: %d != %d (indice %d) \n", teste, a[i], b[i], i);
    }
  }
}

void verificar_ponteiro(void *p, char *teste){
  if(p == NULL)
    printf("  Erro de verificacao no %s: ponteiro nulo \n", teste);
}



/*Fim testes */


typedef struct elemento entrada;

struct elemento{ /* é permitida a alteração desta estrutura */
  char *termo;
  unsigned int *paginas;
  int n_paginas; /* quantidade de elementos do campo paginas */
  entrada *proximo; 
};

struct estrutura_indice{ 
    entrada *primeiro;
    unsigned int tamanho;
};

typedef struct estrutura_indice indice;

indice* criar_indice(){
    indice *ind = (indice*)malloc(sizeof(indice));
    ind->primeiro = NULL;
    ind->tamanho = 0;
    return ind;
}

unsigned int tamanho(indice *ind){
    return ind->tamanho;
}

void inserir_entrada(indice *ind, char *termo,unsigned int *paginas,int n_paginas){
    entrada *nova_entrada = (entrada*)malloc(sizeof(entrada));
    nova_entrada->termo = termo;
    nova_entrada->paginas = paginas;
    nova_entrada->n_paginas = n_paginas;
    nova_entrada->proximo = ind->primeiro;
    ind->primeiro = nova_entrada;
    ind->tamanho++;
}

void imprimir(indice *ind) {
    entrada *aux = ind->primeiro;
    while(aux){
        printf("%s,", aux->termo);
        for (int i = 0; i < aux->n_paginas; ++i) {
            printf(" %d", aux->paginas[i]);
            if (i < aux->n_paginas - 1) {
                printf(",");
            }
        }
        printf("\n");
        aux = aux->proximo;
    }
}

entrada* localizar(indice *ind, char *termo_de_busca){
    entrada *aux = ind->primeiro;
    for(unsigned int i = 1;i<ind->tamanho;i++){
        if(aux->termo == termo_de_busca){
            return aux;
        }
        else
        {
            aux = aux->proximo;
        }
    }
    return NULL;
}

void atualizar_entrada(indice *ind, char *termo, unsigned int *paginas, int n_paginas){
    entrada *atualizar = localizar(ind, termo);
    unsigned int *paginas_att = (unsigned int*)malloc(sizeof(unsigned int)* n_paginas);
    atualizar->paginas = paginas_att;
    if(atualizar){
        for(int i=0;i<n_paginas;i++){
            paginas_att[i] = paginas[i];
        }
    }
}

int main(){
  /*  TESTE 1 */
  indice* idc = criar_indice();
  verificar_int(0, tamanho(idc), "teste 1");
  
  /* TESTE 2 */
  unsigned int pgs_criptografia[] = {10};
  inserir_entrada(idc, "criptografia", pgs_criptografia, 1);
  unsigned int pgs_analise[] = {12, 27};
  inserir_entrada(idc, "análise", pgs_analise, 2);
  unsigned int pgs_complexidade[] = {2, 3, 5};
  inserir_entrada(idc, "complexidade", pgs_complexidade, 3);
  verificar_int(3, tamanho(idc), "teste 2");
  
  /* TESTE 3 */
  entrada *e = localizar(idc, "complexidade");
  verificar_ponteiro(e, "teste 3");
  verificar_str("complexidade", e->termo, "teste 3");
  verificar_arranjo(3, pgs_complexidade, e->paginas, "teste 3");

  /* TESTE 4 */
  unsigned int pgs_complexidade_2[] = {2, 3, 5, 6};
  atualizar_entrada(idc, "complexidade", pgs_complexidade_2, 4);
  e = localizar(idc, "complexidade");
  verificar_ponteiro(e, "teste 4");
  verificar_str("complexidade", e->termo, "teste 4");
  verificar_arranjo(4, pgs_complexidade_2, e->paginas, "teste 4");
  verificar_arranjo(3, pgs_complexidade, e->paginas, "teste 4");

  /* TESTE 5 */
  unsigned int pgs_argumento[] = {11, 12};
  inserir_entrada(idc, "argumento", pgs_argumento, 2);
  unsigned int pgs_classe[] = {8, 9, 7, 20, 21, 22};
  inserir_entrada(idc, "classe", pgs_classe, 6);
  unsigned int pgs_funcao[] = {51};
  inserir_entrada(idc, "função", pgs_funcao, 1);
  verificar_int(6, tamanho(idc), "teste 5");

  /* TESTE 6 */
  e = localizar(idc, "função");
  verificar_ponteiro(e, "teste 6");
  verificar_str("função", e->termo, "teste 6");
  verificar_arranjo(4, pgs_funcao, e->paginas, "teste 6");
  verificar_arranjo(3, pgs_funcao, e->paginas, "teste 6");

  /* Teste de impressão */
  imprimir(idc);

  return 0;
}