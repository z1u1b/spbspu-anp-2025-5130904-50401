#include <iostream>
#include <cmath>

namespace zubarev
{
  struct point_t
  {
    double x, y;
  };

  struct rectangle_t
  {
    double width, height;
    point_t pos;
  };

  struct Shape
  {
    virtual ~Shape() = default;
    virtual double getArea() const = 0;
    virtual rectangle_t getFrameRect() const = 0;
    virtual void move(const point_t& p) = 0;
    virtual void move(double dx, double dy) = 0;
    virtual void scale(double k) = 0;
  };

  struct Rectangle : Shape
  {
    Rectangle(double width, double height, const point_t& pos);
    virtual ~Rectangle() = default;
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const point_t& p) override;
    void move(double dx, double dy) override;
    void scale(double k) override;

  private:
    double width_, height_;
    point_t pos_;
  };

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

  struct Ring : Shape
  {
    Ring(double r1, double r2, const point_t& pos);
    virtual ~Ring() = default;
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const point_t& p) override;
    void move(double dx, double dy) override;
    void scale(double k) override;

  private:
    double r1_, r2_;
    point_t pos_;
  };

  point_t getExtL(const rectangle_t& frame);
  point_t getExtR(const rectangle_t& frame);
  void scaleAtCertainPnt(Shape* shapes[], size_t size, point_t userPos, double k);
  rectangle_t getWholeFrame(Shape* shapes[], size_t size);
  double getWholeArea(Shape* shapes[], size_t size);
  void printInfo(Shape* shapes[], size_t size);
}

zubarev::Polygon::Polygon(const size_t size, point_t* peaks) :
  size_(size)
{
  peaks_ = new point_t[size_];
  for (size_t i = 0; i < size_; ++i) {
    peaks_[i] = peaks[i];
  }
  pos_ = getCentroid();
}

zubarev::Polygon::~Polygon()
{
  delete[] peaks_;
}
zubarev::Polygon::Polygon(const Polygon& w) :
  size_(w.size_),
  peaks_(w.size_ ? new point_t[w.size_] : nullptr),
  pos_(w.pos_)
{
  for (size_t i = 0; i < size_; ++i) {
    peaks_[i] = w.peaks_[i];
  }
}
zubarev::Polygon& zubarev::Polygon::operator=(const Polygon& w)
{
  point_t* r = nullptr;
  if (w.size_) {
    r = new point_t[w.size_];
    for (size_t i = 0; i < w.size_; ++i) {
      r[i] = w.peaks_[i];
    }
  }
  delete[] peaks_;
  peaks_ = r;
  size_ = w.size_;
  return *this;
}
zubarev::Polygon::Polygon(Polygon&& w) :
  size_(w.size_),
  peaks_(w.peaks_),
  pos_(w.pos_)
{
  w.peaks_ = nullptr;
}
zubarev::Polygon& zubarev::Polygon::operator=(zubarev::Polygon&& w)
{
  if (this == &w) {
    return *this;
  }
  delete[] peaks_;
  peaks_ = w.peaks_;
  size_ = w.size_;
  w.peaks_ = nullptr;
  return *this;
}
double zubarev::Polygon::getArea() const
{
  double res = 0;
  for (size_t i = 0; i < size_ - 1; ++i) {
    res += (peaks_[i].x * peaks_[i + 1].y - peaks_[i + 1].x * peaks_[i].y);
  }
  res += (peaks_[size_ - 1].x * peaks_[0].y - peaks_[0].x * peaks_[size_ - 1].y);
  return 0.5 * std::abs(res);
}

zubarev::point_t zubarev::Polygon::getCentroid()
{
  double A = getArea();
  double Cx = 0, Cy = 0;
  double temp = 0;

  for (size_t i = 0; i < size_ - 1; ++i) {
    temp = peaks_[i].x * peaks_[i + 1].y - peaks_[i + 1].x * peaks_[i].y;
    Cx += (peaks_[i].x + peaks_[i + 1].x) * temp;
    Cy += (peaks_[i].y + peaks_[i + 1].y) * temp;
  }

  temp = peaks_[size_ - 1].x * peaks_[0].y - peaks_[0].x * peaks_[size_ - 1].y;
  Cx += (peaks_[size_ - 1].x + peaks_[0].x) * temp;
  Cy += (peaks_[size_ - 1].y + peaks_[0].y) * temp;

  Cx /= (6 * A);
  Cy /= (6 * A);

  return {Cx, Cy};
}

zubarev::rectangle_t zubarev::Polygon::getFrameRect() const
{
  point_t leftExPt = peaks_[0];
  point_t rightExPt = peaks_[0];

  for (size_t i = 1; i < size_; i++) {
    if (peaks_[i].x < leftExPt.x) {
      leftExPt.x = peaks_[i].x;
    }
    if (peaks_[i].x > rightExPt.x) {
      rightExPt.x = peaks_[i].x;
    }
    if (peaks_[i].y > leftExPt.y) {
      leftExPt.y = peaks_[i].y;
    }
    if (peaks_[i].y < rightExPt.y) {
      rightExPt.y = peaks_[i].y;
    }
  }

  rectangle_t allFrame = {};
  allFrame.height = leftExPt.y - rightExPt.y;
  allFrame.width = rightExPt.x - leftExPt.x;
  allFrame.pos = {leftExPt.x + allFrame.width / 2, leftExPt.y - allFrame.height / 2};
  return allFrame;
}

void zubarev::Polygon::move(double dx, double dy)
{
  for (size_t i = 0; i < size_; ++i) {
    peaks_[i].x += dx;
    peaks_[i].y += dy;
  }
  pos_.x += dx;
  pos_.y += dy;
}

void zubarev::Polygon::move(const point_t& p)
{
  double dx = p.x - pos_.x;
  double dy = p.y - pos_.y;
  move(dx, dy);
}

void zubarev::Polygon::scale(double k)
{
  for (size_t i = 0; i < size_; ++i) {
    peaks_[i].x = pos_.x + k * (peaks_[i].x - pos_.x);
    peaks_[i].y = pos_.y + k * (peaks_[i].y - pos_.y);
  }
}

zubarev::Ring::Ring(double r1, double r2, const point_t& pos) :
  r1_(r1),
  r2_(r2),
  pos_(pos)
{}

double zubarev::Ring::getArea() const
{
  return M_PI * std::abs(r1_ * r1_ - r2_ * r2_);
}

zubarev::rectangle_t zubarev::Ring::getFrameRect() const
{
  rectangle_t frame;
  double r = std::max(r1_, r2_);
  frame.pos = pos_;
  frame.width = 2 * r;
  frame.height = 2 * r;
  return frame;
}

void zubarev::Ring::move(const point_t& p)
{
  pos_ = p;
}

void zubarev::Ring::move(double dx, double dy)
{
  pos_.x += dx;
  pos_.y += dy;
}

void zubarev::Ring::scale(double k)
{
  r1_ *= k;
  r2_ *= k;
}

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
  width_ *= k;
  height_ *= k;
}

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

int main()
{
  namespace zub = zubarev;

  zub::point_t scaleCenter = {};
  double k = 0;
  std::cout << "Input coordinate: ";
  std::cin >> scaleCenter.x >> scaleCenter.y;
  if (std::cin.fail()) {
    std::cerr << "Wrong input" << '\n';
    return 1;
  }

  std::cout << "Input coefficient: ";
  std::cin >> k;
  if (k < 0 || std::cin.fail()) {
    std::cerr << "Wrong input" << '\n';
    return 1;
  }

  const size_t size = 3;
  zub::Shape* shapes[size] = {};

  zub::point_t polyA[3] = {{0, 0}, {4, 0}, {2, 4}};
  try {
    shapes[0] = new zub::Polygon(3, polyA);
  } catch (...) {
    std::cerr << "Memory allocation" << '\n';
    return 1;
  }

  shapes[1] = new zub::Rectangle(2, 2, {-7, -7});
  shapes[2] = new zub::Ring(3, 1, {5, -10});

  std::cout << "--- BEFORE SCALING ---" << '\n';
  zub::printInfo(shapes, size);

  zub::scaleAtCertainPnt(shapes, size, scaleCenter, k);

  std::cout << "--- AFTER SCALING (k=" << k << " relative to " << scaleCenter.x << ", " << scaleCenter.y << ") ---" << '\n';

  zub::printInfo(shapes, size);

  for (size_t i = 0; i < size; i++) {
    delete shapes[i];
  }
}
