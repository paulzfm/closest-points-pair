#include "randgendialog.h"
#include "ui_randgendialog.h"

using std::make_tuple;

RandGenDialog::RandGenDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RandGenDialog)
{
    ui->setupUi(this);
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
