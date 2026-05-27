#include "security.h"

// a piaci ar kezdeti erteke a beszerzesi ar lesz
Security::Security(QString ISIN, QString name, int qty, double purchasePrice, Currency baseCurrency)
    : m_ISIN(ISIN)
    , m_name(name)
    , m_qty(qty)
    , m_avgPurchase(purchasePrice)
    , m_baseCurrency(baseCurrency)
    , m_marketPrice(purchasePrice)
{}

QString Security::getISIN(){
    return m_ISIN;
}

QString Security::getName(){
    return m_name;
}

int Security::getQty(){
    return m_qty;
}

double Security::getAvgPurchasePrice(){
    return m_avgPurchasePrice;
}

Currency Security::getBaseCurrency(){
    return m_baseCurrency;
}

double Security::getMarketPrice(){
    return m_marketPrice;
}

// innentol szamitott ertekek kovetkeznek
double Security::getMarketValue(){
    return m_qty * m_marketPrice;
}

double Security::getUnrealizedPnL(){
    return (m_marketPrice - m_avgPurchasePrice) * m_qty;
}

double Security::getReturnPct(){
    return (m_marketPrice - m_avgPurchasePrice) / m_avgPurchasePrice * 100;
}
