#include "transactiondialog.h"
#include "ui_transactiondialog.h"

#include <QDialogButtonBox>
#include <QString>
#include <QPushButton>
#include <QMessageBox>
#include <QRegularExpressionValidator>
#include "currency.h"

using std::vector;

TransactionDialog::TransactionDialog(Transaction transaction, const vector<Security> &securities, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::TransactionDialog)
    , m_transaction(transaction)
    , m_securities(securities)
{

    ui->setupUi(this);

    if(m_securities.empty()){
        ui->sellButton->setEnabled(false);
        ui->rebuyButton->setEnabled(false);
    }

    ui->dialogButtons->button(QDialogButtonBox::Ok)->setText("Transact");

    ui->priceField->setButtonSymbols(QAbstractSpinBox::NoButtons);

    QRegularExpressionValidator *commaGuard = new QRegularExpressionValidator(
        QRegularExpression("[^,]*"), this
    );
    ui->isinField->setValidator(commaGuard);
    ui->nameField->setValidator(commaGuard);

    connect(ui->dialogButtons, &QDialogButtonBox::accepted, this, &TransactionDialog::checkTransactionBeforeSubmit);
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


// publikus getterek

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
            if(!m_securities.empty()){
                ui->rebuyButton->setEnabled(true);
            }

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

            on_isinSelector_currentIndexChanged();

            return;

        case Transaction::SELL:
            ui->rebuyButton->setEnabled(false);

            ui->isinSelector->setVisible(true);
            ui->isinField->setVisible(false);
            ui->nameField->setEnabled(false);
            ui->currencySelector->setEnabled(false);

            on_isinSelector_currentIndexChanged();

            return;
    }
}

void TransactionDialog::checkTransactionBeforeSubmit(){

    if(m_transaction == Transaction::BUY_NEW){
        QString chosenISIN = ui->isinField->text();
        for(const Security &security : m_securities){
            if(security.getISIN() == chosenISIN){
                QMessageBox::information(this, "", "If you wish to re-buy an already bought security, please check the \"Re-buy a security already in the portfolio\" checkbox");
                return;
            }
        }
    }
    QDialog::accept();
    return;

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

