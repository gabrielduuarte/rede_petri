
#include<stdio.h>
#include<stdlib.h>

#define MAX 15
#define GAME 1

int * token(int nlug);
void arc_consumidores(int ncon, int a_con[MAX][MAX]);
void arc_produtor(int apro, int a_pro[MAX][MAX]);

int main(void)
{
    int i;
    int nlug,           /* Quantidade de lugares */
        *tok,           /* Quantidade de Tokens */
        ntran,          /* Quantidade de transicoes */
        ncon,           /* Quantidade de arcos consumidores (lugar para transicao) */
        a_con[MAX][MAX],/* Matriz do arco consumidor */
        apro,           /* Quantidade de arcos produtores (transicao para lugar) */
        a_pro[MAX][MAX]; /* Matriz do arco produtor */

    
    /*Recebe os lugares*/
    scanf("%d", &nlug);
    printf("Quantidade de lugares: %d\n", nlug);

    /*Recebe os tokens*/
    tok=token(nlug);
    for(i=0; i<nlug; i++)    /*Recebe os tokens dependendo da quantidade de lugares */
        printf("Tokens em respectivos lugares: tok[%d]: %d\n", i, tok[i]);

    /*Recebe a quantidade de transicoes*/
    scanf("%d", &ntran);
    printf("Quantidade de transicoes: %d\n", ntran);

    scanf("%d", &ncon);
    printf("Quantidade de arcos consumidores: %d\n", ncon);

    /* Passa numero de arcos consumidores e a matriz pra preencher */
    arc_consumidores(ncon, a_con);

    scanf("%d", &apro);
    printf("Quantidade de arcos produtores: %d\n", apro);
    
    /* Passa numero de arcos produtores e a matriz para preenche */
    arc_produtor(apro, a_pro);

    /*rede_p(nlug, tok, a_con, a_pro);*/


    return 0;
}

int * token(int nlug)
{
    int i; 
    static int tok[MAX];
    for(i=0; i<nlug; i++)
        scanf("%d", &tok[i]);

    return tok;
}

void arc_consumidores(int ncon, int a_con[MAX][MAX])
{
    int i, lug, tran, rot;

    for(i=0; i<ncon; i++)
    {
        scanf("%d %d %d", &lug, &tran, &rot);
        a_con[lug][tran]=rot;
        printf("Arco consumidor: A_con[%d][%d]: %d\n", lug, tran, a_con[lug][tran]);
    }
    
    return;
}

void arc_produtor(int apro, int a_pro[MAX][MAX])
{
    int i, lug, tran, rot;

    for(i=0; i<apro; i++)
    {
        scanf("%d %d %d", &tran, &lug, &rot);
        a_pro[tran][lug]=rot;
        printf("Arco produtor: A_pro[%d][%d]: %d\n", tran, lug, a_pro[tran][lug]);
    }
    return;
}

