#include "transactiondialog.h"
#include "ui_transactiondialog.h"

#include <QDialogButtonBox>
#include <QString>
#include <QPushButton>
#include "currency.h"

using std::vector;

TransactionDialog::TransactionDialog(Transaction transaction, const vector<Security> &securities, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::TransactionDialog)
    , m_transaction(transaction)
    , m_securities(securities)
{
    ui->setupUi(this);

    ui->dialogButtons->button(QDialogButtonBox::Ok)->setText("Transact");

    connect(ui->dialogButtons, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(ui->dialogButtons, &QDialogButtonBox::rejected, this, &QDialog::reject);

    ui->currencySelector->addItems({
        "HUF",
        "EUR",
        "USD"
    });

    for(const Security& security : m_securities){
        ui->isinSelector->addItem(security.getISIN());
    }

    switch(m_transaction){
        case Transaction::BUY_NEW:
            ui->buyButton->setChecked(true);
            ui->rebuyButton->setChecked(false);
            break;

        case Transaction::REBUY:
            ui->buyButton->setChecked(true);
            ui->rebuyButton->setChecked(true);
            break;

        case Transaction::SELL:
            ui->sellButton->setChecked(true);
            ui->rebuyButton->setChecked(false);
            break;

    }

    changeForm(m_transaction);

}

TransactionDialog::~TransactionDialog()
{
    delete ui;
}


Transaction TransactionDialog::getTransaction(){
    return m_transaction;
}


QString TransactionDialog::getISIN(){
    switch(m_transaction){
        case Transaction::REBUY:
        case Transaction::SELL:
            return ui->isinSelector->currentText();
        case Transaction::BUY_NEW:
            return ui->isinField->text();
    }
}

QString TransactionDialog::getName(){
    return ui->nameField->text();
}

int TransactionDialog::getQty(){
    return ui->qtyField->value();
}


double TransactionDialog::getPrice(){
    return ui->priceField->value();
}

Currency TransactionDialog::getBaseCurrency(){
    return currencyFromQString(ui->currencySelector->currentText());
}


// privat metodusok

void TransactionDialog::changeForm(Transaction transaction){

    switch(transaction){
        case Transaction::BUY_NEW:
            ui->rebuyButton->setEnabled(true);

            ui->isinSelector->setVisible(false);
            ui->isinField->setVisible(true);
            ui->nameField->setEnabled(true);
            ui->currencySelector->setEnabled(true);

            return;

        case Transaction::REBUY:
            ui->rebuyButton->setEnabled(true);

            ui->isinSelector->setVisible(true);
            ui->isinField->setVisible(false);
            ui->nameField->setEnabled(false);
            ui->currencySelector->setEnabled(false);

            return;

        case Transaction::SELL:
            ui->rebuyButton->setEnabled(false);

            ui->isinSelector->setVisible(true);
            ui->isinField->setVisible(false);
            ui->nameField->setEnabled(false);
            ui->currencySelector->setEnabled(false);

            return;
    }
}


void TransactionDialog::on_sellButton_clicked()
{
    m_transaction = Transaction::SELL;
    changeForm(m_transaction);
}

void TransactionDialog::on_buyButton_clicked()
{
    if(ui->rebuyButton->isChecked()){
        m_transaction = Transaction::REBUY;
    }else{
        m_transaction = Transaction::BUY_NEW;
    }
    changeForm(m_transaction);
}


void TransactionDialog::on_rebuyButton_checkStateChanged()
{
    on_buyButton_clicked();
}


void TransactionDialog::on_isinSelector_currentIndexChanged()
{
    QString ISIN = ui->isinSelector->currentText();
    for(const Security &security : m_securities){
        if(security.getISIN() == ISIN){
            ui->nameField->setText(security.getName());
            ui->currencySelector->setCurrentText(currencyToQString(security.getBaseCurrency()));
            return;
        }
    }
    throw std::invalid_argument("ISIN not found");
}

