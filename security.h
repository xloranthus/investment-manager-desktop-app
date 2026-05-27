#ifndef SECURITY_H
#define SECURITY_H
#include <QString>
#include "currency.h"

class Security
{
public:
    Security(QString ISIN, QString name, int qty, double purchasePrice, Currency baseCurrency, double marketPrice);
    Security(QString ISIN, QString name, int qty, double purchasePrice, Currency baseCurrency);

    // getterek
    QString getISIN() const;
    QString getName() const;
    int getQty() const;
    double getAvgPurchasePrice() const;
    Currency getBaseCurrency() const;
    double getMarketPrice() const;
    double getMarketValue() const;
    double getUnrealizedPnL() const;
    double getReturnPct() const;

    // tovabbi metodusok
    void updateMarketPrice(double newMarketPrice);
    void sell(int qty, double sellPrice);
    void reBuy(const Security &other);
    QString toQString() const;


private:
    QString m_ISIN, m_name;
    int m_qty;
    double m_avgPurchasePrice;
    Currency m_baseCurrency;
    double m_marketPrice;
};

#endif // SECURITY_H
