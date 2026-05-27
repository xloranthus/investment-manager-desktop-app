#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "portfoliowidget.h"
#include "simplecsvparser.h"
#include "transactiondialog.h"
#include <QMainWindow>
#include <QString>

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

private slots:
    void on_action_New_triggered();

    void on_action_Open_triggered();

    void on_action_Save_triggered();

    void on_actionSave_As_triggered();

    void on_action_Buy_New_triggered();

    void on_action_Re_buy_Existing_triggered();

    void on_action_Sell_triggered();

private:
    Ui::MainWindow *ui;
    PortfolioWidget *m_portfolioWidget;
    QActionGroup *m_displayCurrencies;
    CurrencyConverter m_converter;
    Currency m_displayCurrency;
    SimpleCSVParser m_parser;
    QString m_filePath;
    std::vector<CurrencyPair> m_currencyPairs;
    std::vector<CurrencyPair> m_defaultCurrencyPairs;
    std::vector<Security> m_securities;

    void on_displayCurrencies_triggered(QAction *action);
    void initiateTransaction(Transaction transaction);
};
#endif // MAINWINDOW_H
