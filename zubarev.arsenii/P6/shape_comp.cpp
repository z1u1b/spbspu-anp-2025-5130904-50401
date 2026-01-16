#include "shape_comp.hpp"
#include <iostream>
zubarev::Shape_comp::Shape_comp() :
  shapes_(nullptr),
  size_(0),
  capacity_(0)
{}

zubarev::Shape_comp::~Shape_comp() noexcept
{
  for (size_t i = 0; i < size_; ++i) {
    delete shapes_[i];
  }
  delete[] shapes_;
}

zubarev::Shape_comp::Shape_comp(const Shape_comp& w) :
  size_(w.size_),
  capacity_(w.capacity_),
  shapes_(w.size_ ? new Shape*[w.capacity_] : nullptr)
{
  for (size_t i = 0; i < size_; ++i) {
    shapes_[i] = w.shapes_[i];
  }
}

zubarev::Shape_comp& zubarev::Shape_comp::operator=(const Shape_comp& w)
{
  Shape** r = nullptr;
  if (w.size_) {
    r = new Shape*[w.capacity_];
    for (size_t i = 0; i < w.size_; ++i) {
      r[i] = w.shapes_[i];
    }
  }
  delete[] shapes_;
  shapes_ = r;
  size_ = w.size_;
  capacity_ = w.capacity_;
  return *this;
}

zubarev::Shape_comp::Shape_comp(Shape_comp&& w) :
  size_(w.size_),
  capacity_(w.capacity_),
  shapes_(w.shapes_)
{
  w.shapes_ = nullptr;
}

zubarev::Shape_comp& zubarev::Shape_comp::operator=(zubarev::Shape_comp&& w)
{
  if (this == &w) {
    return *this;
  }
  delete[] shapes_;
  shapes_ = w.shapes_;
  size_ = w.size_;
  capacity_ = w.capacity_;
  w.shapes_ = nullptr;
  return *this;
}

double zubarev::Shape_comp::getArea() const noexcept
{
  return getWholeArea(shapes_, size_);
}

zubarev::rectangle_t zubarev::Shape_comp::getFrameRect() const noexcept
{
  return getWholeFrame(shapes_, size_);
}

void zubarev::Shape_comp::move(const zubarev::point_t& p) noexcept
{
  for (size_t i = 0; i < size_; ++i) {
    shapes_[i]->move(p);
  }
}

void zubarev::Shape_comp::move(double dx, double dy) noexcept
{
  for (size_t i = 0; i < size_; ++i) {
    shapes_[i]->move(dx, dy);
  }
}

void zubarev::Shape_comp::scale(double k)
{
  if (k <= 0) {
    throw std::invalid_argument("Scale must be positive");
  }

  for (size_t i = 0; i < size_; ++i) {
    shapes_[i]->scale(k);
  }
}

void zubarev::Shape_comp::append(Shape* value)
{
  add(value, size_);
}

void zubarev::Shape_comp::preappend(Shape* value)
{
  add(value, 0);
}

void zubarev::Shape_comp::add(Shape* value, size_t index)
{
  if (index > size_) {
    throw std::out_of_range("Index out of range");
  }

  if (size_ >= capacity_) {
    size_t newCapacity = (capacity_ == 0) ? 2 : capacity_ * 2;
    Shape** newArr = new Shape*[newCapacity];

    for (size_t i = 0; i < index; ++i) {
      newArr[i] = shapes_[i];
    }

    newArr[index] = value;

    for (size_t i = index; i < size_; ++i) {
      newArr[i + 1] = shapes_[i];
    }

    delete[] shapes_;
    shapes_ = newArr;
    capacity_ = newCapacity;
  } else {
    for (size_t i = size_; i > index; --i) {
      shapes_[i] = shapes_[i - 1];
    }
    shapes_[index] = value;
  }

  ++size_;
}

zubarev::Shape& zubarev::Shape_comp::first() noexcept
{
  return get(0);
}
zubarev::Shape& zubarev::Shape_comp::last() noexcept
{
  return get(size_ - 1);
}

zubarev::Shape& zubarev::Shape_comp::at(size_t index)
{
  if (index >= size_) {
    throw std::out_of_range("Index out of range");
  }
  return *shapes_[index];
}

zubarev::Shape& zubarev::Shape_comp::get(size_t index) noexcept
{
  return *shapes_[index];
}

void zubarev::Shape_comp::remove(size_t index)
{
  if (index > size_) {
    throw std::out_of_range("Index out of range");
  }

  for (size_t i = index; i < size_; i++) {
    shapes_[i] = shapes_[i + 1];
  }

  --size_;
}

void zubarev::Shape_comp::dropFirst()
{
  if (size_ == 0) {
    throw std::out_of_range("Index out of range");
  }

  remove(0);
}

void zubarev::Shape_comp::dropLast()
{
  if (size_ == 0) {
    throw std::out_of_range("Index out of range");
  }

  remove(size_ - 1);
}

void zubarev::Shape_comp::clear()
{
  for (size_t i = 0; i < size_; ++i) {
    delete shapes_[i];
  }
  size_ = 0;
}

size_t zubarev::Shape_comp::size()
{
  return size_;
}

bool zubarev::Shape_comp::empty()
{
  return (size_ == 0);
}

void zubarev::Shape_comp::reserve(size_t newCapacity)
{
  Shape** newArr = new Shape*[newCapacity];

  for (size_t i = 0; i < size_; ++i) {
    newArr[i] = shapes_[i];
  }

  delete[] shapes_;
  shapes_ = newArr;
  capacity_ = newCapacity;
}

void zubarev::Shape_comp::shrink()
{
  reserve(size_);
}

size_t zubarev::Shape_comp::capacity()
{
  return capacity_;
}

zubarev::Shape** zubarev::Shape_comp::shapes()
{
  return shapes_;
}
