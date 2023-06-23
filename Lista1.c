#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//nós
typedef struct node{
    int value;
    struct node* next;
}Node;

//lista
typedef struct{
    Node *inicio;
    int tam;
}Lista;

//Remover
Node* remover(Lista *lista){
    Node *aux = lista->inicio;
    Node *anterior = NULL;

    if(aux == NULL)
        return NULL;

    while(aux->next != NULL){
        anterior = aux;
        aux = aux->next;
    }

    // remove o último nó
    if(anterior != NULL)
        anterior->next = NULL;
    else
        lista->inicio = NULL;

    lista->tam--;

    return aux;
}



void inserir_no_fim(Lista *lista, int num){
    Node *aux, *novo = malloc(sizeof(Node));
    
    if(novo){
        novo->value = num;
        novo->next = NULL;
        
        if(lista->inicio == NULL){
            lista->inicio = novo;
            lista->tam++;
        }
        else{
            aux = lista->inicio;
            while(aux->next != NULL)
                aux = aux->next;

            // Se o valor do último nó é igual ao número a ser inserido,
            // remove o último nó
            if(aux->value == num){
                remover(lista);
            }
            // Senão, insere um novo nó no final
            else{
                aux->next = novo;
                lista->tam++;
            }
        }
    }
    else{
        printf("Erro de alocação");
    }   
}





//imprime lista na tela 
void print_lista(Lista lista, int i){
    Node *no = lista.inicio;
    int tamanho, val;
    if(no == NULL){
        printf("0 -1\n");
    }
    else{
        while(no){
            val = no->value;
            no = no->next;
        }
    printf("%d %d", lista.tam, val);
    }
    printf("\n\n");
}


int main()
{
    clock_t start, end;
    double cpu_time_used;

    start = clock();

    int opc, ant, p;
    Lista lista;
    scanf("%d", &p);
    for (int i = 0; i < p; i++) {
        char teste[5];
        do{
            scanf("%s", teste);
            if (strcmp(teste, "END") == 0)
                break;
            
            else{
            int valor = atoi(teste);
            inserir_no_fim(&lista, valor);
            }
            
        }while(1);
        printf("caso %d: ", i);
        print_lista(lista, i);
        
        // Liberando a memória alocada
        while (lista.inicio) {
            remover(&lista);
        }


        lista.tam = 0;
    }

    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

    printf("Tempo de execução: %f segundos\n", cpu_time_used);

    return 0;
}
