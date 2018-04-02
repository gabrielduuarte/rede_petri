
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define MAX 256
#define GAME 1
#define VOLTA -1

int * token(int nlug);
void arc_consumidores(int nacon, int a_con[MAX][MAX]);
void arc_produtor(int napro, int a_pro[MAX][MAX]);
void simulador(int nlug, int *tok, int ntran, int nacon, int a_con[MAX][MAX], int napro, int a_pro[MAX][MAX]);
void sorteia_trans(int tran[], int ntran);
void ativa_tran(int tran[], int ntran, int nlug, int *tok, int a_con[MAX][MAX], int a_pro[MAX][MAX]);

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

    simulador(nlug, tok, ntran, nacon, a_con, napro, a_pro);

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

void simulador(int nlug, int *tok, int ntran, int nacon, int a_con[MAX][MAX], int napro, int a_pro[MAX][MAX])
{
    int i, lugar, count=0, j;
    int tran[ntran];

    /*for(i=0; i<ntran; i++)
        for(j=0; j<nlug; j++)
            printf("Arco consumidor: a_con[%d][%d]:%d\n",i,j,a_con[i][j]);*/
  
    printf("Transicoes sorteadas\n");
    sorteia_trans(tran, ntran);
    for(i=0; i<ntran; i++)
        printf("%d ", tran[i]);
    printf("\n");
    
    ativa_tran(tran, ntran, nlug, tok, a_con, a_pro);

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

void ativa_tran(int tran[], int ntran, int nlug, int *tok, int a_con[MAX][MAX], int a_pro[MAX][MAX])
{
    int i, lugar, novolugar, j;
    
    for(i=0; i<ntran; i++)
    {
        for(lugar=0; lugar<nlug; lugar++)
        {
            if(a_con[lugar][tran[i]]!=0)
            {
                if(a_con[lugar][tran[i]]<=tok[lugar])
                {
                    printf("O arco consumidor do lugar:%d para a transicao %d ativou a transicao\n", lugar, tran[i]);
                    tok[lugar]--;
                    printf("Tokens no lugar %d: %d\n", lugar, tok[lugar]);
                    for(novolugar=0; novolugar<nlug; novolugar++)
                    {
                        if(a_pro[tran[i]][novolugar]!=0)
                        {
                            printf("Produziu %d token da tran:%d para o lugar:%d\n", a_pro[tran[i]][novolugar], tran[i], novolugar);
                            tok[novolugar]+=a_pro[tran[i]][novolugar];
                            printf("Tokens no lugar %d: %d\n", novolugar, tok[novolugar]);
                        }
                    }
                }
                else
                    printf("O arco consumidor do lugar %d para a transicao %d nao ativou\n", lugar, tran[i]);
            }
        }
    }
}


