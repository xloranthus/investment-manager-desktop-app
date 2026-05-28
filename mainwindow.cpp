#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QActionGroup>
#include <QString>
#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>

using std::vector;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_portfolioWidget(new PortfolioWidget(this))
    , m_displayCurrencies(new QActionGroup(this))
{
    ui->setupUi(this);

    // beegetett alapertelmezett ertekek
    m_defaultCurrencyPairs = {
        CurrencyPair("EUR/HUF", 355.0),
        CurrencyPair("USD/HUF", 305.0),
        CurrencyPair("EUR/USD", 1.15)
    };

    // amig a felhasznalo felul nem irja, addig az alapertelmezett atvaltasi arfolyamokat fogja hasznalni
    m_currencyPairs = m_defaultCurrencyPairs;
    m_converter.calcExchangeRateMatrix(m_currencyPairs);

    setCentralWidget(m_portfolioWidget);

    m_displayCurrency = Currency::HUF;

    m_displayCurrencies->addAction(ui->action_HUF);
    m_displayCurrencies->addAction(ui->action_EUR);
    m_displayCurrencies->addAction(ui->action_USD);

    connect(m_displayCurrencies, &QActionGroup::triggered, this, &MainWindow::on_displayCurrencies_triggered);

}

MainWindow::~MainWindow()
{
    delete ui;
    // widget-eket elvileg nem kell felszabaditani, mert azokat a Qt automatikusan fel fogja, ha meg lett adva nekik szulo
}

void MainWindow::on_displayCurrencies_triggered(QAction *action){

    bool anyChecked = m_displayCurrencies->checkedAction() != nullptr;

    if(!anyChecked){
        action->setChecked(true);
        return;
    }

    m_displayCurrency = currencyFromQString(m_displayCurrencies->checkedAction()->text().replace("&", ""));

    for(const Security &security : m_securities){
        m_portfolioWidget->updateSecurity(security, m_converter, m_displayCurrency);
    }
}


void MainWindow::on_action_New_triggered()
{
    m_currencyPairs = m_defaultCurrencyPairs;
    m_securities.clear();
    m_portfolioWidget->setRowCount(0);
}





void MainWindow::on_action_Open_triggered()
{
    QString filePath = QFileDialog::getOpenFileName(
        this,
        "Open Portfolio File",
        "",
        "Portfolio Files (*.portfolio)"
    );
    if(filePath.isEmpty()) return;

    m_filePath = filePath;

    m_currencyPairs.clear();
    m_securities.clear();
    m_portfolioWidget->setRowCount(0);
    m_parser.readFile(m_filePath, m_currencyPairs, m_securities);

    for(const Security &security : m_securities){
        m_portfolioWidget->addSecurity(security, m_converter, m_displayCurrency);
    }

    QMessageBox::information(this, "", "Portfolio loaded successfully");
}




void MainWindow::on_action_Save_triggered()
{
    if(m_filePath.isEmpty()){
        on_actionSave_As_triggered();
        return;
    }

    m_parser.writeFile(m_filePath, m_currencyPairs, m_securities);
    QMessageBox::information(this, "", "Portfolio saved successfully");
}


void MainWindow::on_actionSave_As_triggered()
{
    QString filePath;
    filePath = QFileDialog::getSaveFileName(
        this,
        "Save Portfolio File",
        "",
        "Portfolio Files (*.portfolio)"
    );

    if(filePath.isEmpty()) return;

    m_filePath = filePath;

    on_action_Save_triggered();
}


void MainWindow::on_action_Buy_New_triggered()
{
    initiateTransaction(Transaction::BUY_NEW);
}


void MainWindow::on_action_Re_buy_Existing_triggered()
{
    initiateTransaction(Transaction::REBUY);
}



void MainWindow::on_action_Sell_triggered()
{
    initiateTransaction(Transaction::SELL);
}

void MainWindow::initiateTransaction(Transaction transaction)
{

    if(m_securities.empty() && transaction != Transaction::BUY_NEW){
        QMessageBox::information(this, "", QString("The portfolio is empty, there are no securities to %1").arg(transaction == Transaction::SELL ? "sell" : "re-buy"));
        return;
    }

    TransactionDialog dlg(transaction, m_securities, this);
    if(dlg.exec() == QDialog::Accepted){

        QString ISIN = dlg.getISIN();
        Security transactionSecurity(ISIN, dlg.getName(), dlg.getQty(), dlg.getPrice(), dlg.getBaseCurrency());

        switch(dlg.getTransaction()){
            case Transaction::SELL:

                for(int i=0; i<m_securities.size(); ++i){
                    if(m_securities[i].getISIN() == ISIN){
                        m_securities[i].sell(dlg.getQty(), dlg.getPrice());
                        if(m_securities[i].getQty() <= 0){
                            m_securities.erase(m_securities.begin() + i);
                            m_portfolioWidget->removeSecurity(ISIN);
                        }else{
                            m_portfolioWidget->updateSecurity(m_securities[i], m_converter, m_displayCurrency);
                        }
                        QMessageBox::information(this, "", "Transaction successful");
                        return;
                    }
                }
                throw std::invalid_argument("ISIN not found");

            case Transaction::BUY_NEW:

                m_securities.push_back(transactionSecurity);
                m_portfolioWidget->addSecurity(transactionSecurity, m_converter, m_displayCurrency);
                QMessageBox::information(this, "", "Transaction successful");
                return;

            case Transaction::REBUY:

                for(Security &security : m_securities){
                    if(security.getISIN() == transactionSecurity.getISIN()){
                        security.reBuy(transactionSecurity);
                        m_portfolioWidget->updateSecurity(security, m_converter, m_displayCurrency);
                        QMessageBox::information(this, "", "Transaction successful");
                        return;
                    }
                }
                throw std::invalid_argument("ISIN not found");

        }


    }
}

