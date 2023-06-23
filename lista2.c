#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

typedef struct node {
    int data;
    struct node *next;
} Node;

Node* createNode(int data) {
    Node* newNode = (Node*) malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Falha na alocação de memória.\n");
        return NULL;
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

//imprime lista na tela 
char* print_lista(Node **array, int j){
    Node **no = array;
    int val;
    char* result = (char*) malloc(100 * sizeof(char));  // assumindo que 100 caracteres são suficientes para cada resultado
    if(no == NULL){
        sprintf(result, "\n");
    }
    else{
        result[0] = '\0';  // Inicializa a string result com uma string vazia
        for(int i = 0; i < j; i++){
            Node* current = no[i];
            while(current){
                val = current->data;
                current = current->next;
            }
            // Concatena o valor à string result
            char temp[12];  // Buffer para converter o int em string
            if(i < j-1)
                sprintf(temp, "%d ", val);  // Adiciona espaço após cada número para legibilidade
            else
                sprintf(temp, "%d", val);  // Adiciona espaço após cada número para legibilidade
            strcat(result, temp);  // Concatena as strings
        }
    }
    return result;
}


int main() {
    clock_t start, end;
    double cpu_time_used;

    start = clock();
    int arraySize = 2; //É modificado ao longo do código
    char cor[3], col[3]; //coluna e cor
    int flag,p=0;
    
    
    scanf("%d",&p);
    // cria a matriz para armazenar os resultados de cada caso
    char** results = (char**) malloc(p * sizeof(char*));
    for (int i = 0; i < p; i++) {
        int j = 0;
        Node** array = (Node**) malloc(arraySize * sizeof(Node*)); //array para alocar o nó
        if (array == NULL) {
            printf("Falha na alocação de memória.\n");
            return -1;
        }

        Node* head = calloc(1, sizeof(Node)); //head da lista
        
        if (head == NULL) {
            printf("Falha na alocação de memória.\n");
            return -1;
        }
        do{
                scanf("%s", col);
                if (strcmp(col, "END") == 0)
                    break;
                
                else{
                scanf("%s", cor);
                if (j >= arraySize) {
                    arraySize *= 2;  // Duplicamos o tamanho do array
                    Node **newArray = realloc(array, arraySize * sizeof(Node *));
                    if (newArray == NULL) {
                        printf("Falha na realocação de memória.\n");
                        return -1;
                    }
                    array = newArray;
                }
                int col_int = atoi(col);
                int cor_int = atoi(cor);
                if(col_int == 0)
                    flag = 2;
                for (int K = 0; K < j; K++) {
                    Node* current = array[K];
                        if(col_int == current->data){
                            //printf("igual a coluna %d\n", current->data);
                            flag = 1;
                            Node* aux = malloc(sizeof(Node));
                            Node *anterior = NULL;
                            aux = current;
                            while (aux->next != NULL)
                            {
                                anterior = aux;
                                aux = aux->next;
                            }
                            // remove o último nó
                            //printf("aux->data = %d\n", aux->data);
                            if(aux->data == cor_int){
                            if(anterior != NULL)
                                anterior->next = NULL;    
                            }
                            else{
                            Node* newNode = createNode(cor_int);
                            while (aux->next != NULL)
                            {
                                aux = aux->next;
                            }
                            aux->next = newNode;
                            aux = newNode;
                            
                            }
                            j--;
                        }
                }
                

                if(flag == 0){
                    head = createNode(head->data+1);
                    Node* current = head;
                        Node* newNode = createNode(cor_int);
                        if (newNode == NULL) {
                            printf("Falha na alocação de memória.\n");
                            return -1;
                        }
                        current->next = newNode;
                        current = newNode;
                
                }
                if(flag == 2){
                // Criar uma nova coluna
                head = createNode(head->data+1);
                array[j] = head;  // Adicionar a nova coluna no final

                // Mover todos os nós uma coluna para a direita
                for (int K = j; K > 0; K--) {
                    array[K]->next = array[K-1]->next;
                }

                // Adicionar o novo nó na primeira coluna
                Node* newNode = createNode(cor_int);
                if (newNode == NULL) {
                    printf("Falha na alocação de memória.\n");
                    return -1;
                }
                array[0]->next = newNode;
                }

                flag = 0;
                }
                array[j] = head;
                j++;
                array[j] = NULL;

                //Verifica se tem coluna Nula:
                for (int K = 0; K < j; K++) {
                    Node* current = array[K];
                    if(current->next == NULL){
                        int temp;
                        for (int K = current->data-1; K < j; K++) {
                            array[K] = array[K+1];
                            if(array[K] != NULL){
                                array[K]->data = array[K]->data-1;
                            }
                            temp = K;
                        }
                        j--;
                        break;
                    }
                }
            }while(1);
            // armazena o resultado na matriz
            results[i] = print_lista(array, j);
            
            // Vamos imprimir os dados para verificar
            j--;
    for (int K = 0; K < j; K++) {
        Node* current = array[K];
        while (current != NULL) {
            printf("%d -> ", current->data);
            current = current->next;
        }
        printf("NULL\n");
    }

            // Liberando a memória quando terminar
            for (int K = 0; K < j; K++) {
                Node* current = array[K];
                while (current != NULL) {
                    Node* temp = current;
                    current = current->next;
                    free(temp);
                }
            }
            free(array);

    }
    // agora, imprime todos os resultados
    for (int i = 0; i < p; i++) {
        printf("caso %d: %s\n", i, results[i]);
    }

    // libera a memória alocada
    for (int i = 0; i < p; i++) {
        free(results[i]);
    }
    free(results);

    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

    //printf("Tempo de execução: %f segundos\n", cpu_time_used);
    return 0;
}
