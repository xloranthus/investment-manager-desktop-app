#ifndef TRANSACTIONDIALOG_H
#define TRANSACTIONDIALOG_H

#include "security.h"
#include "currency.h"
#include <vector>

#include <QDialog>
#include <QString>

enum Transaction{
    BUY_NEW = 0,
    REBUY,
    SELL
};

namespace Ui {
class TransactionDialog;
}

class TransactionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TransactionDialog(Transaction transaction, const std::vector<Security> &securities, QWidget *parent = nullptr);
    ~TransactionDialog();

    Transaction getTransaction();
    QString getISIN();
    QString getName();
    int getQty();
    double getPrice();
    Currency getBaseCurrency();


private slots:
    void on_sellButton_clicked();

    void on_buyButton_clicked();

    void on_rebuyButton_checkStateChanged();

    void on_isinSelector_currentIndexChanged();

private:
    Ui::TransactionDialog *ui;
    Transaction m_transaction;
    std::vector<Security> m_securities;

    void changeForm(Transaction transaction);
};

#endif // TRANSACTIONDIALOG_H
