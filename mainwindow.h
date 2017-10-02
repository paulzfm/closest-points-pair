#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "core/point.h"

#include <QMainWindow>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QPointF>
#include <QLabel>
#include <QObject>
#include <QEvent>

#include <vector>
#include <functional>
#include <tuple>

using std::vector;
using std::function;
using std::tuple;

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

    void on_actionNaive_Solver_triggered();

    void on_actionClear_Points_triggered();

private:
    Ui::MainWindow *ui;
    QLabel *status_label, *pos_label;

    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *e);
    bool eventFilter(QObject *, QEvent *event);

    void solve(function<tuple<tuple<Point, Point>, double>(vector<Point>&)> solver);

    vector<Point> pts;
    vector<QPointF> emph_pts;

    QPointF toQPointF(const Point& p)
    {
        return QPointF(p.x, p.y);
    }

    Point toPoint(const QPointF& p)
    {
        return Point(p.x(), p.y());
    }
};

#endif // MAINWINDOW_H
