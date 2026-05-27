#include <QString>
#include <QStringList>
#include "currency.h"
using std::vector;

// Currency
QString currencyToQString(Currency currency){
    switch(currency){
    case Currency::HUF: return "HUF";
    case Currency::EUR: return "EUR";
    case Currency::USD: return "USD";
    default: return "Unknown currency";
    }
}

Currency currencyFromQString(const QString &currency){
    if(currency == "HUF") return Currency::HUF;
    if(currency == "EUR") return Currency::EUR;
    if(currency == "USD") return Currency::USD;
    throw std::invalid_argument("Unknown currency");
}

// CurrencyPair
CurrencyPair::CurrencyPair(QString name, double exchangeRate)
    : m_name(name)
    , m_exchangeRate(exchangeRate)
{}

// CurrencyConverter
CurrencyConverter::CurrencyConverter(int numberOfCurrencies)
    : m_exchangeRateMatrix(numberOfCurrencies, vector<double>(numberOfCurrencies, 1.0))
{}

// diagonalisban maradnak az inicializalt 1.0 ertekek
void CurrencyConverter::calcExchangeRateMatrix(const vector<CurrencyPair> &currencyPairs){
    for(const CurrencyPair& currencyPair : currencyPairs){
        QStringList currencyNames = currencyPair.m_name.split('/');
        m_exchangeRateMatrix[currencyFromQString(currencyNames[0])][currencyFromQString(currencyNames[1])] = currencyPair.m_exchangeRate;
        m_exchangeRateMatrix[currencyFromQString(currencyNames[1])][currencyFromQString(currencyNames[0])] = 1 / currencyPair.m_exchangeRate;
    }
}

double CurrencyConverter::convert(double value, Currency fromCurrency, Currency toCurrency) const{
    return value * m_exchangeRateMatrix[fromCurrency][toCurrency];
}

