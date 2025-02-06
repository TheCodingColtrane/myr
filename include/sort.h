#include "./file_parser.h"
#include "./investiments.h"
void holidaysheapsort(Investiment::holidays dados[], int n, bool (*compare)(const Investiment::holidays&, const Investiment::holidays&));
void investimentheapsort(Investiment::investiments dados[], int n, bool (*compare)(const Investiment::investiments&, const Investiment::investiments&));
bool compareholidaysdate(const Investiment::holidays& a, const Investiment::holidays& b);
bool compareinvestmentdate(const Investiment::investiments& a, const Investiment::investiments& b);


