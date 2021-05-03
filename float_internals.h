#ifndef FLOAT_INTERNALS_H_
#define FLOAT_INTERNALS_H_

#include <string>
#include <cfloat>


std::string FloatInternalsAsString(float value);
std::string FloatToBinaryPresentation(float value);
char GetSign(const std::string& binary_representation);
std::string GetMantissa(const std::string& binary_representation);
int GetExponent(const std::string& binary_representation);
int StringToInt(const std::string& data);
char GetFirstDigit(const std::string& binary_representation);
#endif  // FLOAT_INTERNALS_H_
