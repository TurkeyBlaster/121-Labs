#include "functions.h"

int Largest(int a, int b, int c) {
  int d = a;
  if (b > d) {
    d = b;
  }
  if (c > d) {
    d = c;
  }
  return d;
}

bool SumIsEven(int a, int b) {
  return !static_cast<bool>((a+b)%2);
}

int BoxesNeeded(int apples) {
  if (apples<=0) {
    return 0;
  }
  else {
    return apples/20+(apples%20 > 0);
  }
}

bool SmarterSection(int A_correct, int A_total, int B_correct, int B_total) {
  if(A_correct < 0 || A_total <= 0 || B_correct < 0 || B_total <= 0 || A_correct > A_total || B_correct > B_total) {
    throw std::invalid_argument("Invalid arguments");
  }
  return static_cast<double>(A_correct)/A_total > static_cast<double>(B_correct)/B_total;
}

bool GoodDinner(int pizzas, bool is_weekend) {
  if (pizzas >= 10) {
    if (is_weekend) {
      return true;
    }
    else {
      return pizzas <= 20;
    }
  }
  else {
    return false;
  }
}

int SumBetween(int low, int high) {
  if (low > high) {
    throw std::invalid_argument("");
  }
  if (low == high) {
    return low;
  }
  long int product((static_cast<long int>(low)+high)*(static_cast<long int>(high)-low+1)/2);
  if ((product<=INT32_MAX) && (product>=INT32_MIN)) {
    return static_cast<int>(product);
  }
  else {
    throw std::overflow_error("");
  }
}

int Product(int a, int b) {
  long int product(static_cast<long int>(a)*static_cast<long int>(b));
  if ((product<=INT32_MAX) && (product>=INT32_MIN)) {
    return static_cast<int>(product);
  }
  else {
    throw std::overflow_error("");
  }
}