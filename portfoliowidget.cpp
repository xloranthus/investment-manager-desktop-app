#include "portfoliowidget.h"
#include <QTableWidgetItem>
#include <QHeaderView>

PortfolioWidget::PortfolioWidget(QWidget *parent)
    : QTableWidget(0, PortfolioColumn::COLUMNS_COUNT, parent)
{
    setHorizontalHeaderLabels({
        "ISIN",
        "Name",
        "Qty",
        "Avg. Purchase Price",
        "Market Price",
        "Market Value",
        "Unrealized P&L",
        "Return %"
    });

    setSelectionBehavior(QAbstractItemView::SelectRows);
    setEditTriggers(QAbstractItemView::NoEditTriggers);
    setAlternatingRowColors(true);
}


// publikus metodusok

void PortfolioWidget::addSecurity(const Security &security, const CurrencyConverter &converter, Currency displayCurrency){
    int row = rowCount();
    insertRow(row);
    updateSecurity(row, security, converter, displayCurrency);
}


void PortfolioWidget::updateSecurity(const Security &security, const CurrencyConverter &converter, Currency displayCurrency){
    int row = findRowByISIN(security.getISIN());
    updateSecurity(row, security, converter, displayCurrency);
}


void PortfolioWidget::removeSecurity(const QString &ISIN){
    int row = findRowByISIN(ISIN);
    removeRow(row);
}



// privat metodusok

int PortfolioWidget::findRowByISIN(const QString &ISIN){
    for(int row = 0; row < rowCount(); ++row){
        if(item(row, PortfolioColumn::ISIN)->text() == ISIN) return row;
    }
    throw std::invalid_argument("Find row by ISIN failed");
}


void PortfolioWidget::updateSecurity(int row, const Security &security, const CurrencyConverter &converter, Currency displayCurrency){

    Currency baseCurrency = security.getBaseCurrency();
    double convertedAvgPurchasePrice = converter.convert(security.getAvgPurchasePrice(), baseCurrency, displayCurrency);
    double convertedMarketPrice = converter.convert(security.getMarketPrice(), baseCurrency, displayCurrency);
    double convertedMarketValue = converter.convert(security.getMarketValue(), baseCurrency, displayCurrency);
    double convertedUnrealizedPnL = converter.convert(security.getUnrealizedPnL(), baseCurrency, displayCurrency);

    QString currencySuffix = " " + currencyToQString(displayCurrency);

    setItem(row, PortfolioColumn::ISIN, new QTableWidgetItem(security.getISIN()));
    setItem(row, PortfolioColumn::NAME, new QTableWidgetItem(security.getName()));
    setItem(row, PortfolioColumn::QTY, new QTableWidgetItem(QString::number(security.getQty())));
    setItem(row, PortfolioColumn::AVG_PURCHASE_PRICE, new QTableWidgetItem(QString::number(convertedAvgPurchasePrice, 'f', 2) + currencySuffix));
    setItem(row, PortfolioColumn::MARKET_PRICE, new QTableWidgetItem(QString::number(convertedMarketPrice, 'f', 2) + currencySuffix));
    setItem(row, PortfolioColumn::MARKET_VALUE, new QTableWidgetItem(QString::number(convertedMarketValue, 'f', 2) + currencySuffix));
    setItem(row, PortfolioColumn::UNREALIZED_PNL, new QTableWidgetItem(QString::number(convertedUnrealizedPnL, 'f', 2) + currencySuffix));
    setItem(row, PortfolioColumn::RETURN_PCT, new QTableWidgetItem(QString::number(security.getReturnPct(), 'f', 2) + " %"));
}

