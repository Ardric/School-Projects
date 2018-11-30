#ifndef _LOCATION_H_
#define _LOCATION_H_

#include <iostream>
#include <string>

using namespace std;

class Location
{
  public:
    Location ()
      : x(0), y(0) { }

    Location (int xx, int yy)
      : x(xx), y(yy) { }

    int getX() const { return x; }
    int getY() const { return y; }

    bool isEqualTo (const Location& other) const;

    bool isNotEqualTo (const Location& other) const;

    string toString() const;

    Location east() const { return Location(x+1, y); }

    Location west() const { return Location(x-1, y); }

    Location north() const { return Location(x, y-1); }

    Location south() const { return Location(x, y+1); }

    bool operator== (const Location& b) const
    {
      return (getX() == b.getX()) and (getY() == b.getY());
    }

  private:
    int x, y;
};

namespace std
{
  template<>
    struct hash<Location>
    {
      size_t operator() (const Location& value) const
      {
	return 13* value.getX() + value.getY();
      }
    };
}

#endif
