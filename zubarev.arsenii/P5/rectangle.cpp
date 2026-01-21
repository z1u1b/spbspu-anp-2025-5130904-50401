#include "rectangle.hpp"
#include <stdexcept>
zubarev::Rectangle::Rectangle(double width, double height, const point_t& pos) :
  width_(width),
  height_(height),
  pos_(pos)
{}

double zubarev::Rectangle::getArea() const
{
  return width_ * height_;
}

zubarev::rectangle_t zubarev::Rectangle::getFrameRect() const
{
  rectangle_t frame;
  frame.width = width_;
  frame.height = height_;
  frame.pos = pos_;
  return frame;
}

void zubarev::Rectangle::move(const point_t& p)
{
  pos_ = p;
}

void zubarev::Rectangle::move(double dx, double dy)
{
  pos_.x += dx;
  pos_.y += dy;
}

void zubarev::Rectangle::scale(double k)
{
  if (k <= 0.0) {
    throw std::invalid_argument("Scale factor must be positive");
  }
  width_ *= k;
  height_ *= k;
}
