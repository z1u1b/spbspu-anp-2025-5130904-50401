
#ifndef POLYGON_H
#define POLYGON_H

#include "shape.hpp"
namespace zubarev
{
  struct Polygon : Shape
  {
    Polygon(const size_t size, point_t* peaks);
    virtual ~Polygon();
    Polygon(const Polygon& w);
    Polygon& operator=(const Polygon& w);
    Polygon(Polygon&& w);
    Polygon& operator=(Polygon&& w);
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const point_t& p) override;
    void move(double dx, double dy) override;
    void scale(double k) override;
    point_t getCentroid();

  private:
    size_t size_;
    point_t* peaks_;
    point_t pos_;
  };
}

#endif
