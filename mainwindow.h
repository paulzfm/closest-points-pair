#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "core/point.h"
#include <vector>

using std::vector;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionRandom_Generator_triggered();

    void on_actionSolver_triggered();

private:
    Ui::MainWindow *ui;

    vector<Point> pts;
};

#endif // MAINWINDOW_H
