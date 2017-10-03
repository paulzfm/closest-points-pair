#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "randgendialog.h"

#include "core/randgen.h"
#include "core/solver.h"
#include "core/naivesolver.h"

#include <time.h>

#include <QMessageBox>

using std::tie;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    // set up ui
    ui->setupUi(this);

    // set up status bar
    this->status_label = new QLabel("Ready.", this);
    this->pos_label = new QLabel("Position: ", this);
    this->statusBar()->addWidget(this->status_label);
    this->statusBar()->addPermanentWidget(this->pos_label);

    // set up graphics view
    this->view = new GraphicsView(this, this->status_label, this->pos_label);
    this->setCentralWidget(this->view);

    // maximize window
    this->showMaximized();
    this->setFocus();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionRandom_Generator_triggered()
{
    RandGenDialog dlg(this);
    if (dlg.exec() == RandGenDialog::Accepted) {
        int size, max_x, max_y;
        tie(size, max_x, max_y) = dlg.get_data();
        RandGen rg;
        vector<Point> new_pts = rg.generate(size, max_x, max_y);
        this->view->insert_points(new_pts);
        this->status_label->setText(QString("%1 random points generated, total %2.")
                                    .arg(size)
                                    .arg(this->view->points_count()));
        this->view->reset_closest_pair();
    }
}

void MainWindow::solve(function<tuple<tuple<Point, Point>, double>(const vector<Point>&)> solver)
{
    if (this->view->points_count() < 2) {
        QMessageBox::about(NULL, "Error",
                           "Input size should be greater than 2 points.");
        return;
    }

    Point p1, p2;
    double d;
    tuple<Point, Point> ps;

    this->view->reset_closest_pair();

    clock_t start = clock();
    tie(ps, d) = solver(this->view->points());
    clock_t end = clock();

    tie(p1, p2) = ps;
    double time = (double) (end - start) / CLOCKS_PER_SEC * 1000.0;
    this->status_label->setText(
                QString("Closest points pair %1 and %2, distance %3, time elapsed %4ms.")
                .arg(QString::fromStdString(p1.str()))
                .arg(QString::fromStdString(p2.str()))
                .arg(d)
                .arg(time));
    this->view->set_closest_pair(p1, p2);
}

void MainWindow::on_actionSolver_triggered()
{
    solve([](const vector<Point>& pts) {
        Solver solver(pts);
        return solver.solve();
    });
}

void MainWindow::on_actionNaive_Solver_triggered()
{
    if (this->view->points_count() > 60000) {
        QMessageBox::about(NULL, "Error",
                           "Input size too large for naive solver, maximum 60000 points.");
        return;
    }

    solve([](const vector<Point>& pts) {
        NaiveSolver solver(pts);
        return solver.solve();
    });
}

void MainWindow::on_actionClear_Points_triggered()
{
    this->view->clear_points();
}

void MainWindow::on_actionSmall_triggered()
{
    this->view->set_point_size(1);
    ui->actionSmall->setChecked(true);
    ui->actionMiddle->setChecked(false);
    ui->actionLarge->setChecked(false);
}

void MainWindow::on_actionMiddle_triggered()
{
    this->view->set_point_size(3);
    ui->actionSmall->setChecked(false);
    ui->actionMiddle->setChecked(true);
    ui->actionLarge->setChecked(false);
}

void MainWindow::on_actionLarge_triggered()
{
    this->view->set_point_size(5);
    ui->actionSmall->setChecked(false);
    ui->actionMiddle->setChecked(false);
    ui->actionLarge->setChecked(true);
}
