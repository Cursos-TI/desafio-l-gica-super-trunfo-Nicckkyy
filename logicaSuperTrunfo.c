#include <stdio.h>
#include <string.h>

// Estrutura que representa a carta do Super Trunfo
// Aqui guardamos todas as informações que uma carta pode ter
typedef struct {
    char estado[30];
    char codigo[10];
    char cidade[50];
    int populacao;
    float area;
    float pib;
    int pontosTuristicos;
    float densidadePopulacional;
    float pibPerCapita;
} Carta;

// Função que calcula informações extras a partir dos dados principais
// Exemplo: densidade populacional e PIB per capita
void calcularAtributos(Carta *c) {
    c->densidadePopulacional = c->populacao / c->area;
    c->pibPerCapita = c->pib / c->populacao;
}

// Função apenas para imprimir os dados da carta de forma organizada
void exibirCarta(Carta c) {
    printf("\n--- Carta ---\n");
    printf("Estado: %s\n", c.estado);
    printf("Codigo: %s\n", c.codigo);
    printf("Cidade: %s\n", c.cidade);
    printf("Populacao: %d\n", c.populacao);
    printf("Area: %.2f\n", c.area);
    printf("PIB: %.2f\n", c.pib);
    printf("Pontos Turisticos: %d\n", c.pontosTuristicos);
    printf("Densidade Populacional: %.2f\n", c.densidadePopulacional);
    printf("PIB per capita: %.2f\n", c.pibPerCapita);
}

// Essa função serve para pegar o valor de um atributo específico da carta
// Exemplo: se escolhermos "1", ele devolve a população da carta
float obterAtributo(Carta c, int opcao) {
    switch(opcao) {
        case 1: return c.populacao;
        case 2: return c.area;
        case 3: return c.pib;
        case 4: return c.pontosTuristicos;
        case 5: return c.densidadePopulacional;
        case 6: return c.pibPerCapita;
        default: return 0;
    }
}

// Essa função compara os dois valores escolhidos de cada carta
// Regra: quem tiver o maior valor ganha
// Exceção: na densidade populacional, vence quem tiver o menor valor
int compararAtributo(float valor1, float valor2, int opcao) {
    if(opcao == 5) { // densidade é especial
        if(valor1 < valor2) return 1;
        else if(valor2 < valor1) return 2;
        else return 0; // empate
    } else {
        if(valor1 > valor2) return 1;
        else if(valor2 > valor1) return 2;
        else return 0; // empate
    }
}

// Só para imprimir o nome do atributo escolhido de forma bonitinha
void exibirNomeAtributo(int opcao) {
    switch(opcao) {
        case 1: printf("Populacao"); break;
        case 2: printf("Area"); break;
        case 3: printf("PIB"); break;
        case 4: printf("Pontos Turisticos"); break;
        case 5: printf("Densidade Populacional"); break;
        case 6: printf("PIB per capita"); break;
    }
}

int main() {
    // Aqui criamos duas cartas já prontas (não pedimos para o usuário cadastrar)
    Carta carta1 = {"SP", "A1", "Sao Paulo", 12300000, 1521.11, 699000000000.0, 30};
    Carta carta2 = {"RJ", "A2", "Rio de Janeiro", 6718903, 1200.00, 400000000000.0, 25};

    // Calcula os atributos derivados para cada carta
    calcularAtributos(&carta1);
    calcularAtributos(&carta2);

    // Mostra as cartas para o jogador
    printf("Carta 1:");
    exibirCarta(carta1);
    printf("\nCarta 2:");
    exibirCarta(carta2);

    // Agora começa a parte do jogo!
    int atributo1, atributo2;

    // Primeiro menu: o jogador escolhe qual será o primeiro atributo de comparação
    printf("\nEscolha o primeiro atributo para comparacao:\n");
    printf("1 - Populacao\n");
    printf("2 - Area\n");
    printf("3 - PIB\n");
    printf("4 - Pontos Turisticos\n");
    printf("5 - Densidade Populacional\n");
    printf("6 - PIB per capita\n");
    printf("Opcao: ");
    scanf("%d", &atributo1);

    // Segundo menu: aqui não deixamos repetir o mesmo atributo do primeiro
    do {
        printf("\nEscolha o segundo atributo (diferente do primeiro):\n");
        for(int i=1; i<=6; i++) {
            if(i != atributo1) { // só mostra opções válidas
                printf("%d - ", i);
                exibirNomeAtributo(i);
                printf("\n");
            }
        }
        printf("Opcao: ");
        scanf("%d", &atributo2);
    } while(atributo2 == atributo1); // repete caso escolha errado

    // Pega os valores escolhidos em cada carta
    float valor1_attr1 = obterAtributo(carta1, atributo1);
    float valor2_attr1 = obterAtributo(carta2, atributo1);
    float valor1_attr2 = obterAtributo(carta1, atributo2);
    float valor2_attr2 = obterAtributo(carta2, atributo2);

    // Faz a comparação de cada atributo separadamente
    int resultado1 = compararAtributo(valor1_attr1, valor2_attr1, atributo1);
    int resultado2 = compararAtributo(valor1_attr2, valor2_attr2, atributo2);

    // Agora somamos os dois valores de cada carta para decidir o resultado final
    float soma1 = valor1_attr1 + valor1_attr2;
    float soma2 = valor2_attr1 + valor2_attr2;

    // Mostra o que aconteceu na rodada
    printf("\n=== Resultado da Comparacao ===\n");

    // Mostra o primeiro atributo
    printf("Atributo 1: ");
    exibirNomeAtributo(atributo1);
    printf("\nCarta 1 (%s): %.2f\nCarta 2 (%s): %.2f\n",
           carta1.cidade, valor1_attr1, carta2.cidade, valor2_attr1);

    // Mostra o segundo atributo
    printf("\nAtributo 2: ");
    exibirNomeAtributo(atributo2);
    printf("\nCarta 1 (%s): %.2f\nCarta 2 (%s): %.2f\n",
           carta1.cidade, valor1_attr2, carta2.cidade, valor2_attr2);

    // Mostra as somas
    printf("\nSoma dos atributos:\n");
    printf("Carta 1 (%s): %.2f\n", carta1.cidade, soma1);
    printf("Carta 2 (%s): %.2f\n", carta2.cidade, soma2);

    // Finalmente, declara o vencedor (ou empate)
    if(soma1 > soma2) {
        printf("\nResultado Final: Carta 1 (%s) venceu!\n", carta1.cidade);
    } else if(soma2 > soma1) {
        printf("\nResultado Final: Carta 2 (%s) venceu!\n", carta2.cidade);
    } else {
        printf("\nResultado Final: Empate!\n");
    }

    return 0;
}
