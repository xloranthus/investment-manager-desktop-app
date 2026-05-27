#ifndef SECURITY_H
#define SECURITY_H
#include <QString>
#include "currency.h"

class Security
{
public:
    Security(QString ISIN, QString name, int qty, double purchasePrice, Currency baseCurrency);

    // getterek
    QString getISIN();
    QString getName();
    int getQty();
    double getAvgPurchasePrice();
    Currency getBaseCurrency();
    double getMarketPrice();
    double getMarketValue();
    double getUnrealizedPnL();
    double getReturnPct();

    double setMarketPrice();


private:
    QString m_ISIN, m_name;
    int m_qty;
    double m_avgPurchasePrice;
    Currency m_baseCurrency;
    double m_marketPrice;
};

#endif // SECURITY_H
