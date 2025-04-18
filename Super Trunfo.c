#include <stdio.h>

int main() {
    // Variáveis para a carta 1
    char estado1;
    char codigo1[4];
    char nomeCidade1[50];
    unsigned long int populacao1;
    float area1;
    float pib1;
    int pontosTuristicos1;
    float densidade1;
    float pibPerCapita1;
    float superPoder1;

    // Variáveis para a carta 2
    char estado2;
    char codigo2[4];
    char nomeCidade2[50];
    unsigned long int populacao2;
    float area2;
    float pib2;
    int pontosTuristicos2;
    float densidade2;
    float pibPerCapita2;
    float superPoder2;

    // Entrada de dados para a carta 1
    printf("Digite os dados da Carta 1:\n");
    printf("Estado (A-H): ");
    scanf(" %c", &estado1);
    printf("Codigo da Carta (ex: A01): ");
    scanf(" %3s", codigo1);
    printf("Nome da Cidade: ");
    scanf(" %49[^\n]", nomeCidade1);
    printf("Populacao: ");
    scanf(" %lu", &populacao1);
    printf("Area (km²): ");
    scanf(" %f", &area1);
    printf("PIB (bilhoes de reais): ");
    scanf(" %f", &pib1);
    printf("Numero de Pontos Turisticos: ");
    scanf(" %d", &pontosTuristicos1);

    // Entrada de dados para a carta 2
    printf("\nDigite os dados da Carta 2:\n");
    printf("Estado (A-H): ");
    scanf(" %c", &estado2);
    printf("Codigo da Carta (ex: B02): ");
    scanf(" %3s", codigo2);
    printf("Nome da Cidade: ");
    scanf(" %49[^\n]", nomeCidade2);
    printf("Populacao: ");
    scanf(" %lu", &populacao2);
    printf("Area (km²): ");
    scanf(" %f", &area2);
    printf("PIB (bilhoes de reais): ");
    scanf(" %f", &pib2);
    printf("Numero de Pontos Turisticos: ");
    scanf(" %d", &pontosTuristicos2);

    // Cálculos densidade e PIB per capita
    densidade1 = (float)populacao1 / area1;
    pibPerCapita1 = (pib1 * 1000000000.0f) / populacao1;

    densidade2 = (float)populacao2 / area2;
    pibPerCapita2 = (pib2 * 1000000000.0f) / populacao2;

    // Cálculo do Super Poder
    // Convertendo populacao para float para somar com os demais floats
    superPoder1 = (float)populacao1 + area1 + (pib1 * 1000000000.0f) + pontosTuristicos1 + pibPerCapita1 + (1.0f / densidade1);
    superPoder2 = (float)populacao2 + area2 + (pib2 * 1000000000.0f) + pontosTuristicos2 + pibPerCapita2 + (1.0f / densidade2);

    // Comparações:
    // Para população, área, PIB, pontos turísticos, PIB per capita e Super Poder: maior vence (1 se Carta 1 vence, 0 se Carta 2 vence)
    // Para densidade populacional: menor vence (1 se Carta 1 vence, 0 se Carta 2 vence)

    int vPopulacao = (populacao1 > populacao2) ? 1 : 0;
    int vArea = (area1 > area2) ? 1 : 0;
    int vPIB = (pib1 > pib2) ? 1 : 0;
    int vPontosTuristicos = (pontosTuristicos1 > pontosTuristicos2) ? 1 : 0;
    int vDensidade = (densidade1 < densidade2) ? 1 : 0;
    int vPIBperCapita = (pibPerCapita1 > pibPerCapita2) ? 1 : 0;
    int vSuperPoder = (superPoder1 > superPoder2) ? 1 : 0;

    // Exibição dos resultados das comparações
    printf("\nComparacao de Cartas:\n");
    printf("Populacao: Carta 1 venceu (%d)\n", vPopulacao);
    printf("Area: Carta 1 venceu (%d)\n", vArea);
    printf("PIB: Carta 1 venceu (%d)\n", vPIB);
    printf("Pontos Turisticos: Carta 1 venceu (%d)\n", vPontosTuristicos);
    printf("Densidade Populacional: Carta 2 venceu (%d)\n", 1 - vDensidade);
    printf("PIB per Capita: Carta 1 venceu (%d)\n", vPIBperCapita);
    printf("Super Poder: Carta 1 venceu (%d)\n", vSuperPoder);

    return 0;
}
