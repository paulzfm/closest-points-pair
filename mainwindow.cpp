#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "core/randgen.h"
#include "core/solver.h"
#include "core/naivesolver.h"

#include <iostream>
#include <tuple>

using std::tie;
using std::tuple;
using std::cerr;

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
    pts = rg.generate(1000000, 10000, 10000);
    cerr << pts.size() << " points inserted";
}

void MainWindow::on_actionSolver_triggered()
{
    Solver solver(pts);
    Point p1, p2;
    double d;
    tuple<Point, Point> ps;
    tie(ps, d) = solver.solve();
    tie(p1, p2) = ps;
    cerr << p1 << " -> " << p2 << " : " << d;
}

void MainWindow::on_actionNaive_Solver_triggered()
{
    NaiveSolver solver(pts);
    Point p1, p2;
    double d;
    tuple<Point, Point> ps;
    tie(ps, d) = solver.solve();
    tie(p1, p2) = ps;
    cerr << p1 << " -> " << p2 << " : " << d;
}
