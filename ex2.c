
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define MAX 256
#define GAME 1
#define VOLTA -1

int * token(int nlug);
void arc_consumidores(int nacon, int a_con[MAX][MAX]);
void arc_produtor(int napro, int a_pro[MAX][MAX]);
void simulador(int nlug, int *tok, int ntran, int a_con[MAX][MAX], int a_pro[MAX][MAX]);
void sorteia_trans(int tran[], int ntran);
int ativa_tran(int a_con[MAX][MAX], int a_pro[MAX][MAX], int tran, int nlug, int *tok);
void produz_token(int a_pro[MAX][MAX], int tran, int nlug, int *tok);
/*int final(int a_con[MAX][MAX], int a_pro[MAX][MAX], int lugar[MAX], int tran, int nlug, int *tok);*/

int main(void)
{
    int i;                  
    int nlug,               /* Numero de lugares */
        *tok,               /* Tokens */
        ntran,              /* Numero de transicoes */
        nacon,              /* Numero de arcos consumidores (lugar para transicao) */
        a_con[MAX][MAX],    /* Arcos consumidores */
        napro,              /* Quantidade de arcos produtores (transicao para lugar) */
        a_pro[MAX][MAX];    /* Arcos produtores */

    srand(time(NULL));
    
    /*Recebe os lugares*/
    scanf("%d", &nlug);
    printf("Quantidade de lugares: %d\n", nlug);

    /*Recebe os tokens*/
    tok=token(nlug);
    for(i=0; i<nlug; i++)    /*Recebe os tokens dependendo da quantidade de lugares */
        printf("Tokens no lugar %d: %d\n", i, tok[i]);

    /*Recebe a quantidade de transicoes*/
    scanf("%d", &ntran);
    printf("Quantidade de transicoes: %d\n", ntran);

    scanf("%d", &nacon);
    printf("Quantidade de arcos consumidores: %d\n", nacon);

    /* Passa numero de arcos consumidores e a matriz pra preencher */
    arc_consumidores(nacon, a_con);

    scanf("%d", &napro);
    printf("Quantidade de arcos produtores: %d\n", napro);
    
    /* Passa numero de arcos produtores e a matriz para preenche */
    arc_produtor(napro, a_pro);

    simulador(nlug, tok, ntran, a_con, a_pro);

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

void arc_consumidores(int nacon, int a_con[MAX][MAX])
{
    int i, lug, tran, rot;

    for(i=0; i<nacon; i++)
    {
        scanf("%d %d %d", &lug, &tran, &rot);
        a_con[lug][tran]=rot;
        printf("Arco consumidor: Do lugar %d para a transicao %d com peso %d\n", lug, tran, a_con[lug][tran]);
    }
    
    return;
}

void arc_produtor(int napro, int a_pro[MAX][MAX])
{
    int i, lug, tran, rot;

    for(i=0; i<napro; i++)
    {
        scanf("%d %d %d", &tran, &lug, &rot);
        a_pro[tran][lug]=rot;
        printf("Arco produtor: Da transicao %d para o lugar %d com peso %d\n", tran, lug, a_pro[tran][lug]);
    }
    return;
}

void simulador(int nlug, int *tok, int ntran, int a_con[MAX][MAX], int a_pro[MAX][MAX])
{
    int i, count=0;
    int tran[ntran];

    while(count < 5)
    { 
        printf("Transicoes sorteadas\n");
        sorteia_trans(tran, ntran);
        for(i=0; i<ntran; i++)
            printf("%d ", tran[i]);
        printf("\n");

        for(i=0; i<ntran; i++)
        {
            if(ativa_tran(a_con, a_pro, tran[i], nlug, tok))
                break;
        }
        count++;
        /*lembrar que acaba o prog quando nenhuma transicao estiver habilitada */
    }

    for(i=0;i<nlug;i++)
        printf("Tokens no lugar %d: %d\n", i, tok[i]);
}

    
void sorteia_trans(int tran[], int ntran)
{
    int i, j;

    for(i=0; i<ntran; i++)
    {
        tran[i]=rand()%ntran;
        for(j=0; j<i; j++)
        {
            if(tran[i]==tran[j])
            {
                tran[i]=rand()%ntran;
                j=VOLTA;
            }
        }
    }

}

int ativa_tran(int a_con[MAX][MAX], int a_pro[MAX][MAX], int tran, int nlug, int *tok)
{
    int i, lugar[MAX]={}, savelugar[MAX];

    for(i=0; i<nlug; i++)
    {
        if(a_con[i][tran]!=0) /*verificar quais lugares apontam para a mesma transicao*/
            lugar[i]=i;
    }
    
    for(i=0; i<nlug; i++)
    {
        if(lugar[i]==i)/*Diz quais sao os lugares que apontam para a mesma tran*/
        {
            if(a_con[lugar[i]][tran]<=tok[lugar[i]])/*verifica se ativa a transicao*/
            {
                printf("Lugar %d para a transicao %d ativada\n", i, tran);
                savelugar[i]=i; /* salva os lugares que apontam para a transicao a ser ativada */
            }
            else
            {
                printf("Lugar %d para a tansicao %d nao ativada\n", i, tran);
                return 0;
            }
        }
    }
    for(i=0; i<nlug; i++)
        if(savelugar[i]==i)
            tok[i]-=a_con[i][tran]; /* Consome os tokens dos lugares que apontam para a transicao ativada*/

    produz_token(a_pro, tran, nlug, tok); /* Produz os tokens para os lugares que a transicao aponta */ 


    return 1;
}

void produz_token(int a_pro[MAX][MAX], int tran, int nlug, int *tok)
{
    int i;

    for(i=0; i<nlug; i++)
    {
        if(a_pro[tran][i]!=0)
        {
            printf("Produziu %d token da tran:%d para o lugar:%d\n", a_pro[tran][i], tran, i);
            tok[i]+=a_pro[tran][i];
            printf("Tokens no lugar %d: %d\n", i, tok[i]);
        }
    }
}






    

