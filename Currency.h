#ifndef CURRENCY_H
#define CURRENCY_H
#include <QString>

enum Currency{
    HUF = 0,
    EUR,
    USD
};


QString currencyToQString(Currency currency){
    switch(currency){
        case Currency::HUF: return "HUF";
        case Currency::EUR: return "EUR";
        case Currency::USD: return "USD";
        default: return "Unknown currency";
    }
}

QString currencyFromQString(const QString &currency){
    if(currency == "HUF") return Currency::HUF;
    if(currency == "EUR") return Currency::EUR;
    if(currency == "USD") return Currency::USD;
    throw std::invalid_argument("Unknown currency");
}

#endif // CURRENCY_H
