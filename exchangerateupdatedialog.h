#ifndef EXCHANGERATEUPDATEDIALOG_H
#define EXCHANGERATEUPDATEDIALOG_H

#include <QDialog>
#include "currency.h"
#include <vector>

namespace Ui {
class ExchangeRateUpdateDialog;
}

class ExchangeRateUpdateDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ExchangeRateUpdateDialog(const std::vector<CurrencyPair> &currencyPairs, QWidget *parent = nullptr);
    ~ExchangeRateUpdateDialog();

    QString getCurrencyPairName();
    double getNewExchangeRate();

private slots:
    void on_currencyPairSelector_currentIndexChanged();

private:
    Ui::ExchangeRateUpdateDialog *ui;
    std::vector<CurrencyPair> m_currencyPairs;
};

#endif // EXCHANGERATEUPDATEDIALOG_H
