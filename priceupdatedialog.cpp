#include "priceupdatedialog.h"
#include "ui_priceupdatedialog.h"

#include <QDialogButtonBox>
#include <QDoubleSpinBox>
#include <QPushButton>

using std::vector;

PriceUpdateDialog::PriceUpdateDialog(const vector<Security>& securities, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::PriceUpdateDialog)
    , m_securities(securities)
{
    ui->setupUi(this);

    ui->nameField->setEnabled(false);
    ui->lastKnownMarketPriceField->setEnabled(false);
    ui->lastKnownMarketPriceField->setButtonSymbols(QAbstractSpinBox::NoButtons);
    ui->newMarketPriceField->setButtonSymbols(QAbstractSpinBox::NoButtons);
    ui->buttonBox->button(QDialogButtonBox::Ok)->setText("Update");

    for(const Security& security : m_securities){
        ui->isinSelector->addItem(security.getISIN());
    }

    on_isinSelector_currentIndexChanged();

}

PriceUpdateDialog::~PriceUpdateDialog()
{
    delete ui;
}

// publikus getterek
QString PriceUpdateDialog::getISIN(){
    return ui->isinSelector->currentText();
}

double PriceUpdateDialog::getNewMarketPrice(){
    return ui->newMarketPriceField->value();
}


void PriceUpdateDialog::on_isinSelector_currentIndexChanged()
{
    QString ISIN = ui->isinSelector->currentText();
    for(const Security &security : m_securities){
        if(security.getISIN() == ISIN){
            ui->nameField->setText(security.getName());
            ui->lastKnownMarketPriceField->setValue(security.getMarketPrice());
            ui->lastKnownMarketPriceCurrency->setText(currencyToQString(security.getBaseCurrency()));
            ui->newMarketPriceCurrency->setText(currencyToQString(security.getBaseCurrency()));
            return;
        }
    }
    throw std::invalid_argument("ISIN not found");
}

