
typedef struct elemento entrada; /* NÂO é permitida a alteração desta instrução */

struct elemento{ /* é permitida a alteração desta estrutura */
  char *termo;
  unsigned int *paginas;
  int n_paginas; /* quantidade de elementos do campo paginas */
  entrada *proximo;
};



struct estrutura_indice{ /* Você DEVE definir os campos desta estrutura de acordo com sua implementação de índice */
  entrada *primeiro;
  unsigned int tamanho;
};

typedef struct estrutura_indice indice; /* NÂO é permitida a alteração desta instrução */

/* NÃO é permitida a alteração dos protótipos das funções a seguir */
indice* criar_indice(); /*OK*/
unsigned int tamanho(indice *ind); /*OK*/
entrada* localizar(indice *ind, char *termo_de_busca); /*OK*/
void inserir_entrada(indice *ind, char *termo, unsigned int *paginas, int n_paginas); /*OK*/
void atualizar_entrada(indice *ind, char *termo, unsigned int *paginas, int n_paginas); /*??*/
void imprimir(indice *ind); /*OK*/
