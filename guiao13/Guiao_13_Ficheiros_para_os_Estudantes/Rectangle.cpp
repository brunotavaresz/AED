// Rectangle.cpp

#include "Rectangle.h"
#include <iostream>
#include <cassert>

Rectangle::Rectangle(void) : height_(1.0), width_(1.0), Figure(Point(0, 0), "white") {
  // Rectangle of width=1 and height=1 and centered at (0,0)
}

Rectangle::Rectangle(Point center, const std::string& color, double width, double height)
    : height_(height), width_(width), Figure(center, color) {
  // Ensure that the width and height are larger than 0.0
  assert(width > 0.0 && height > 0.0);
}

Rectangle::Rectangle(double x, double y, const std::string& color, double width, double height)
    : height_(height), width_(width), Figure(Point(x, y), color) {
  // Ensure that the width and height are larger than 0.0
  assert(width > 0.0 && height > 0.0);
}

double Rectangle::GetHeight(void) const { return height_; }

void Rectangle::SetHeight(double height) {
  // Ensure that the height is larger than 0.0
  assert(height > 0.0);
  height_ = height;
}

double Rectangle::GetWidth(void) const { return width_; }

void Rectangle::SetWidth(double width) {
  // Ensure that the width is larger than 0.0
  assert(width > 0.0);
  width_ = width;
}

std::string Rectangle::GetClassName(void) const { return "Rectangle"; }

double Rectangle::Area(void) const {
  return width_ * height_;
}

double Rectangle::Perimeter(void) const {
  return 2 * (width_ + height_);
}

std::ostream& operator<<(std::ostream& os, const Rectangle& obj) {
  os << "Center: " << obj.GetCenter() << std::endl;
  os << "Color: " << obj.GetColor() << std::endl;
  os << "Width = " << obj.GetWidth() << ", Height = " << obj.GetHeight() << std::endl;
  return os;
}

std::istream& operator>>(std::istream& is, Rectangle& obj) {
  double x, y, width, height;
  std::string color;

  std::cout << "Enter center coordinates (x y): ";
  is >> x >> y;
  obj.SetCenter(Point(x, y));

  std::cout << "Enter color: ";
  is >> color;
  obj.SetColor(color);

  std::cout << "Enter width: ";
  is >> width;
  obj.SetWidth(width);

  std::cout << "Enter height: ";
  is >> height;
  obj.SetHeight(height);

  return is;
}
