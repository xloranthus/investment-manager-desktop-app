#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "portfoliowidget.h"
#include "simplecsvparser.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private:
    Ui::MainWindow *ui;
    PortfolioWidget *m_portfolioWidget;
    QActionGroup *m_displayCurrencies;
    CurrencyConverter m_converter;
    Currency m_displayCurrency;
    SimpleCSVParser m_parser;
    std::vector<CurrencyPair> m_currencyPairs;
    std::vector<CurrencyPair> m_defaultCurrencyPairs;
    std::vector<Security> m_securities;

    void on_displayCurrencies_triggered(QAction *action);
};
#endif // MAINWINDOW_H
