#ifndef SIMPLECSVPARSER_H
#define SIMPLECSVPARSER_H
#include <QString>
#include "currency.h"
#include "security.h"
#include <vector>

class SimpleCSVParser
{
public:
    void readFile(const QString &path, std::vector<CurrencyPair> &currencyPairs, std::vector<Security> &securities);
    void writeFile(const QString &path, const std::vector<CurrencyPair> &currencyPairs, const std::vector<Security> &securities);
};

#endif // SIMPLECSVPARSER_H
