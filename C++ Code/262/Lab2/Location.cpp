#include "Location.h"

#include <sstream>

bool Location::isEqualTo (const Location& other) const
{
  return x == other.x && y == other.y;
}

bool Location::isNotEqualTo (const Location& other) const
{
  return x != other.x || y != other.y;
}

string Location::toString () const
{
  ostringstream out;
  out << "(" << x << "," << y << ")";
  return out.str();
}
