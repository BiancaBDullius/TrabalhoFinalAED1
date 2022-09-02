/* Instruções do trabalho:
Continuar a sua implementação da agenda (exercício 3) semana 1 dentro dos mesmo parâmetros, mas incluir o seguinte.
- Nenhuma variável pode ser declarada em todo o programa, somente ponteiros. Todos os dados do programa devem ser guardados dentro do pBuffer.
Nem mesmo como parâmetro de função. Só ponteiros que apontam para dentro do pBuffer.
Exemplo do que não pode: int c; char a; int v[10];  void Funcao(int parametro)
- Não pode usar struct em todo o programa.
- Usar fila ordenada (heap) para armazenar as pessoas em ordem alfabética sempre que o usuário incluir uma nova pessoa.
- Implementar a base de dados da agenda usando lista duplamente ligada
Somente essa base de dados pode ficar fora do buffer principal, ou seja, pode usar um malloc para cada nodo. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void incluirPessoa();
void listarPessoas();
void excluirPessoa();
void buscarPessoa();
void realocarMemoria();

// pBuffer = ['int = 1 ou 0 define se programa para ou continua', 'int = quantidade de pessoas adicionadas ' ]
void *pBuffer;
int *opcao;

int main()
{

    pBuffer = (int *)malloc(sizeof(int) * 2);

    opcao = pBuffer;
    *opcao = 1;

    while ((*((int *)pBuffer)) != 0)
    {
        // enquanto opcao for != 0 programa vai continuar
        printf("\n\nValor pBuffer = %d\n\n", *((int *)pBuffer));
        printf(" ------ Menu --------\n1 - Incluir pessoa\n2 - Excluir pessoa\n3 - Listar pessoas\n4 - Buscar pessoa\n0 - Sair\nDigite sua opcao: ");
        scanf("%d", opcao);

        switch (*((int *)pBuffer))
        {
        case 1:
            incluirPessoa();
            break;
        case 2:
            excluirPessoa();
            break;
        case 3:
            listarPessoas();
            break;
        case 4:
            buscarPessoa();
            break;
        case 0:
            break;
        default:
            break;
        }

        // parar programa *opcao = 0;
    }

    // printf("Valor pBuffer = %d\n", *((int *)pBuffer));

    free(pBuffer);
    return 0;
}

void incluirPessoa()
{
    int *qtdPessoas;
    pBuffer = realloc(pBuffer, (sizeof(int) * 2));

    qtdPessoas = (pBuffer + sizeof(int));
    // teste
    // to do setar pBuffer qtdPessoas pra 0 no começo do programa
    *qtdPessoas = 12;
    printf("\nFuncao de incluir, quatidade de pessoas: %d", *((int *)(pBuffer + sizeof(int))));
}
void excluirPessoa()
{
    printf("\nFuncao de exluir");
}
void listarPessoas()
{
    printf("\nFuncao de listar");
}
void buscarPessoa()
{
    printf("\nFuncao de buscar");
}