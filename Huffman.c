/*obs: para construção da árvore de Huffman foi adotado o padrão de inserção de folhas à direita e de àrvores no ramo da esquerda*/
#include<stdio.h>
#include<stdlib.h>

typedef struct sNo{
    char infoCh; // guarda qual char está sendo representado
    int infoNum; // guarda soma de frequências (definição de Huffman)
    struct sNo* dir; // aponta para ramo da direita
    struct sNo* esq; // aponta para ramo da esquerda
}NO;

typedef struct sLista{
    NO* info; // endereço para o nó
    struct sLISTA* prox;
}LISTA;


void ordenaMatr(int** elem){
    int aux0;
    int aux1;
    for (int i = 0; i < 53; i++)
            {
                for (int j = 0; j < 53; j++)
                {
                    if (elem[i][0] < elem[j][0])
                    {
                        aux0 = elem[i][0];
                        aux1 = elem[i][1];
                        elem[i][0] = elem[j][0];
                        elem[i][1] = elem[j][1];
                        elem[j][0] = aux0;
                        elem[j][1] = aux1;
                    }
                }
            }
}

LISTA* initLista(){
    LISTA* lista;
    lista = (LISTA*)malloc(sizeof(LISTA));
    lista->info = NULL;
    lista->prox = NULL;
    return lista;
}

LISTA* novoLista(){ // novo nó na lista
    LISTA* lista = initLista();
    lista->info = NULL;
    lista->prox = NULL;
    return lista;
}

LISTA* busca(LISTA* ptr){
    LISTA* aux = (LISTA*)malloc(sizeof(LISTA));
    aux = ptr;
    if(ptr -> prox == NULL)
        return ptr;
    while(aux->prox != NULL){
        aux = (LISTA*) (aux -> prox);
    }
    return aux;
}

void addLista(LISTA* ptr, NO* novo){ // cria nó na lista com um elemento da futura árvore
    LISTA* aux = busca(ptr);
    LISTA* lista = novoLista();
    aux->prox = (struct sLISTA*) lista; // adiciona nó na lista
    lista->info = novo; // nó da lista recebe nó da futura árvore
}

void novoNo(LISTA* ptr,char info, int freq){
    NO* novo;
    novo = (NO*) malloc(sizeof(NO));
    novo->infoCh = info;
    novo->infoNum = freq;
    novo->dir = NULL;
    novo->esq = NULL;
    addLista(ptr,novo);

}

int swt(int aux){ // switch para atualizar frequência de char

    if(aux >= 65 && aux <= 90){
        aux = aux - 65;
        return aux;
    }else if(97 <= aux && aux <= 122){
        aux = aux - 71;
        return aux;
    }else { // if aux == 32
        return 52; // últia posição eh reservada para " " (espaço)
    }
}

NO* novoArvore(int freq){
    NO* novo;
    novo->infoNum = freq;
    novo->infoCh = '*';
    novo->dir = NULL;
    novo->esq = NULL;
    return novo;
}

void limpaLista(LISTA* ptr){ // apaga os campos da lista que não estão sendo utilizados (os dois primeiros elementos )
    LISTA* aux = ptr;
    aux =(LISTA*) aux->prox;
    aux =(LISTA*) aux->prox;
    ptr = aux;
}

void insereNo(LISTA* ptr,NO* novo){ // insere a raiz na lista de forma ordenada
    int i = 0; //recebe 1 quando o nó foi inserido
    LISTA* aux1 =(LISTA*) ptr->prox; // auxiliar para percorrer lista
    LISTA* aux2 = ptr;
    LISTA* novo_lista = novoLista();
    novo_lista->info = novo;
    
    if((ptr->info)->infoNum > novo->infoNum){ // insere no início
            novo_lista->prox = ptr->prox;
            ptr = novo_lista;
            i = 1;
        }
    
    if(i != 1){ 
        while(i != 1){
        if((aux1->info)->infoNum < novo->infoNum){ // caminha pela lista
            aux1 =(LISTA*) aux1->prox;
            aux2 =(LISTA*) aux2->prox;
        }else if((aux1->info)->infoNum > novo->infoNum){ // insere no meio
            aux2->prox =(LISTA*) novo_lista;
            novo_lista->prox =(LISTA*) aux1;
            i = 1;
        }else{ // insere no fim
            aux1->prox = novo_lista;
            novo_lista->prox = NULL;
            i = 1;
        }
    }
    }
}

void passoHuffman(LISTA* ptr){ 
    int freq = 0;
    LISTA* aux1 = ptr;
    LISTA* aux2 =(LISTA*) ptr->prox;

    while(ptr->prox != NULL){

        freq = ((aux1->info)->infoNum) + ((aux2->info)->infoNum); // frequência total da nova raiz 

        NO* novo = novoArvore(freq); // cria novo nó

        if((aux1->info)->infoCh == '*' && (aux2->info)->infoCh != '*'){ //campo char do elemento com valor "*" representa uma raiz
            novo->infoCh = '*';
            novo->dir = aux2;
            novo->esq = aux1;        
        }else if((aux1->info)->infoCh != '*' && (aux2->info)->infoCh == '*'){
            novo->infoCh = '*';
            novo->dir = aux1;
            novo->esq = aux2;         
        }else if((aux1->info)->infoCh == '*' && (aux2->info)->infoCh == '*' || (aux1->info)->infoCh != '*' && (aux2->info)->infoCh != '*'){ 
            if((aux1->info)->infoNum > (aux2->info)->infoNum ){
                novo->infoCh = '*';
                novo->dir = aux1;
                novo->esq = aux2;
            }else{
                novo->infoCh = '*';
                novo->dir = aux2;
                novo->esq = aux1;
            }
        }

        limpaLista(ptr);

        insereNo(ptr,novo);
    }
    
}

int main(){
    FILE* fileR; // path para leitura do arquivo
    FILE* fileW; // paths para escrita 
    int vetInicial[53][2]; //guarda as frequencias das letras em [x][0] e qual o char em [x][1]
    LISTA* ptr = initLista(); // aponta para raiz (inicializado com NULL)
    int aux = 0,i = 0, j = 0, aux2 = 0, menor = 600; // 600 é apenas um valor arbitrário e alto para "menor"

    fileR = fopen("entrada.txt","r");
    //fileW = fopen("entrada.txt","w");
    
    printf("0 - compactar / 1 - descompactar: ");
    scanf("%d",&aux);

    switch(aux){ // case 0 - compactar / case 1 - descompactar

        case 0:

            aux = 0; // limpando aux

            for(int i = 0; i < 53; i++){ // inicializa a matriz dizendo por [i][1] qual eh o char responsável pela frequência em [i][0]
                
                if(i < 25 || i == 25) // intervalo de maiúsculas
                    vetInicial[i][1] = i + 65;
                else if(26 <= i && i <= 51) // intervalo de minúsculas
                    vetInicial[i][1] = i + 71;
                else // i == 52
                    vetInicial[i][1] = 32; // 32 == espaço (ASCII)
            }


            int j = 0;
            do{ // inicializando vetor de frequência
                    vetInicial[j][0] = 0;
            j++;
            }while(j != 53);

            int temp = 0;

            do{ // lê arquivo e conta frequencia
                
                aux = fgetc(fileR); //leitura char por char do arquivo

                if(aux != -1)
                    temp = swt(aux); // retorna posição do da matriz responsável pela letra encontrada no arquivo
                    vetInicial[temp][0] += 1;
                    temp = 0;
            }while(aux != -1); // -1 eh o retorno de fgetc() para EOF

            /*for(int i = 0; i<53; i++){
                printf("%c",vetInicial[i][1]);
                printf("%d\n",vetInicial[i][0]);
            }*/

            j = 0;

            while(i < 53){
                int temp = vetInicial[j][0];
                    if(temp != 0){
                        if(menor > temp){
                            menor = temp;
                            vetInicial[j][0] = 0; // zera a frequência e não eh mais considerado na proxima passagem pela matriz
                            aux2 = j;
                        }
                        if(j == 52){ // chegou à última posição
                            i = 0;
                            j = 0; // reinicia o contador para percorrer a matriz
                            novoNo(ptr,vetInicial[aux2][1],vetInicial[aux2][0]);
                            aux2 = 0;
                            menor = 600; // reiniciando 
                        }
                    }else{
                        if(i == 53){
                            continue;
                        }
                        i++; // para cada zero encontrado
                        }
                j++;
            }

            passoHuffman(ptr); // ira construir a árvore

            break;

    case 1:
        aux = 0;
    break;

    } // fim do switch
    pclose(fileR);
    //pclose(fileW);
    return 0;

}


