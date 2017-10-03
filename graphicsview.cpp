#include "graphicsview.h"

#include <QDebug>

GraphicsView::GraphicsView(QWidget *parent, QLabel *status, QLabel *pos)
    : QGraphicsView(parent), status_label(status), pos_label(pos)
{
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    this->setMouseTracking(true);
}

vector<Point> GraphicsView::points()
{
    vector<Point> v;
    for (const auto& p: pts) {
        v.push_back(Point(p.x(), p.y()));
    }
    return v;
}

int GraphicsView::points_size() const
{
    return pts.size();
}

void GraphicsView::insert_points(const vector<Point> &points)
{
    for (const auto& p: points) {
        pts.push_back(QPointF(p.x, p.y));
    }
    this->viewport()->update();
}

void GraphicsView::clear_points()
{
    pts.clear();
    emph_pts.clear();
    this->viewport()->update();
}

void GraphicsView::set_closest_pair(const Point &p1, const Point &p2)
{
    emph_pts.clear();
    emph_pts.push_back(QPointF(p1.x, p1.y));
    emph_pts.push_back(QPointF(p2.x, p2.y));
    this->viewport()->update();
}

void GraphicsView::reset_closest_pair()
{
    emph_pts.clear();
    this->viewport()->update();
}

void GraphicsView::paintEvent(QPaintEvent *e)
{
    QPainter painter(this->viewport());
    QPen linepen(Qt::black);
    linepen.setCapStyle(Qt::RoundCap);
    linepen.setWidth(5);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(linepen);
    for (const auto& p: pts) {
        painter.drawPoint(p);
    }

    linepen.setColor(Qt::red);
    painter.setPen(linepen);
    for (const auto& p: emph_pts) {
        painter.drawPoint(p);
    }

    QGraphicsView::paintEvent(e);
}

void GraphicsView::mousePressEvent(QMouseEvent *e)
{
    QPointF p = e->localPos();
    pts.push_back(p);
    this->status_label->setText(QString("Point %1 inserted, total %2.")
                                .arg(qpoint_to_qstring(p))
                                .arg(pts.size()));

    this->viewport()->update();
    QGraphicsView::mousePressEvent(e);
}

void GraphicsView::mouseMoveEvent(QMouseEvent *e)
{
    QPointF p = e->localPos();
    this->pos_label->setText(QString("Position: %1").arg(qpoint_to_qstring(p)));
    emph_pts.clear();

    QGraphicsView::mouseMoveEvent(e);
}

QString GraphicsView::qpoint_to_qstring(const QPointF &p)
{
    return QString("(%1, %2)").arg(p.x()).arg(p.y());
}
