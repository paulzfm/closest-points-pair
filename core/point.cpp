#include "point.h"

std::ostream& operator << (std::ostream& out, const Point& p)
{
    out << p.str();
    return out;
}
