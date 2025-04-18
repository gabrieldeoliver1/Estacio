#include <stdio.h>
#include <string.h>

// Estrutura para armazenar os dados da carta
typedef struct {
    char nomePais[50];
    char estado[3];
    char codigo[5];
    char nomeCidade[50];
    int populacao;
    float area;
    float pib; // em bilhões de reais
    int pontosTuristicos;
    float densidade;      // populacao / area
} Carta;

// Função para calcular densidade demográfica
void calculaDensidade(Carta *carta) {
    carta->densidade = (float)carta->populacao / carta->area;
}

// Função para exibir os dados básicos da carta
void exibirCarta(Carta carta) {
    printf("%s - %s (%s)\n", carta.nomeCidade, carta.estado, carta.nomePais);
}

// Função para exibir o menu e retornar a opção escolhida
int menu(int atributoExcluido) {
    int opcao;
    printf("\nEscolha o atributo para comparar:\n");
    if (atributoExcluido != 1) printf("1 - Populacao\n");
    if (atributoExcluido != 2) printf("2 - Area\n");
    if (atributoExcluido != 3) printf("3 - PIB\n");
    if (atributoExcluido != 4) printf("4 - Numero de Pontos Turisticos\n");
    if (atributoExcluido != 5) printf("5 - Densidade Demografica\n");
    printf("0 - Sair\n");
    printf("Opcao: ");
    scanf("%d", &opcao);
    return opcao;
}

// Função que retorna o valor do atributo escolhido para uma carta
float obterValorAtributo(Carta carta, int atributo) {
    switch (atributo) {
        case 1: return (float)carta.populacao;
        case 2: return carta.area;
        case 3: return carta.pib;
        case 4: return (float)carta.pontosTuristicos;
        case 5: return carta.densidade;
        default: return 0.0f;
    }
}

// Função que retorna o nome do atributo para exibição
const char* nomeAtributo(int atributo) {
    switch (atributo) {
        case 1: return "Populacao";
        case 2: return "Area";
        case 3: return "PIB (bilhoes de reais)";
        case 4: return "Numero de Pontos Turisticos";
        case 5: return "Densidade Demografica (hab/km²)";
        default: return "Atributo desconhecido";
    }
}

// Função para imprimir valor formatado conforme atributo
void imprimirValor(int atributo, float valor) {
    switch (atributo) {
        case 1: // População
        case 4: // Pontos turísticos
            printf("%d", (int)valor);
            break;
        case 3: // PIB
            printf("%.2f bilhoes de reais", valor);
            break;
        case 2: // Área
        case 5: // Densidade
            printf("%.2f", valor);
            break;
        default:
            printf("%.2f", valor);
    }
}

// Função para comparar dois valores segundo regra do atributo
// Retorna 1 se valor1 vence, 2 se valor2 vence, 0 se empate
int compararAtributos(int atributo, float valor1, float valor2) {
    if (valor1 == valor2) return 0; // empate
    if (atributo == 5) { // Densidade Demográfica: menor vence
        return (valor1 < valor2) ? 1 : 2;
    } else { // Demais atributos: maior vence
        return (valor1 > valor2) ? 1 : 2;
    }
}

int main() {
    // Cartas pré-definidas
    Carta carta1 = {
        "Brasil",
        "SP",
        "A01",
        "Sao Paulo",
        12325000,
        1521.11f,
        699.28f,
        50,
        0.0f
    };
    Carta carta2 = {
        "Brasil",
        "RJ",
        "B02",
        "Rio de Janeiro",
        6748000,
        1200.25f,
        300.50f,
        30,
        0.0f
    };

    // Calcula densidade para as cartas
    calculaDensidade(&carta1);
    calculaDensidade(&carta2);

    int atributo1 = -1, atributo2 = -1;

    // Escolha do primeiro atributo
    do {
        atributo1 = menu(0);
        if (atributo1 == 0) {
            printf("Saindo do programa.\n");
            return 0;
        }
        if (atributo1 < 1 || atributo1 > 5) {
            printf("Opcao invalida! Tente novamente.\n");
        }
    } while (atributo1 < 1 || atributo1 > 5);

    // Escolha do segundo atributo (não pode ser igual ao primeiro)
    do {
        atributo2 = menu(atributo1);
        if (atributo2 == 0) {
            printf("Saindo do programa.\n");
            return 0;
        }
        if (atributo2 < 1 || atributo2 > 5) {
            printf("Opcao invalida! Tente novamente.\n");
            continue;
        }
        if (atributo2 == atributo1) {
            printf("Voce ja escolheu esse atributo. Escolha outro.\n");
        }
    } while (atributo2 < 1 || atributo2 > 5 || atributo2 == atributo1);

    // Obter valores dos atributos para as duas cartas
    float valor1_attr1 = obterValorAtributo(carta1, atributo1);
    float valor2_attr1 = obterValorAtributo(carta2, atributo1);
    float valor1_attr2 = obterValorAtributo(carta1, atributo2);
    float valor2_attr2 = obterValorAtributo(carta2, atributo2);

    // Comparar individualmente
    int vencedor_attr1 = compararAtributos(atributo1, valor1_attr1, valor2_attr1);
    int vencedor_attr2 = compararAtributos(atributo2, valor1_attr2, valor2_attr2);

    // Soma dos valores para cada carta (usando valores originais, não invertendo densidade)
    float soma_carta1 = valor1_attr1 + valor1_attr2;
    float soma_carta2 = valor2_attr1 + valor2_attr2;

    // Determinar vencedor da soma
    int vencedor_soma;
    if (soma_carta1 > soma_carta2) {
        vencedor_soma = 1;
    } else if (soma_carta2 > soma_carta1) {
        vencedor_soma = 2;
    } else {
        vencedor_soma = 0; // empate
    }

    // Exibir resultados
    printf("\n--- Comparacao entre cartas ---\n");
    printf("Carta 1: %s - %s (%s)\n", carta1.nomeCidade, carta1.estado, carta1.nomePais);
    printf("Carta 2: %s - %s (%s)\n\n", carta2.nomeCidade, carta2.estado, carta2.nomePais);

    // Exibe atributos e valores
    printf("Atributo 1: %s\n", nomeAtributo(atributo1));
    printf("  Carta 1: ");
    imprimirValor(atributo1, valor1_attr1);
    printf("\n  Carta 2: ");
    imprimirValor(atributo1, valor2_attr1);
    printf("\n");

    printf("Atributo 2: %s\n", nomeAtributo(atributo2));
    printf("  Carta 1: ");
    imprimirValor(atributo2, valor1_attr2);
    printf("\n  Carta 2: ");
    imprimirValor(atributo2, valor2_attr2);
    printf("\n");

    // Exibe vencedores individuais
    char *msg_vencedor_attr1 = (vencedor_attr1 == 0) ? "Empate" :
                               (vencedor_attr1 == 1) ? "Carta 1 venceu" : "Carta 2 venceu";
    char *msg_vencedor_attr2 = (vencedor_attr2 == 0) ? "Empate" :
                               (vencedor_attr2 == 1) ? "Carta 1 venceu" : "Carta 2 venceu";

    printf("\nResultado da comparacao individual:\n");
    printf("  %s: %s\n", nomeAtributo(atributo1), msg_vencedor_attr1);
    printf("  %s: %s\n", nomeAtributo(atributo2), msg_vencedor_attr2);

    // Exibe soma dos atributos
    printf("\nSoma dos atributos:\n");
    printf("  Carta 1: %.2f\n", soma_carta1);
    printf("  Carta 2: %.2f\n", soma_carta2);

    // Exibe vencedor final
    if (vencedor_soma == 0) {
        printf("\nResultado final: Empate!\n");
    } else {
        printf("\nResultado final: %s (%s) venceu!\n",
               (vencedor_soma == 1) ? "Carta 1" : "Carta 2",
               (vencedor_soma == 1) ? carta1.nomeCidade : carta2.nomeCidade);
    }

    return 0;
}
