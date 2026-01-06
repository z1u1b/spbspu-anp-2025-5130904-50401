#ifndef SHAPE_H
#define SHAPE_H
#include "geom.hpp"
#include <cstddef>

namespace zubarev
{
  struct Shape
  {
    virtual ~Shape() = default;
    virtual double getArea() const = 0;
    virtual rectangle_t getFrameRect() const = 0;
    virtual void move(const point_t& p) = 0;
    virtual void move(double dx, double dy) = 0;
    virtual void scale(double k) = 0;
  };

  // point_t getExtL(const rectangle_t& frame);
  // point_t getExtR(const rectangle_t& frame);
  // void scaleAtCertainPnt(Shape* shapes[], size_t size, point_t userPos, double k);
  // rectangle_t getWholeFrame(Shape* shapes[], size_t size);
  // double getWholeArea(Shape* shapes[], size_t size);
  // void printInfo(Shape* shapes[], size_t size);
}

#endif
