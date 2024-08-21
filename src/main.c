#include <stdio.h>

#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <locale.h>
#include <ctype.h>

char guessWords[][128] = {
    "league of legends",
    "venancio e pedrao",
    "roedores e bovinos",
    "dona izete",
    "joao tetris",
    "tamandua bailarino",
    "salmao a vacuo",
    "bigasdev",
    "green moon",
    "free spirit",
    "the wallers corp",
    "pan pan studios"
};
const char guessHints[][128] = {
    "Vicio",
    "Melhores amigos",
    "Melhores animais",
    "O real nome do professor de programacao",
    "O ultimo heroi da terra",
    "Estudio de jogos",
    "Estudio de jogos",
    "Estudio de jogos",
    "Estudio de jogos",
    "Estudio de jogos",
    "Estudio de jogos",
    "Estudio de jogos"
};

int seedSaved = 999;

typedef struct no {
    int id;
    int carteira;
    struct no *proximo;
}No;

typedef struct{
    No *inicio;
    int tam;
}Lista;

void criar_Lista(Lista *lista){
    lista->inicio = NULL;
    lista->tam = 0;
}

//procedimento para inserir no inicio
void inserir_no_inicio(Lista* lista, int num){
    No *novo = malloc(sizeof(No));

    if(novo){
        //Criando personagem
        novo->id = num;
        novo->carteira = 0;

        novo->proximo = lista->inicio;
        lista->inicio = novo;
        lista->tam++;

    }else
        printf("Erro ao alocar memoria!\n");
}

//procedimento para inserir no fim
void inserir_no_fim(Lista *lista, int num){
    No *aux, *novo = malloc(sizeof(No));

    if(novo){
        novo->id = num;
        novo->carteira = 0;
        novo->proximo = NULL;

        //Eh o primeiro?
        if(lista->inicio == NULL)
            lista->inicio = novo;
        else{
            aux = lista->inicio;
            while(aux->proximo)
                aux = aux->proximo;
            aux->proximo = novo;
        }
        lista->tam++;
    }else
        printf("Erro ao alocar memoria!\n");
}

//procedimento para inserir
void inserir_no_index(Lista *lista, int num, int index, int carteira){
    No *aux, *novo = malloc(sizeof(No));

    aux = lista->inicio;

    if(lista->inicio == NULL){
        printf("Erro ao alocar memoria!\n");
    } else {

        if(novo){
        novo->id = num;
        novo->carteira = carteira;


        if(index >= lista->tam){
            index = lista->tam - 1;
        }

        for(int i = 0; i<index; i++){
            aux=aux->proximo;
        }

        novo->proximo = aux->proximo;
        aux->proximo = novo;
        //lista->tam++;
        }

    }

}

//procedimento para remover
void remover_por_index(Lista *lista, int index){
    No *curChecando, *prevChecando;
    curChecando = lista->inicio;

    if(lista->inicio == NULL){
        return;
    }

    if(index >= lista->tam){
        index = lista->tam - 1;
    }

    //Muda o checando anterior para o proximo, e o current checando para o proximo
    for(int i = 0; i < index; i++){
        prevChecando = curChecando;
        curChecando = curChecando->proximo;
    }

    if(index>0){
        prevChecando->proximo = curChecando->proximo;
    //Inicio da lista vira o proximo da lista quando o index eh o primeiro
    }else{
        lista->inicio = curChecando->proximo;
    }

    free(curChecando);
    lista->tam--;
}

void procurar_id(Lista *lista, No **out, int id){
    No *no = lista->inicio;

    while(no){
        if(no->id == id){
            *out = no;
        }
        no = no->proximo;
    }
}

// Adiciona ou diminui quantidade de dinheiro para o jogador, pergunta a operacao e depois o valor em real
void dinheiro(Lista *lista, int jog, int op, int valor){
    No *no = lista->inicio;

    while(no){

        if(no->id == jog){

        //Adiciona quantidade de dinheiro para o jogador
        if(op == 1){
            no->carteira += valor;

        }

        //Remove todo o dinheiro do jogador
        else if(op == 2){
            no->carteira = valor*0;
            printf("Dinheiro zerado!!");

        }

        break;
        }

        no = no->proximo;

    }

}

// Muda o ranking dependendo do dinheiro
void ranking(Lista *lista){
    No *curChecando, *prevChecando;
    int index = lista->tam;
    No *maior;
    int maiorId;

    curChecando = lista->inicio;
    maior = lista->inicio;
    maiorId = maior->id;

    //Checa qual da lista tem mais dinheiro
    for(int i = 0; i<index; i++){
        if(i > 0 && curChecando->carteira > prevChecando->carteira){
            if(maior->carteira < curChecando->carteira){
                maior = curChecando;
                maiorId = maior->id;
            }
        }

        prevChecando = curChecando;
        curChecando = curChecando->proximo;
    }


    do{

    //Reseta curChecando depois de um loop
    curChecando = lista->inicio;
    prevChecando = curChecando;

    //Vai mover pra cima da lista se a pessoa tiver mais dinheiro que a anterior
    for(int i = 0; i<index;i++){
        if(i > 0 && curChecando->carteira > prevChecando->carteira){

            // Se for a segunda posicao da lista, jogador vai pra primeira
            if(i == 1) {
                inserir_no_index(lista, prevChecando->id, i, prevChecando->carteira);
                lista->inicio = curChecando;
            }
            else{
                inserir_no_index(lista, prevChecando->id, i, prevChecando->carteira);
                lista->tam++;
                remover_por_index(lista, i - 1);

            }
        }

        prevChecando = curChecando;
        curChecando = curChecando->proximo;

    }

    }while(lista->inicio->id != maiorId);

}

void esperar_input()
{
    printf("\nEnter para continuar");
    getchar();// deteccao de input
}

void imprimir(Lista lista){
    No *no = lista.inicio;

    printf("LEADERBOARD:\n\n");
    //printf("\n\tLista tam %d: \n", lista.tam);
    while(no){
        printf("\nID: %d \n", no->id);
        printf("Dinheiro: R$%d\n", no->carteira);

        no = no->proximo;
    }
    printf("\n\n");
}

// Precisa mudar a order para que ele pegue os ids ao inves de pegar quem ta proximo na fila
void hangman(Lista *lista){

    No *jogador = lista->inicio;
    int seed = 0;

    // Para nao repetir a seed da ultima vez
    do{
        seed = rand() % sizeof(guessWords)/sizeof(guessWords[0]);
    }while(seed == seedSaved);


    int wordLen = strlen(guessWords[seed]);
    int numCorrect = 0;
    int oldCorrect = 0;

    // Multiplicador de dinheiro
    int mult = 0;

    // Pega o tamanho da palavra e cada posicao do array da palavra vai ser igual a 0, quando for igual a 1 mudara para a letra certa
    int mask[wordLen];
    for(int i = 0; i < wordLen; ++i){
        if(isspace(guessWords[seed][i])){
            mask[i] = 1;
            numCorrect++;
        }else
            mask[i] = 0;
    }

    // Letra escrita pelo jogador
    char guess;

    // Operacao e quantidade de reais que serao usados
    int op = 0;
    int qtdReal = 0;

    // Loop fica rodando enquanto a palavra ainda nao foi encontrada
    while(numCorrect < wordLen){

        do{
            imprimir(*lista);
            printf("Turno do jogador %d", jogador->id);
            printf("\n\n\n\n");

            // Imprime a palavra
            printf(guessHints[seed]);
            printf("\n\n");
            for(int i = 0; i < wordLen; i++){
                if(mask[i] == 1){
                    printf("%c ", guessWords[seed][i]);
                } else printf("_ ");
            }

            getchar();
            esperar_input();

            // Pega uma operacao aleatoria da roda
            op = (rand() % 19) + 1;
            if(op > 4) //1->1,2->2,3->3,4->3,5->1,6->1,7->1,8->1,9->1
                op = 1;

            system("cls");
            printf("               .:^!7????JJJ??77!^:.\n");
            printf("           .^!?YPYP5PJY5?JJJP5JYYYYJ!^.\n");
            printf("        .^7?J7~JY5PY5Y5GY??5GY7!?5PYJYJ?~.\n");
            printf("      .!?J!^75?~?Y5PYPPGPJJGGY::^!~!!7J?YY7.\n");
            printf("     ~J?7Y?~^7PJ^?5P5YGPGJ5BG?5PY!^Y5Y7~?PP5~\n");
            printf("   .?Y?~?GP??!^5JY75P5PBB5GB5YBGYYYPJ?J5Y!7PP?.\n");
            printf("  :JJY5J?7!?Y5YJ75JY5PPP5YPP5GG5YPY5YY?77J75YYY:\n");
            printf(" .?JY5PGBG5YJYPP5J7~7YYJJJ???J?J5PYJ7?JYJY?7?JYJ.\n");
            printf(" !JY5YY5P5GGGPP555JJJJJJJJ???77?G5YP5YYYY55J?7JY!\n");
            printf(":??5GPGBGPPP5GPYJYYYJJJJ????????JYJ55YYYJJ?!!??YJ:\n");
            printf("~?J555PP5PPPPP5YY?JJJJJJ??????JJ?JPGGPP55YJ!!77YY~\n");
            printf("!?5Y?Y55YJJJ?J?YJ?JJJJJJJ????JJJJJPPGP555YJ77?JYY~\n");
            printf("!JYPJJJJJJJ?JJ7^??JJJJJJJJJJJJJJ??!J5555P5PPP55YJ~\n");
            printf("^JJ?7!7JJJ?J??J7?YJJJJJJJJJJJJJJY!:7?7!7!7?YY55Y?^\n");
            printf(".7J~7?7J?!7JJ5PP55G55YJJ???JJJJY5P5J7!7???^.7!7Y!.\n");
            printf(" :?J!~!7?YPGPPYPGBGPJ5J?JYY???77?Y5PPJ!^!~^!!^J?:\n");
            printf("  ^JYYPG5JPP5PBBGB57J5YYYPPJYY?JJJY?JY??J7!7~J?^\n");
            printf("   ^J555P5PPBBBGB5~?PYP5JGGYJP5?YY5J7?75GJ~7Y?^\n");
            printf("    .755YPGBBGG#Y!?GJPP5JPP5?YGPJYJYYJY??7JY!.\n");
            printf("      ^?555PPBG?!?BY5PP?^!!~:75P57J555YJJY7:\n");
            printf("        :7Y5PPPJ7GG?5PYJ7JYJ??7Y5??YJYJJ!:\n");
            printf("          .^7J5PPP5YY5JJYYP5YYJJJYYJ?!^.\n");
            printf("              .^!7JYY555555YYJJ?7~^.\n");
            printf("                    ...::::...\n");
            printf("\n");

            esperar_input();

            if(op != 1){
                // Se o jogador pegou bankrupt perde todo o dinheiro
                if(op == 2){
                    dinheiro(lista, jogador->id, 2, 0);
                    ranking(lista);
                    printf("\nJogador %d perdeu tudo e esta morando de aluguel", jogador->id);
                    esperar_input();
                } else{
                    printf("Jogador %d perdeu o turno mas passa bem", jogador->id);
                    esperar_input();
                }

                //Se jogador pegou bankrupt ou lose a turn entao o turno vai pro proximo (se for o ultimo da lista entao a lista voltara pro comeco)
                if(jogador->id < lista->tam) {
                    procurar_id(lista, &jogador, jogador->id+1);
                    system("cls");
                }else {
                    procurar_id(lista, &jogador, 1);
                    system("cls");
                }
            } else{
                qtdReal = ((rand() % 6) + 1) * 5;
                printf("jogador %d rodou %d na roda das rodas", jogador->id, qtdReal);
                esperar_input();
            }

        }while(op != 1);

        system("cls");
        // Imprime a palavra
        printf(guessHints[seed]);
        printf("\n\n");
        for(int i = 0; i < wordLen; i++){
            if(mask[i] == 1){
                printf("%c ", guessWords[seed][i]);
            } else printf("_ ");
        }
        printf("\nJogador %d esta chutando por %d reais", jogador->id, qtdReal);

        printf("\n\nEscreva uma letra: \n");
        scanf(" %c", &guess);

        oldCorrect = numCorrect;

        for(int i = 0; i < wordLen; i++) {

            // Caso letra ja foi escrita antes, jogo vai continuar (nao mudar para o proximo da ordem)
            if(mask[i] == 1) {
                if(guessWords[seed][i] == guess) {
                    break;
                }
                    continue;
            }

            // Se acertar, adiciona a letra na tela e aumenta a qtd de numeros corretos
            if( guess == guessWords[seed][i] ) {
                mult++;

                mask[i] = 1;
                numCorrect++;
            }

        }

        // Checa se o jogador errou ou nao
        if( oldCorrect == numCorrect){
            printf("\nJogador %d errou a letra!\n", jogador->id);
            esperar_input();
            getchar();

            // Se o jogador nao for o ultimo, muda pro proximo, senao volta pro primeiro id
            if(jogador->id < lista->tam) {
                procurar_id(lista, &jogador, jogador->id+1);


            }else {
                procurar_id(lista, &jogador, 1);
            }

            system("cls");

        }else{
            printf("\nJogador %d acertou a letra '%c' %d vez(es)!\n", jogador->id, guess, mult);
            esperar_input();
            getchar();

            dinheiro(lista, jogador->id, 1, qtdReal*mult);
            ranking(lista);
            mult = 0;

            //Caso for uma vogal, pula o turno
            if(guess == 'a' || guess == 'e' || guess == 'i' || guess == 'o' || guess == 'u') {
                if(jogador->id < lista->tam) {
                    procurar_id(lista, &jogador, jogador->id+1);
                }else {
                    procurar_id(lista, &jogador, 1);
                    }
            }


        }
        system("cls");
    }

    imprimir(*lista);
    printf("PARABENS JOGADOR %d", lista->inicio->id);
    printf("\n\nA palavra certa:\n%s\n", guessWords[seed]);
    seedSaved = seed;
    esperar_input();

    system("cls");

}

int main(){

    srand(time(NULL));
    setlocale(LC_ALL,"Portuguese");

    int opcao, operador, valor;
    int id = 0;
    int turno = 0;

    //No *lista NULL;
    Lista lista;

    criar_Lista(&lista);
    inserir_no_fim(&lista, 1);
    inserir_no_fim(&lista, 2);
    inserir_no_fim(&lista, 3);

    printf("Quantos turnos voce quer?\n");
    scanf("%d", &turno);
    system("cls");

    for(int i = 0; i < turno; i++){
        printf("TURNO [%d/%d]\n", i+1, turno);
        hangman(&lista);
    }

    return 0;
}
