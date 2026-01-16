#include "shape_comp.hpp"
#include <all.hpp>
#include <iostream>



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

  zub::Shape_comp shapes = zub::Shape_comp();

  try {

    
    shapes.append(new zub::Rectangle(2, 2, {-7, -7}));


    shapes.append(new zub::Ring(3, 1, {5, -10}));


    zub::point_t polyA[3] = {{0, 0}, {4, 0}, {2, 4}};
    shapes.preappend(new zub::Polygon(3, polyA));

    zub::printInfo(shapes.shapes(), shapes.size());


    std::cout << "\n";
    std::cout << "First area: " << shapes.first().getArea() << "\n";
    std::cout << "Last area: " << shapes.last().getArea() << "\n";


    shapes.add(new zub::Rectangle(2, 8, {2, 2}), 2);
    std::cout << "\nAfter insert at index 2:\n";
    zub::printInfo(shapes.shapes(), shapes.size());


    shapes.remove(1);
    std::cout << "\nAfter remove index 1:\n";
    zub::printInfo(shapes.shapes(), shapes.size());

    shapes.dropFirst();
    shapes.dropLast();
    std::cout << "\nAfter drop first and last:\n";
    zub::printInfo(shapes.shapes(), shapes.size());

    shapes.clear();
    std::cout << "\nAfter clear:\n";
    std::cout << "Empty: " << shapes.empty() << "\n";

  } catch (const std::exception& e) {
    std::cerr << "Error: " << e.what() << "\n";
  }

  return 0;
}
// zub::point_t polyA[3] = {{0, 0}, {4, 0}, {2, 4}};
// try {
//   shapes[0] = new zub::Polygon(3, polyA);
// } catch (...) {
//   std::cerr << "Memory allocation" << '\n';
//   return 1;
// }

// std::cout << "--- BEFORE SCALING ---" << '\n';
// zub::printInfo(shapes, size);

// zub::scaleAtCertainPnt(shapes, size, scaleCenter, k);

// std::cout << "--- AFTER SCALING (k=" << k << " relative to " << scaleCenter.x << ", "
//           << scaleCenter.y << ") ---" << '\n';

// zub::printInfo(shapes, size);

// for (size_t i = 0; i < size; i++) {
//   delete shapes[i];
// }
