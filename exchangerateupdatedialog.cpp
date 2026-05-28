#include "exchangerateupdatedialog.h"
#include "ui_exchangerateupdatedialog.h"

#include <QDialogButtonBox>
#include <QPushButton>

using std::vector;

ExchangeRateUpdateDialog::ExchangeRateUpdateDialog(const vector<CurrencyPair> &currencyPairs, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ExchangeRateUpdateDialog)
    , m_currencyPairs(currencyPairs)
{
    ui->setupUi(this);

    ui->lastKnownExchangeRateField->setEnabled(false);
    ui->buttonBox->button(QDialogButtonBox::Ok)->setText("Update");

    for(const CurrencyPair &currencyPair : m_currencyPairs){
        ui->currencyPairSelector->addItem(currencyPair.m_name);
    }

    on_currencyPairSelector_currentIndexChanged();
}

ExchangeRateUpdateDialog::~ExchangeRateUpdateDialog()
{
    delete ui;
}

QString ExchangeRateUpdateDialog::getCurrencyPairName(){
    return ui->currencyPairSelector->currentText();
}

double ExchangeRateUpdateDialog::getNewExchangeRate(){
    return ui->newExchangeRateField->value();
}

void ExchangeRateUpdateDialog::on_currencyPairSelector_currentIndexChanged()
{
    QString chosenCurrencyPairName = ui->currencyPairSelector->currentText();
    for(const CurrencyPair &currencyPair : m_currencyPairs){
        if(currencyPair.m_name == chosenCurrencyPairName){
            ui->lastKnownExchangeRateField->setValue(currencyPair.m_exchangeRate);
            return;
        }
    }
    throw std::invalid_argument("Currency pair not found");
}

