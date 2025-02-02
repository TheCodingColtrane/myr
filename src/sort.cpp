#include <array>
#include "../include/file_parser.h"

void holidaysheap(holidays dados[], int n, int i, bool (*compare)(const holidays&, const holidays&)) {
    int maior = i;
    int esq = 2 * i + 1;
    int dir = 2 * i + 2;

    if (esq < n && compare(dados[maior], dados[esq])) maior = esq;
    if (dir < n && compare(dados[maior], dados[dir])) maior = dir;

    if (maior != i) {
        std::swap(dados[i], dados[maior]);
        holidaysheap(dados, n, maior, compare);
    }
}

void holidaysheapsort(holidays dados[], int n, bool (*compare)(const holidays&, const holidays&)) {
    for (int i = n / 2 - 1; i >= 0; --i) {
        holidaysheap(dados, n, i, compare);
    }

    for (int i = n - 1; i > 0; --i) {
        std::swap(dados[0], dados[i]);
        holidaysheap(dados, i, 0, compare);
    }
}

void investimentsheap(investiments dados[], int n, int i, bool (*compare)(const investiments&, const investiments&)) {
    int maior = i;
    int esq = 2 * i + 1;
    int dir = 2 * i + 2;

    if (esq < n && compare(dados[maior], dados[esq])) maior = esq;
    if (dir < n && compare(dados[maior], dados[dir])) maior = dir;

    if (maior != i) {
        std::swap(dados[i], dados[maior]);
        investimentsheap(dados, n, maior, compare);
    }
}

void investimentheapsort(investiments dados[], int n, bool (*compare)(const investiments&, const investiments&)) {
    for (int i = n / 2 - 1; i >= 0; --i) {
        investimentsheap(dados, n, i, compare);
    }

    for (int i = n - 1; i > 0; --i) {
        std::swap(dados[0], dados[i]);
        investimentsheap(dados, i, 0, compare);
    }
}

bool compareholidaysdate(const holidays& a, const holidays& b) {
    return a.date < b.date;
}

bool compareinvestmentdate(const investiments& a, const investiments& b) {
    return a.data_inicio < b.data_inicio;
}