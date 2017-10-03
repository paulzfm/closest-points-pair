#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "core/point.h"
#include "graphicsview.h"

#include <QMainWindow>

#include <functional>
#include <tuple>

using std::function;
using std::tuple;

namespace Ui {
class MainWindow;
}

// main application window
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    // triggered when press "Run -> Random Point Generator"
    void on_actionRandom_Generator_triggered();

    // triggered when press "Run -> Solver"
    void on_actionSolver_triggered();

    // triggered when press "Run -> Naive Solver"
    void on_actionNaive_Solver_triggered();

    // triggered when press "Plot -> Clear Points"
    void on_actionClear_Points_triggered();

    // triggered when press "Plot -> Set Point Size"
    void on_actionSmall_triggered();
    void on_actionMiddle_triggered();
    void on_actionLarge_triggered();

private:
    Ui::MainWindow *ui;
    QLabel *status_label, *pos_label;
    GraphicsView *view;

    void solve(function<tuple<tuple<Point, Point>, double>(const vector<Point>&)> solver);
};

#endif // MAINWINDOW_H
