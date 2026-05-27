#include "mainwindow.h"

#include <QApplication>
#include <QDebug>
#include "currency.h"
#include "security.h"
#include "simplecsvparser.h"
using std::vector;

int main(int argc, char *argv[])
{

    /*
    // segedosztalyok tesztelese
    vector<CurrencyPair> currencyPairs;
    currencyPairs.emplace_back("EUR/HUF", 300);
    currencyPairs.emplace_back("USD/HUF", 200);
    currencyPairs.emplace_back("EUR/USD", 1.5);

    vector<Security> securities;
    securities.emplace_back("ABC123", "VanEck Semiconductor", 80, 71.32, currencyFromQString("EUR"));
    securities.emplace_back("DEF456", "Military Defense", 45, 65.20, currencyFromQString("USD"), 98.70);
    securities.emplace_back("BUX789", "Hungarian Index", 10, 18000.5, currencyFromQString("HUF"), 23500.2);

    QString testPath = "/Users/lorantertekes/QtProjects/InvestmentManagerDesktopApp/test1.portfolio";
    SimpleCSVParser parser;
    parser.writeFile(testPath, currencyPairs, securities);

    currencyPairs.clear();
    securities.clear();
    parser.readFile(testPath, currencyPairs, securities);

    for(const Security &security : securities){
        qDebug() << security.toQString();
    }

    CurrencyConverter converter;
    converter.calcExchangeRateMatrix(currencyPairs);
    qDebug() << converter.convert(1, Currency::EUR, Currency::HUF);
    qDebug() << converter.convert(1, Currency::EUR, Currency::USD);
    qDebug() << converter.convert(1, Currency::EUR, Currency::EUR);
    qDebug() << converter.convert(1, Currency::USD, Currency::HUF);
    qDebug() << converter.convert(1, Currency::USD, Currency::EUR);
    qDebug() << converter.convert(1, Currency::USD, Currency::USD);
    qDebug() << converter.convert(1, Currency::HUF, Currency::EUR);
    qDebug() << converter.convert(1, Currency::HUF, Currency::USD);
    qDebug() << converter.convert(1, Currency::HUF, Currency::HUF);
    */

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return QApplication::exec();
}
