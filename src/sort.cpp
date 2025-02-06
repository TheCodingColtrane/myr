#include <array>
#include "../include/file_parser.h"

void holidaysheap(Investiment::holidays dados[], int n, int i, bool (*compare)(const Investiment::holidays&, const Investiment::holidays&)) {
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

void holidaysheapsort(Investiment::holidays dados[], int n, bool (*compare)(const Investiment::holidays&, const Investiment::holidays&)) {
    for (int i = n / 2 - 1; i >= 0; --i) {
        holidaysheap(dados, n, i, compare);
    }

    for (int i = n - 1; i > 0; --i) {
        std::swap(dados[0], dados[i]);
        holidaysheap(dados, i, 0, compare);
    }
}

void investimentsheap(Investiment::investiments dados[], int n, int i, bool (*compare)(const Investiment::investiments&, const Investiment::investiments&)) {
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

void investimentheapsort(Investiment::investiments dados[], int n, bool (*compare)(const Investiment::investiments&, const Investiment::investiments&)) {
    for (int i = n / 2 - 1; i >= 0; --i) {
        investimentsheap(dados, n, i, compare);
    }

    for (int i = n - 1; i > 0; --i) {
        std::swap(dados[0], dados[i]);
        investimentsheap(dados, i, 0, compare);
    }
}

bool compareholidaysdate(const Investiment::holidays& a, const Investiment::holidays& b) {
    return a.date < b.date;
}

bool compareinvestmentdate(const Investiment::investiments& a, const Investiment::investiments& b) {
    return a.starting_date < b.starting_date;
}