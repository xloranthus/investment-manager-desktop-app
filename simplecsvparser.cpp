#include "simplecsvparser.h"
#include "currency.h"
#include <QStringList>
#include <QFile>
#include <QTextStream>
using std::vector;


void SimpleCSVParser::readFile(const QString &path, std::vector<CurrencyPair> &currencyPairs, std::vector<Security> &securities){
    QFile f(path);
    f.open(QFile::ReadOnly | QFile::Text);
    QString content = QString::fromUtf8(f.readAll());
    f.close();

    const QStringList lines = content.split('\n');
    QStringList parts;

    // CurrencyPair
    double exchangeRate;

    // Security
    int qty;
    double avgPurchasePrice, marketPrice;

    bool typeConversionOk = true;

    for(const QString &line : lines){
        parts = line.split(',');
        if(parts[0] == "currencypair"){
            exchangeRate = parts[2].toDouble(&typeConversionOk);
            if(!typeConversionOk) throw std::invalid_argument("Invalid exchange rate");

            currencyPairs.emplace_back(parts[1], exchangeRate);
            continue;
        }
        if(parts[0] == "security"){
            qty = parts[3].toInt(&typeConversionOk);
            if(!typeConversionOk) throw std::invalid_argument("Invalid quantity");

            avgPurchasePrice = parts[4].toDouble(&typeConversionOk);
            if(!typeConversionOk) throw std::invalid_argument("Invalid average purchase price");

            marketPrice = parts[6].toDouble(&typeConversionOk);
            if(!typeConversionOk) throw std::invalid_argument("Invalid market price");

            securities.emplace_back(parts[1], parts[2], qty, avgPurchasePrice, currencyFromQString(parts[5]), marketPrice);
            continue;
        }
        throw std::invalid_argument("Invalid line type");
    }
}


void SimpleCSVParser::writeFile(const QString &path, const std::vector<CurrencyPair> &currencyPairs, const std::vector<Security> &securities){
    QStringList line, lines;

    for(const CurrencyPair &currencyPair : currencyPairs){
        line = {
            "currencypair",
            currencyPair.m_name,
            QString::number(currencyPair.m_exchangeRate, 'f', 2)
        };
        lines.append(line.join(','));
    }

    for(const Security &security : securities){
        line = {
            "security",
            security.getISIN(),
            security.getName(),
            QString::number(security.getQty()),
            QString::number(security.getAvgPurchasePrice(), 'f', 2),
            currencyToQString(security.getBaseCurrency()),
            QString::number(security.getMarketPrice(), 'f', 2)
        };
        lines.append(line.join(','));
    }

    QString content = lines.join('\n');

    QFile f(path);
    f.open(QFile::WriteOnly | QFile::Text);
    f.write(content.toUtf8());
    f.close();
}



