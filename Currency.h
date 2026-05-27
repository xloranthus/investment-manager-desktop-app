#ifndef CURRENCY_H
#define CURRENCY_H

#include <QString>
#include <vector>

enum Currency{
    HUF = 0,
    EUR,
    USD,
    CURRENCIES_COUNT
};

QString currencyToQString(Currency currency);

Currency currencyFromQString(const QString &currency);

struct CurrencyPair{
    CurrencyPair(QString name, double exchangeRate);
    QString m_name;
    double m_exchangeRate;
};

class CurrencyConverter{
public:
    CurrencyConverter(int numberOfCurrencies = Currency::CURRENCIES_COUNT);
    void calcExchangeRateMatrix(const std::vector<CurrencyPair> &currencyPairs);
    double convert(double value, Currency fromCurrency, Currency toCurrency) const;
private:
    std::vector<std::vector<double>> m_exchangeRateMatrix;
};

#endif // CURRENCY_H
