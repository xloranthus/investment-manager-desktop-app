#include "security.h"
#include <QStringList>

// ezt a konstruktort fajlbol beolvasaskor hivom
Security::Security(QString ISIN, QString name, int qty, double purchasePrice, Currency baseCurrency, double marketPrice)
    : m_ISIN(ISIN)
    , m_name(name)
    , m_qty(qty)
    , m_avgPurchasePrice(purchasePrice)
    , m_baseCurrency(baseCurrency)
    , m_marketPrice(marketPrice)
{}

// ezt a konstruktort uj ertekpapir vasarlasakor hivom
Security::Security(QString ISIN, QString name, int qty, double purchasePrice, Currency baseCurrency)
    : Security(ISIN, name, qty, purchasePrice, baseCurrency, purchasePrice)
{}

QString Security::getISIN() const{
    return m_ISIN;
}

QString Security::getName() const{
    return m_name;
}

int Security::getQty() const{
    return m_qty;
}

double Security::getAvgPurchasePrice() const{
    return m_avgPurchasePrice;
}

Currency Security::getBaseCurrency() const{
    return m_baseCurrency;
}

double Security::getMarketPrice() const{
    return m_marketPrice;
}

// innentol szamitott ertekek kovetkeznek
double Security::getMarketValue() const{
    return m_qty * m_marketPrice;
}

double Security::getUnrealizedPnL() const{
    return (m_marketPrice - m_avgPurchasePrice) * m_qty;
}

double Security::getReturnPct() const{
    return (m_marketPrice - m_avgPurchasePrice) / m_avgPurchasePrice * 100;
}

// tovabbi metodusok

// a piaci arat modosithatja a felhasznalo is barmikor,
// tovabba minden vetel/eladas eseten automatikusan frissul a veteli/eladasi arra
void Security::updateMarketPrice(double newMarketPrice){
    m_marketPrice = newMarketPrice;
}

void Security::sell(int qty, double sellPrice){
    m_qty -= qty;
    updateMarketPrice(sellPrice);
}

void Security::reBuy(const Security &other){
    if(m_ISIN != other.m_ISIN || m_name != other.m_name || m_baseCurrency != other.m_baseCurrency){
        throw std::invalid_argument("ISIN code, name and base currency should be the same when re-buying the same security");
    }

    m_avgPurchasePrice = (m_avgPurchasePrice * m_qty + other.m_avgPurchasePrice * other.m_qty) / (m_qty + other.m_qty);
    m_qty += other.m_qty;
    updateMarketPrice(other.m_marketPrice);
}

QString Security::toQString() const{

    QStringList parts = {
        m_ISIN,
        m_name,
        QString::number(m_qty),
        QString::number(m_avgPurchasePrice, 'f', 2),
        currencyToQString(m_baseCurrency),
        QString::number(m_marketPrice, 'f', 2),
        QString::number(getMarketValue(), 'f', 2),
        QString::number(getUnrealizedPnL(), 'f', 2),
        QString::number(getReturnPct(), 'f', 2)
    };

    return parts.join(", ");
}

