#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void incluirPessoa(char **primeiro, char **ultimo);
void listarPessoas(char **inicio);
void excluirPessoa(char **fim);
void buscarPessoa(char **inicio);
void limparMemoria(char **inicio, void *pBuffer);

// pBuffer = ['int = 1 ou 0 define se programa para ou continua', 'int = quantidade de pessoas adicionadas ' ]
char *primeiro = NULL;
char *ultimo = NULL;

int main()
{

    void *pBuffer;
    int *opcao;

    pBuffer = (int *)malloc(sizeof(int) * 2);
    opcao = pBuffer;
    *opcao = 1;

    while ((*((int *)pBuffer)) != 0)
    {
        printf(" ------ Menu --------\n1 - Incluir pessoa\n2 - Excluir pessoa\n3 - Listar pessoas\n4 - Buscar pessoa\n0 - Sair\nDigite sua opcao: ");
        scanf("%d", opcao);

        switch (*((int *)pBuffer))
        {
        case 1:
            incluirPessoa(&primeiro, &ultimo);
            break;
        case 2:

            excluirPessoa(&ultimo);
            break;
        case 3:
            listarPessoas(&primeiro);
            break;
        case 4:
            buscarPessoa(&primeiro);
            break;
        case 0:
            break;
        default:
            break;
        }
    }

    limparMemoria(&primeiro, pBuffer);
    return 0;
}

void incluirPessoa(char **inicio, char **fim)
{
    void *nodo = (void *)malloc(sizeof(int) * 4 + sizeof(char) * 11);
    char *nome = (char *)malloc(sizeof(char) * 11);
    int *idade, *telefone;
    char *anterior, *proximo;

    nome = nodo;
    idade = (nodo + sizeof(char) * 11);
    telefone = (nodo + sizeof(char) * 11 + sizeof(int));
    anterior = (nodo + sizeof(char) * 11 + sizeof(int) * 2);
    proximo = (nodo + sizeof(char) * 11 + sizeof(int) * 3);

    printf("Digite o nome: ");
    scanf("%s", nome);
    printf("Digite a idade: ");
    scanf("%d", idade);
    printf("Digite o telefone: ");
    scanf("%d", telefone);

    char **comparar = inicio;

    while ((*comparar) &&
           (strcmp((*comparar), nome) < 1))
    {
        comparar = (char **)(*comparar + sizeof(char) * 11 + sizeof(int) * 3);
    }

    *((char **)(nodo + sizeof(char) * 11 + sizeof(int) * 3)) = *(comparar);
    *(comparar) = nodo;
}

void excluirPessoa(char **fim)
{
    char *excluir, *proximo;
    char **atual = fim;

    excluir = *atual;

    proximo = *(char **)(excluir + sizeof(char) * 11 + sizeof(int) * 3);
    free(excluir);
    excluir = proximo;
    printf("\nRemovido do fim da lista.\n");
}

void listarPessoas(char **inicio)
{
    char **atual = inicio;

    while (*atual)
    {
        printf("\n\nNome: %s\nIdade: %d\nTelefone: %d\n", *((char **)atual), *((int **)(*atual + sizeof(char) * 11)), *((int **)(*atual + sizeof(char) * 11 + sizeof(int))));
        atual = (char **)(*atual + sizeof(char) * 11 + sizeof(int) * 3);
    }
}

void buscarPessoa(char **inicio)
{
    int *comparar = 0;
    char **atual = inicio;
    char *nome = (char *)malloc(sizeof(char) * 11);

    printf("Digite o nome da pessoa que deseja buscar: ");
    scanf("%s", nome);
    while (*(atual) && (strcmp(nome, *(atual)) != 0))
    {
        atual = (char **)(*atual + sizeof(char) * 11 + sizeof(int) * 3);
    }

    if (*(atual))
    {
        if (strcmp(nome, *(atual)) == 0)
        {
            printf("\nEncontrou a pessoa. Dados:\nNome: %s\nIdade:%d\nTelefone:%d\n\n", *((char **)atual), *((int **)(*atual + sizeof(char) * 11)), *((int **)(*atual + sizeof(char) * 11 + sizeof(int))));
        }
    }
    else
    {
        printf("\nPessoa não encontrada na lista.\n");
    }
    free(nome);
}

void limparMemoria(char **inicio, void *pBuffer)
{

    char *excluir, *proximo;
    char **atual = inicio;
    excluir = *atual;

    while (excluir != NULL)
    {
        proximo = *(char **)(excluir + sizeof(char) * 11 + sizeof(int) * 3);
        free(excluir);
        excluir = proximo;
    }
    free(pBuffer);
}