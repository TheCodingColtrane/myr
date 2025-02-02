#include "./file_parser.h"
void holidaysheapsort(holidays dados[], int n, bool (*compare)(const holidays&, const holidays&));
void investimentheapsort(investiments dados[], int n, bool (*compare)(const investiments&, const investiments&));
bool compareholidaysdate(const holidays& a, const holidays& b);
bool compareinvestmentdate(const investiments& a, const investiments& b);


