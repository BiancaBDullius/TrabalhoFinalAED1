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

// tamanho da pessoa + pnext: sizeof(char)*10 + sizeof(int)*4

void incluirPessoa(char **primeiro, char **ultimo);
void listarPessoas(char **inicio);
void excluirPessoa(char **inicio);
void buscarPessoa(char **inicio);
void resetLista();
void realocarMemoria();

// pBuffer = ['int = 1 ou 0 define se programa para ou continua', 'int = quantidade de pessoas adicionadas ' ]
void *lista;
int qtdLista2 = 0;
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
        // enquanto opcao for != 0 programa vai continuar
        printf(" ------ Menu --------\n1 - Incluir pessoa\n2 - Excluir pessoa\n3 - Listar pessoas\n4 - Buscar pessoa\n0 - Sair\nDigite sua opcao: ");
        scanf("%d", opcao);

        switch (*((int *)pBuffer))
        {
        case 1:
            incluirPessoa(&primeiro, &ultimo);
            break;
        case 2:

            excluirPessoa(&primeiro);
            break;
        case 3:
            // printf("Lista fora da função: %p\n", lista);
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

        // parar programa *opcao = 0;
    }

    // printf("Valor pBuffer = %d\n", *((int *)pBuffer));

    free(pBuffer);
    char **atual = &primeiro;

    while (*((char **)atual))
    {
        char *antigo = *atual;
        *atual = *((char **)(atual + sizeof(char) * 11 + sizeof(int) * 3));
        atual = &(*(atual + sizeof(char) * 11 + sizeof(int) * 3));
        free(antigo);
    }
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
    // printf("\n\nNome: %s\nIdade: %d\nTelefone: %d", nodo, *((int *)(nodo + sizeof(char) * 11)), *((int *)(nodo + sizeof(char) * 11 + sizeof(int))));

    // printf("\nPrimeiro Nodo: %d\n", *((int *)lista));

    char **comparar = inicio; // coloca "comparar" no inicio da lista

    while ((*comparar) &&
           (strcmp(*((char **)comparar), nome) < 1))
    {
        // anda pela lista até achar o lugar certo
        comparar = &(*(comparar + sizeof(char) * 11 + sizeof(int) * 3));
    }

    // adiciona o next do nodo atual como o next da nova pessoa adicionada
    proximo = *(comparar + sizeof(char) * 11 + sizeof(int) * 3);
    // adiciona a nova pessoa como o next no nodo atual da lista
    *comparar = nodo;
    // free(nome);
}

void resetLista()
{
    int *pProximo, *pUltimo, *qtdLista;
    pProximo = lista;
    pUltimo = (lista + sizeof(int));
    qtdLista = (lista + sizeof(int) * 2);

    *pProximo = 0;
    *pUltimo = 0;
    *qtdLista = 0;
    printf("\nLista resetada, proximo: %d\nAnterior: %d\nqtdLista: %d\n", *((int *)lista), *((int *)(lista + sizeof(int))), *((int *)(lista + sizeof(int) * 2)));
}

void excluirPessoa(char **inicio)
{
    int *comparar = 0;
    char *antigo;
    char **atual = inicio;
    char *nome;

    printf("Digite o nome da pessoa que deseja deletar: ");
    scanf("%s", nome);
    comparar = (int *)(strcmp(nome, *((char **)atual)) == 0);
    while (*((char **)atual) && comparar == (int *)0)
    {
        atual = &(*(atual + sizeof(char) * 11 + sizeof(int) * 3));
        comparar = (int *)(strcmp(nome, *((char **)atual)) == 0);
    }

    if (comparar == (int *)1)
    {
        antigo = *atual;
        *atual = *((char **)(atual + sizeof(char) * 11 + sizeof(int) * 3));
        // free(*((char *)antigo));
        // free(antigo);
    }
}

void listarPessoas(char **inicio)
{
    char **atual = inicio;

    while (*atual)
    {
        printf("\n\nNome: %s\nIdade: %d\nTelefone: %d\n", *((char **)atual), *((int **)(*atual + sizeof(char) * 11)), *((int **)(*atual + sizeof(char) * 11 + sizeof(int))));
        atual = &(*(atual + sizeof(char) * 11 + sizeof(int) * 3));
    }
}

void buscarPessoa(char **inicio)
{
    int *comparar = 0;
    char **atual = inicio;
    char *nome = (char *)malloc(sizeof(char) * 11);

    printf("Digite o nome da pessoa que deseja buscar: ");
    scanf("%s", nome);
    while (*((char **)atual) && (strcmp(nome, *((char **)atual)) != 0))
    {
        printf("comparar 2: %d\n", (strcmp(nome, *((char **)atual)) == 0));
        atual = &(*(atual + sizeof(char) * 11 + sizeof(int) * 3));
    }

    if (strcmp(nome, *((char **)atual)) == 0)
    {
        printf("\nEncontrou a pessoa. Dados:\nNome: %s\nIdade:%d\nTelefone:%d\n\n", *((char **)(atual)), *((char **)(atual + sizeof(char) * 11)), *((char **)(atual + sizeof(char) * 11 + sizeof(int))));
    }
    else
    {
        printf("\nPessoa não encontrada na lista.\n");
    }
    free(nome);
}
