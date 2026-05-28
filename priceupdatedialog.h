#ifndef PRICEUPDATEDIALOG_H
#define PRICEUPDATEDIALOG_H

#include "security.h"
#include "currency.h"
#include <vector>
#include <QDialog>

namespace Ui {
class PriceUpdateDialog;
}

class PriceUpdateDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PriceUpdateDialog(const std::vector<Security> &securities, QWidget *parent = nullptr);
    ~PriceUpdateDialog();

    QString getISIN();
    double getNewMarketPrice();

private slots:
    void on_isinSelector_currentIndexChanged();

private:
    Ui::PriceUpdateDialog *ui;
    std::vector<Security> m_securities;
};

#endif // PRICEUPDATEDIALOG_H
