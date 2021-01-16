#include "main.h"
#include "vector_class.hpp"

using namespace std;

double CVector::getLength() {
  return sqrt(pow(x, 2) + pow(y, 2));
}

double CVector::getAngle() {
  if (x != 0) return tan(y / x);
  else if (y > 0) return (3.14159 / 2);
  else if (y < 0) return (3 * 3.14159 / 2);
  else return 0;
}

CVector CVector::operator+ (const CVector& param) {
  CVector temp;
  temp.x = x + param.x;
  temp.y = y + param.y;
  return temp;
}

CVector CVector::operator* (const double& param) {
  CVector temp;
  temp.x = x * param;
  temp.y = y * param;
  return temp;
}
