#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "randgendialog.h"

#include "core/randgen.h"
#include "core/solver.h"
#include "core/naivesolver.h"

#include <iostream>
#include <tuple>
#include <time.h>

#include <QPainter>
#include <QPen>
#include <QStringBuilder>

using std::tie;
using std::tuple;
using std::cerr;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->showMaximized();
    qApp->installEventFilter(this);

    this->status_label = new QLabel("Ready.", this);
    this->pos_label = new QLabel("Position: ", this);
    this->statusBar()->addWidget(this->status_label);
    this->statusBar()->addPermanentWidget(this->pos_label);

    this->setFocus();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPen linepen(Qt::black);
    linepen.setCapStyle(Qt::RoundCap);
    linepen.setWidth(5);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(linepen);
    for (const auto& p: pts) {
        painter.drawPoint(toQPointF(p));
    }

    linepen.setColor(Qt::red);
    painter.setPen(linepen);
    for (const auto& p: emph_pts) {
        painter.drawPoint(p);
    }
}

void MainWindow::mousePressEvent(QMouseEvent *e)
{
    Point p = toPoint(e->localPos());
    pts.push_back(p);
    this->status_label->setText(QString("Point %1 inserted, total %2.")
                                .arg(QString::fromStdString(p.str()))
                                .arg(pts.size()));
    update();
}

bool MainWindow::eventFilter(QObject *, QEvent *event)
{
    if (event->type() == QEvent::MouseMove) {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
        Point p = toPoint(mouseEvent->localPos());
        this->pos_label->setText(QString("Position: %1").arg(QString::fromStdString(p.str())));
        emph_pts.clear();
    }
    return false;
}

void MainWindow::on_actionRandom_Generator_triggered()
{
    RandGenDialog dlg(this);
    if (dlg.exec() == RandGenDialog::Accepted) {
        int size, max_x, max_y;
        tie(size, max_x, max_y) = dlg.get_data();
        RandGen rg;
        vector<Point> new_pts = rg.generate(size, max_x, max_y);
        pts.insert(pts.end(), new_pts.begin(), new_pts.end());
        this->status_label->setText(QString("%1 random points generated, total %2.")
                                    .arg(size)
                                    .arg(pts.size()));
        emph_pts.clear();
        update();
    }
}

void MainWindow::solve(function<tuple<tuple<Point, Point>, double>(vector<Point>&)> solver)
{
    Point p1, p2;
    double d;
    tuple<Point, Point> ps;

    emph_pts.clear();
    update();

    clock_t start = clock();
    tie(ps, d) = solver(pts);
    clock_t end = clock();

    tie(p1, p2) = ps;
    double time = (double) (end - start) / CLOCKS_PER_SEC * 1000.0;
    this->status_label->setText(
                QString("Closest points pair %1 and %2, distance %3, time elapsed %4ms.")
                .arg(QString::fromStdString(p1.str()))
                .arg(QString::fromStdString(p2.str()))
                .arg(d)
                .arg(time));
    emph_pts.push_back(toQPointF(p1));
    emph_pts.push_back(toQPointF(p2));
    update();
}

void MainWindow::on_actionSolver_triggered()
{
    solve([](vector<Point>& pts) {
        Solver solver(pts);
        return solver.solve();
    });
}

void MainWindow::on_actionNaive_Solver_triggered()
{
    solve([](vector<Point>& pts) {
        NaiveSolver solver(pts);
        return solver.solve();
    });
}

void MainWindow::on_actionClear_Points_triggered()
{
    pts.clear();
    emph_pts.clear();
    update();
}
