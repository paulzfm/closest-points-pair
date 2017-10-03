#include "randgendialog.h"
#include "ui_randgendialog.h"

#include <QIntValidator>

using std::make_tuple;

RandGenDialog::RandGenDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RandGenDialog)
{
    ui->setupUi(this);
    auto v1 = new QIntValidator(1, 2000000, this);
    auto v2 = new QIntValidator(1, 1200, this);
    auto v3 = new QIntValidator(1, 600, this);

    ui->edit_size->setValidator(v1);
    ui->edit_max_x->setValidator(v2);
    ui->edit_max_y->setValidator(v3);
}

RandGenDialog::~RandGenDialog()
{
    delete ui;
}

tuple<int, int, int> RandGenDialog::get_data()
{
    return make_tuple(ui->edit_size->text().toInt(),
                      ui->edit_max_x->text().toInt(),
                      ui->edit_max_y->text().toInt());
}
