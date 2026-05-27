#ifndef PORTFOLIOWIDGET_H
#define PORTFOLIOWIDGET_H

#include "security.h"
#include "currency.h"
#include <QTableWidget>

enum PortfolioColumn{
    ISIN = 0,
    NAME,
    QTY,
    AVG_PURCHASE_PRICE,
    MARKET_PRICE,
    MARKET_VALUE,
    UNREALIZED_PNL,
    RETURN_PCT,
    COLUMNS_COUNT
};


class PortfolioWidget : public QTableWidget
{
    Q_OBJECT

public:
    explicit PortfolioWidget(QWidget *parent = nullptr);

    void addSecurity(const Security &security, const CurrencyConverter &converter, Currency displayCurrency);
    void updateSecurity(const Security &security, const CurrencyConverter &converter, Currency displayCurrency);
    void removeSecurity(const QString &ISIN);
private:
    int findRowByISIN(const QString &ISIN);
    void updateSecurity(int row, const Security &security, const CurrencyConverter &converter, Currency displayCurrency);
};

#endif // PORTFOLIOWIDGET_H
