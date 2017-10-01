#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "core/randgen.h"
#include "core/solver.h"
#include <tuple>
#include <QDebug>

using std::tie;
using std::tuple;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionRandom_Generator_triggered()
{
    RandGen rg;
    vector<Point> randoms = rg.generate(3000, 500, 500);
    pts.insert(pts.begin(), randoms.begin(), randoms.end());
    qDebug() << pts.size() << " points inserted\n";
}

void MainWindow::on_actionSolver_triggered()
{
    Solver solver(pts);
    Point p1, p2;
    double d;
    tuple<Point, Point> ps;
    tie(ps, d) = solver.solve();
    tie(p1, p2) = ps;
    qDebug() << ": " << d;
}
