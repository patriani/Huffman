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

void initLista(LISTA** lista){
    (*lista) = NULL;
}

LISTA* novoLista(){ // novo nó na lista
    LISTA* lista = NULL;
    lista = (LISTA*)malloc(sizeof(LISTA));
    lista->info = NULL;
    lista->prox = NULL;
    return lista;
}

LISTA* busca(LISTA* ptr){
    LISTA* aux = (LISTA*)malloc(sizeof(LISTA));
    aux = ptr;
    if(ptr == NULL || ptr->prox == NULL)
        return ptr;
    while(aux->prox != NULL){
        aux = (LISTA*) (aux -> prox);
    }
    return aux;
}

/*
void addLista(LISTA** ptr, NO* novo){ // cria nó na lista com um elemento da futura árvore
    LISTA* aux = busca((*ptr)); // aux recebe endereço do último elemento da lista
    LISTA* lista = novoLista(); // um nó de lista
    aux->prox = (struct sLISTA*) lista; // adiciona nó na lista
    lista->info = novo; // nó da lista recebe nó da futura árvore
}

void novoNo(LISTA** ptr,char info, int freq){
    NO* novo;
    novo = (NO*) malloc(sizeof(NO));
    novo = NULL;
    novo->infoNum = freq;
    novo->infoCh = info;
    addLista(ptr,novo);

}*/



NO* novoNo(char info, int freq){
    NO* novo;
    novo = NULL;
    novo = (NO*) malloc(sizeof(NO));
    novo->infoNum = freq;
    novo->infoCh = info;
    return novo;
}

void addLista(LISTA** ptr, char info, int freq){ // cria nó na lista com um elemento da futura árvore
    LISTA* aux = busca((*ptr)); // aux recebe endereço do último elemento da lista
    LISTA* lista = novoLista(); // um nó de lista
    NO* novo = novoNo(info,freq);
    lista->info = novo; // nó da lista recebe nó da futura árvore
    if((*ptr) == NULL )
        (*ptr) =  lista; 
    else
        aux->prox = (struct sLISTA*) lista; // adiciona nó na lista
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

void limpaLista(LISTA** ptr){ // apaga os campos da lista que não estão sendo utilizados (os dois primeiros elementos )
    LISTA* aux = (*ptr);
    aux =(LISTA*) aux->prox;
    aux =(LISTA*) aux->prox;
    (*ptr) = aux;
} 

void insereNo(LISTA** ptr,NO* novo){ // insere a raiz na lista de forma ordenada
    int i = 0; //recebe 1 quando o nó foi inserido
    LISTA* aux1 =(LISTA*) (*ptr)->prox; // auxiliar para percorrer lista
    LISTA* aux2 = (*ptr);
    LISTA* novo_lista = novoLista();
    novo_lista->info = novo;
    
    if(((*ptr)->info)->infoNum > novo->infoNum){ // insere no início
            novo_lista->prox = (*ptr)->prox;
            (*ptr) = novo_lista;
            i = 1;
        }
    
    if(i != 1){ 
        while(i != 1){
        if((aux1->info)->infoNum < novo->infoNum){ // caminha pela lista
            aux1 =(LISTA*) aux1->prox;
            aux2 =(LISTA*) aux2->prox;
        }else if((aux1->info)->infoNum > novo->infoNum){ // insere no meio
            aux2->prox = (struct sLISTA*)novo_lista;
            novo_lista->prox =(struct sLISTA*) aux1;
            i = 1; // condição de saída
        }else{ // insere no fim
            aux1->prox =(struct sLISTA*) novo_lista;
            novo_lista->prox = NULL;
            i = 1; // condição de saída
        }
    }
    }
}


void passoHuffman(LISTA** ptr){ 
    int freq = 0;
    int freq1 = 0,freq2 = 0;
    LISTA* aux1 = NULL;
    aux1 = (*ptr);
    LISTA* aux2 = NULL;
    aux2 = (LISTA*) (*ptr)->prox;
    NO* temp = NULL;

    if((*ptr) != NULL){
        //printf("%d",(aux1->info)->infoNum);
        while((*ptr)->prox != NULL){
            //printf("\n\n\nentrou no while");
            
            temp = (aux1->info);
            freq1 = temp->infoNum;
            temp = (aux2->info);
            freq2 = (temp->infoNum);
            freq =  freq1 + freq2; // frequência total da nova raiz 
            temp = NULL;

            NO* novo = novoArvore(freq); // cria novo nó

            if((aux1->info)->infoCh == '*' && (aux2->info)->infoCh != '*'){ //campo char do elemento com valor "*" representa uma raiz
                novo->infoCh = '*';
                novo->dir = aux2->info;
                novo->esq = aux1->info;        
            }else if((aux1->info)->infoCh != '*' && (aux2->info)->infoCh == '*'){
                novo->infoCh = '*';
                novo->dir = aux1->info;
                novo->esq = aux2->info;         
            }else if((aux1->info)->infoCh == '*' && (aux2->info)->infoCh == '*' || (aux1->info)->infoCh != '*' && (aux2->info)->infoCh != '*'){ 
                if((aux1->info)->infoNum > (aux2->info)->infoNum ){
                    novo->infoCh = '*';
                    novo->dir = aux1->info;
                    novo->esq = aux2->info;
                }else{
                    novo->infoCh = '*';
                    novo->dir = aux2->info;
                    novo->esq = aux1->info;
                }
            }

            limpaLista(ptr);

            insereNo(ptr,novo);
        }
    }
}

int main(){
    FILE* fileR; // path para leitura do arquivo
    FILE* fileW; // paths para escrita 
    int vetInicial[53][2]; //guarda as frequencias das letras em [x][0] e qual o char em [x][1]
    LISTA* ptr ; // aponta para raiz (inicializado com NULL)
    int aux = 0,i = 0, j = 0, aux2 = 0, menor = 600; // 600 é apenas um valor arbitrário e alto para "menor"
    int temp = 0;

    initLista(&ptr);

    fileR = fopen("entrada.txt","r"); //abre arquivo para leitura
    fileW = fopen("saida.dvz","a"); // abre arquivo para escrita
    
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

            while(i < 53){ // adiciona nós na lista encadeada com as raízes 
                int temp = vetInicial[j][0];
                    if(temp != 0){
                        if(menor > temp){
                            menor = temp;
                            aux2 = j;
                        }
                        if(j == 52){ // chegou à última posição
                            i = 0; // o contador de zeros reinicia para não contar novamente os elementos de frequência nula da leitura anterior
                            char tempCh = vetInicial[aux2][1];
                            //printf("%d , %c", tempCh);
                            //novoNo(&ptr,tempCh,vetInicial[aux2][0]);           
                            addLista(&ptr,tempCh,vetInicial[aux2][0]);
                            vetInicial[j][0] = 0; // zera a frequência e não eh mais considerado na proxima passagem pela matriz
                            aux2 = 0;
                            j = 0; // reinicia o contador para percorrer a matriz
                            menor = 600; // reiniciando 
                        }
                    }else{
                        if(i == 53)
                            continue;
                        i++; // para cada zero encontrado
                        }
                j++;
            }
            printf("%d",((ptr->info)->infoNum));
            passoHuffman(&ptr); // ira construir a árvore

            

            break;

    case 1:
        aux = 0;
    break;

    } // fim do switch
    pclose(fileR);
    //pclose(fileW);
    return 0;

}


