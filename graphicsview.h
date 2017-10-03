#ifndef GRAPHICSVIEW_H
#define GRAPHICSVIEW_H

#include <QGraphicsView>
#include <QLabel>
#include <QMouseEvent>

#include "core/point.h"

#include <vector>

using std::vector;

// graphics view for plotting points
class GraphicsView : public QGraphicsView
{
    Q_OBJECT

public:
    explicit GraphicsView(QWidget *parent = 0, QLabel *status = 0, QLabel *pos = 0);

    // get all input points
    vector<Point> points();

    // get input points size
    int points_size() const;

    // insert random generated points
    void insert_points(const vector<Point>& pts);

    // clear all points
    void clear_points();

    // set closest points pair
    void set_closest_pair(const Point& p1, const Point& p2);

    // reset/clear closest points pair
    void reset_closest_pair();

private:
    // events
    void paintEvent(QPaintEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);

    // labels inherited from main window
    QLabel *status_label, *pos_label;

    // points data
    vector<QPointF> pts;
    vector<QPointF> emph_pts; // closest pair

    // helper functions
    QString qpoint_to_qstring(const QPointF& p);
};

#endif // GRAPHICSVIEW_H
