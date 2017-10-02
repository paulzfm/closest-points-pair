#ifndef RANDGENDIALOG_H
#define RANDGENDIALOG_H

#include <QDialog>

#include <tuple>

using std::tuple;

namespace Ui {
class RandGenDialog;
}

class RandGenDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RandGenDialog(QWidget *parent = 0);
    ~RandGenDialog();

    tuple<int, int, int> get_data();

private:
    Ui::RandGenDialog *ui;
};

#endif // RANDGENDIALOG_H
