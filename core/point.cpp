#include "point.h"

#include <iostream>
#include <QDebug>

std::ostream& operator << (std::ostream& out, const Point& p)
{
    out << "(" << p.x << ", " << p.y << ")";
    return out;
}

QDebug operator << (QDebug& out, const Point& p)
{
    QDebugStateSaver saver(out);
    out.nospace() << "(" << p.x << ", " << p.y << ")";
    return out;
}
