#include <cmath>
#include <cstring>
#include <iostream>
#include "float_internals.h"
#include <vector>
#include <algorithm>
#define INF FLT_MAX + 1

std::string FloatToBinaryPresentation(float value) {

  // shifts all bytes to integer part, e. g. 1.001 becomes 1001
  int shifted_value = *reinterpret_cast<int*>(&value);
  std::string binary_representation;
  for (int i = 0; i < sizeof(value) * 8; ++i) {
    // uses binary operations to get byte in the i-th place
    binary_representation += (((1 << i) & shifted_value) != 0) ? '1' : '0';
  }
  std::reverse(binary_representation.begin(), binary_representation.end());
  return binary_representation;
}

// Due to previous function, binary_representation has the form:
// the 1st byte is sign: '+' if 0, '-' if 1
// from 2 to 9 are bytes of exponent
// from 10 to 32 are bytes of mantissa


char GetSign(const std::string& binary_representation) {
  return (binary_representation.front() == '1') ? '-' : '+';
}

std::string GetMantissa(const std::string& binary_representation) {
  return binary_representation.substr(9);
}

int StringToInt(const std::string& data) {
  int result = 0;
  for (int pos = data.size() - 1; pos >= 0; --pos) {
    result += (data.at(pos) - '0') * std::pow(2, data.size() - 1 - pos);
  }
  return result;
}

int GetExponent(const std::string& binary_representation) {
  std::string exponent = binary_representation.substr(1, 8);
  return std::max(StringToInt(exponent) - 127, -126);
}

char GetFirstDigit(const std::string& binary_representation) {
  int count_of_ones = count_if(binary_representation.begin() + 1,
                               binary_representation.begin() + 9, [](char
                                                                     byte) {
        return (byte == '1');
      });
  return (count_of_ones == 0) ? '0' : '1';
}

std::string FloatInternalsAsString(float value) {
  if (value == 0 && GetSign(FloatToBinaryPresentation(value)) == '+') {
    return "+0";
  }
  if (value == -0.) {
    return "-0";
  }
  std::string result = FloatToBinaryPresentation(value);
  if (value > INF) {
    return "+INF";
  } else if (value < -INF - 1) {
    return "-INF";
  }
  result = std::string(1, GetSign(result)) +
      GetFirstDigit(result) + "." +
      GetMantissa(result) + "_2 * 2^{" + std::to_string(GetExponent(result))
      + "}";
  return result;
}
