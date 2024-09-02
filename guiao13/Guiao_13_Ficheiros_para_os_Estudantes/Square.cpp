// Square.cpp

#include "Square.h"
#include <iostream>
#include <cassert>

Square::Square(void) : Rectangle(Point(0, 0), "white", 1.0, 1.0) {
  // Square of edge=1 and centered at (0,0)
}

Square::Square(Point center, const std::string& color, double length)
    : Rectangle(center, color, length, length) {
  // Ensure that the length is larger than 0.0
  assert(length > 0.0);
}

Square::Square(double x, double y, const std::string& color, double length)
    : Rectangle(x, y, color, length, length) {
  // Ensure that the length is larger than 0.0
  assert(length > 0.0);
}

double Square::GetEdgeLength(void) const {
  return Rectangle::GetWidth(); // Since it's a square, width and height are the same
}

void Square::SetEdgeLength(double length) {
  // Ensure that the length is larger than 0.0
  assert(length > 0.0);
  Rectangle::SetWidth(length);
  Rectangle::SetHeight(length);
}

std::string Square::GetClassName(void) const {
  return "Square";
}

std::ostream& operator<<(std::ostream& os, const Square& obj) {
  os << "Center: " << obj.GetCenter() << std::endl;
  os << "Color: " << obj.GetColor() << std::endl;
  os << "Edge Length = " << obj.GetEdgeLength() << std::endl;
  return os;
}

std::istream& operator>>(std::istream& is, Square& obj) {
  double x, y, length;
  std::string color;

  std::cout << "Enter center coordinates (x y): ";
  is >> x >> y;
  obj.SetCenter(Point(x, y));

  std::cout << "Enter color: ";
  is >> color;
  obj.SetColor(color);

  std::cout << "Enter edge length: ";
  is >> length;
  obj.SetEdgeLength(length);

  return is;
}

