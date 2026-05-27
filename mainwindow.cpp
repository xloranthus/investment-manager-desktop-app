#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QActionGroup>

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
    m_currencyPairs = defaultCurrencyPairs;
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

    m_displayCurrency = currencyFromQString(m_displayCurrencies->checkedAction()->text());

    for(const Security &security : m_securities){
        m_portfolioWidget->updateSecurity(security, m_converter, m_displayCurrency);
    }
}

