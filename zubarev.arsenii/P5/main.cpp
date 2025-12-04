#include <iostream>
using s_t=size_t
struct point_t
{
  double x,y;
};
struct rectangle_t
{
  double width, height;
  point_t pos;
};

struct Shape
{
  virtual ~Shape() = default;
  virtual double getArea() const=0;
  virtual  rectangle_t getFrameRect() const=0;
  virtual void move(const point_t& p) = 0;
  virtual void move(double dx, double dy) = 0;
  virtual void scale(double k) = 0;
};

struct Rectangle: Shape
{
  Rectangle(double width, double height, const point_t& pos);
  virtual ~Rectangle() = default;
  double getArea() const override;
  rectangle_t getFrameRect() const override;
  void move(const point_t& p) override;
  void move(double dx, double dy) override;
  void scale(double k) override;
  private:
    double width_,height_;
    point_t pos_;
};

Rectangle::Rectangle(double width, double height, const point_t& pos):
  width_(width),
  height_(height),
  pos_(pos)
  {}

double Rectangle::getArea() const {
  return height_*width_;
}
rectangle_t Rectangle::getFrameRect() const {
  rectangle_t frame;
  frame.width=width_;
  frame.height=height_;
  frame.pos=pos_;
  return frame;
}
void Rectangle::move(const point_t&p) {
  pos_=p;
}

void Rectangle::move(double dx, double dy) {
  pos_.x+=dx;
  pos_.y+=dy;
}
void Rectangle::scale(double k) {
  width_*=k;
  height_*=k;
}
double dist(point_t &a,point_t &b) {
  double dx=a.x-b.x;
  double dy=a.y-b.y;
  return std::sqrt(dx*dx + dy*dy);
}
void scaleAtCertainPnt(Shape * shapes[],s_t size,point_t pos,double k) {
  for (s_t i=0;i<size;++i) {
    rectangle_t frame=shapes[i].getFrameReact();
    point_t auxPnt1={frame.pos.x+frame.width/2,frame.pos.y+frame.height/2};
    shapes[i].move(pos);
    point_t auxPnt2={frame.pos.x+frame.width/2,frame.pos.y+frame.height/2};
    double distance=dist(auxPnt1, auxPnt2);
    shapes[i].scale(k);
    
  }
}

int main() {
  using namespace std;
  size_t result = 0;
  cout << result << endl;
  return 0;
}
