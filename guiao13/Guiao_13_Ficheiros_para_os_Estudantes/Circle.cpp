// Circle.cpp

#include "Circle.h"
#include <iostream>
#include <cmath>
#include <cassert>

#define _USE_MATH_DEFINES

Circle::Circle(void) : radius_(1.0), Figure(Point(0, 0), "white") {
  // Circle of radius 1 and centered at (0,0)
}

Circle::Circle(Point center, const std::string& color, double radius)
    : radius_(radius), Figure(center, color) {
  // Ensure that the radius is larger than 0.0
  assert(radius > 0.0);
}

Circle::Circle(double x, double y, const std::string& color, double radius)
    : radius_(radius), Figure(Point(x, y), color) {
  // Ensure that the radius is larger than 0.0
  assert(radius > 0.0);
}

double Circle::GetRadius(void) const { return radius_; }

void Circle::SetRadius(double radius) {
  // Ensure that the radius is larger than 0.0
  assert(radius > 0.0);
  radius_ = radius;
}

std::string Circle::GetClassName(void) const { return "Circle"; }

double Circle::Area(void) const {
  return M_PI * std::pow(radius_, 2);
}

double Circle::Perimeter(void) const {
  return 2 * M_PI * radius_;
}

bool Circle::Intersects(const Circle& c) const {
  // |r1 - r2| < dist(C1,C2) < r1 + r2
  double distance_between_centers = GetCenter().DistanceTo(c.GetCenter());
  double sum_of_radii = radius_ + c.radius_;
  double absolute_difference_of_radii = std::abs(radius_ - c.radius_);

  return ((absolute_difference_of_radii < distance_between_centers) &&
          (distance_between_centers < sum_of_radii));
}

std::ostream& operator<<(std::ostream& os, const Circle& obj) {
  os << "Center: " << obj.GetCenter() << std::endl;
  os << "Color: " << obj.GetColor() << std::endl;
  os << "Radius = " << obj.GetRadius() << std::endl;
  return os;
}

std::istream& operator>>(std::istream& is, Circle& obj) {
  double x, y, radius;
  std::string color;

  std::cout << "Enter center coordinates (x y): ";
  is >> x >> y;
  obj.SetCenter(Point(x, y));

  std::cout << "Enter color: ";
  is >> color;
  obj.SetColor(color);

  std::cout << "Enter radius: ";
  is >> radius;
  obj.SetRadius(radius);

  return is;
}
