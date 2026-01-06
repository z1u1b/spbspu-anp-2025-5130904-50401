#include "utils.hpp"
#include <iostream>
zubarev::point_t zubarev::getExtL(const rectangle_t& frame)
{
  return {frame.pos.x - frame.width / 2, frame.pos.y + frame.height / 2};
}

zubarev::point_t zubarev::getExtR(const rectangle_t& frame)
{
  return {frame.pos.x + frame.width / 2, frame.pos.y - frame.height / 2};
}

void zubarev::scaleAtCertainPnt(Shape* shapes[], size_t size, point_t userPos, double k)
{
  for (size_t i = 0; i < size; i++) {

    rectangle_t frame = shapes[i]->getFrameRect();
    point_t p1 = getExtR(frame);

    shapes[i]->move(userPos);

    frame = shapes[i]->getFrameRect();
    point_t p2 = getExtR(frame);

    double dx = -k * (p2.x - p1.x);
    double dy = -k * (p2.y - p1.y);

    shapes[i]->scale(k);
    shapes[i]->move(dx, dy);
  }
}

zubarev::rectangle_t zubarev::getWholeFrame(Shape* shapes[], size_t size)
{
  rectangle_t frame = shapes[0]->getFrameRect();

  point_t leftExPt = getExtL(frame);
  point_t rightExPt = getExtR(frame);

  for (size_t i = 1; i < size; i++) {
    frame = shapes[i]->getFrameRect();

    if (getExtL(frame).x < leftExPt.x) {
      leftExPt.x = getExtL(frame).x;
    }
    if (getExtR(frame).x > rightExPt.x) {
      rightExPt.x = getExtR(frame).x;
    }
    if (getExtL(frame).y > leftExPt.y) {
      leftExPt.y = getExtL(frame).y;
    }
    if (getExtR(frame).y < rightExPt.y) {
      rightExPt.y = getExtR(frame).y;
    }
  }

  rectangle_t allFrame = {};
  allFrame.height = std::abs(leftExPt.y - rightExPt.y);
  allFrame.width = std::abs(leftExPt.x - rightExPt.x);
  allFrame.pos = {leftExPt.x + allFrame.width / 2, leftExPt.y - allFrame.height / 2};
  return allFrame;
}

double zubarev::getWholeArea(Shape* shapes[], size_t size)
{
  double sum = 0;
  for (size_t i = 0; i < size; i++) {
    sum += shapes[i]->getArea();
  }
  return sum;
}

void zubarev::printInfo(Shape* shapes[], size_t size)
{
  for (size_t i = 0; i < size; ++i) {
    std::cout << "Figure " << i + 1 << '\n';

    rectangle_t frame = shapes[i]->getFrameRect();
    std::cout << "Area: " << shapes[i]->getArea() << '\n';
    std::cout << "Frame width: " << frame.width << '\n';
    std::cout << "Frame height: " << frame.height << '\n';
    std::cout << "Frame center: " << frame.pos.x << " " << frame.pos.y << '\n';
    std::cout << '\n';
  }

  std::cout << "All\n";
  rectangle_t allFrame = getWholeFrame(shapes, size);
  std::cout << "Whole area: " << getWholeArea(shapes, size) << '\n';
  std::cout << "Whole frame width: " << allFrame.width << '\n';
  std::cout << "Whole frame height: " << allFrame.height << '\n';
  std::cout << "Whole frame center: " << allFrame.pos.x << " " << allFrame.pos.y << '\n';
  std::cout << '\n';
}
