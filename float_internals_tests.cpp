#include <gtest/gtest.h>
#include "float_internals.h"
#include <climits>
#include <cmath>
#define INF std::numeric_limits<float>::infinity()

TEST(convert, GetRepresentation) {
  EXPECT_TRUE(FloatToBinaryPresentation(1.15) ==
  "00111111100100110011001100110011");
  EXPECT_TRUE(FloatToBinaryPresentation(1.5e-38) ==
  "00000000101000110101010111100110");
  EXPECT_TRUE(FloatToBinaryPresentation(42) ==
  "01000010001010000000000000000000");
  EXPECT_TRUE(FloatToBinaryPresentation(43) ==
  "01000010001011000000000000000000");
  EXPECT_TRUE(FloatToBinaryPresentation(-1025) ==
  "11000100100000000010000000000000");
  EXPECT_TRUE(FloatToBinaryPresentation(-10256488.12) ==
  "11001011000111001000000001101000");
  EXPECT_EQ(FloatToBinaryPresentation(INF),
  "01111111100000000000000000000000");
  EXPECT_EQ(FloatToBinaryPresentation(-INF),
  "11111111100000000000000000000000");
}

TEST(sign, GetSign) {
EXPECT_TRUE(GetSign(FloatToBinaryPresentation(1.15)) == '+');
EXPECT_TRUE(GetSign(FloatToBinaryPresentation(-1.15)) == '-');
EXPECT_TRUE(GetSign(FloatToBinaryPresentation(-0.)) == '-');
EXPECT_TRUE(GetSign(FloatToBinaryPresentation(0)) == '+');
EXPECT_TRUE(GetSign(FloatToBinaryPresentation(INF)) == '+');
EXPECT_TRUE(GetSign(FloatToBinaryPresentation(-INF)) == '-');
}

TEST(mantissa, GetMantissa) {
  EXPECT_EQ(GetMantissa(FloatToBinaryPresentation(1.15)),
            "00100110011001100110011");
  EXPECT_EQ(GetMantissa(FloatToBinaryPresentation(-1.15)),
            "00100110011001100110011");
  EXPECT_EQ(GetMantissa(FloatToBinaryPresentation(-1.55448451)),
            "10001101111100101011001");
  EXPECT_EQ(GetMantissa(FloatToBinaryPresentation(2)),
            "00000000000000000000000");
  EXPECT_EQ(GetMantissa(FloatToBinaryPresentation(std::numeric_limits<float>::infinity())),
            "00000000000000000000000");
}

TEST(exponent, GetExponent) {
  EXPECT_EQ(GetExponent(FloatToBinaryPresentation(42)), 5);
  EXPECT_EQ(GetExponent(FloatToBinaryPresentation(-42)), 5);
  EXPECT_EQ(GetExponent(FloatToBinaryPresentation(-14848.14)), 13);
  EXPECT_EQ(GetExponent(FloatToBinaryPresentation(545154.5451515)), 19);
  EXPECT_EQ(GetExponent(FloatToBinaryPresentation(3.402823e+39)), 128);
  EXPECT_EQ(GetExponent(FloatToBinaryPresentation(1.0e-38)), -126);
  EXPECT_EQ(GetExponent(FloatToBinaryPresentation(-0.1)), -4);
  EXPECT_EQ(GetExponent(FloatToBinaryPresentation(0.6)), -1);
}

TEST(Final, FloatInternalsAsString) {
  EXPECT_EQ(FloatInternalsAsString(0), "+0");
  EXPECT_EQ(FloatInternalsAsString(42), "+1.01010000000000000000000_2 * 2^{5}");
  EXPECT_EQ(FloatInternalsAsString(-0.1), "-1.10011001100110011001101_2 * 2^{-4}");
  EXPECT_EQ(FloatInternalsAsString(1.0e-38), "+0.11011001110001111101110_2 * 2^{-126}");
  EXPECT_EQ(FloatInternalsAsString(-INF), "-INF");
  EXPECT_EQ(FloatInternalsAsString(INF), "+INF");
  EXPECT_EQ(FloatInternalsAsString(-0.), "-0");
}

TEST(Test_3, HardCases) {
  EXPECT_EQ(FloatInternalsAsString(1.701e38),
            "+1.11111111111000000100011_2 * 2^{126}");
  EXPECT_EQ(FloatInternalsAsString(1.7014118e38),
            "+1.00000000000000000000000_2 * 2^{127}");
  EXPECT_EQ(FloatInternalsAsString(std::numeric_limits<float>::max()),
            "+1.11111111111111111111111_2 * 2^{127}");
  EXPECT_EQ(FloatInternalsAsString(std::numeric_limits<float>::min()),
            "+1.00000000000000000000000_2 * 2^{-126}");
}

TEST(Test_2, SpecialCases) {
  EXPECT_EQ(FloatInternalsAsString(0), "+0");
  EXPECT_EQ(FloatInternalsAsString(-1.0e-100), "-0");
  EXPECT_EQ(FloatInternalsAsString(INFINITY), "+INF");
  EXPECT_EQ(FloatInternalsAsString(-std::numeric_limits<float>::infinity()),
            "-INF");
  EXPECT_EQ(FloatInternalsAsString(-INFINITY), "-INF");
}
TEST(Test_0, SampleTests) {
  EXPECT_EQ(FloatInternalsAsString(0), "+0");
  EXPECT_EQ(FloatInternalsAsString(42),
            "+1.01010000000000000000000_2 * 2^{5}");
  EXPECT_EQ(FloatInternalsAsString(1.0e-38),
            "+0.11011001110001111101110_2 * 2^{-126}");
  EXPECT_EQ(FloatInternalsAsString(-0.1),
            "-1.10011001100110011001101_2 * 2^{-4}");
}

TEST(Test_1, SimpleCases) {
  EXPECT_EQ(FloatInternalsAsString(1.0e-37),
            "+1.00010000001110011101010_2 * 2^{-123}");
  EXPECT_EQ(FloatInternalsAsString(1.5e-38),
            "+1.01000110101010111100110_2 * 2^{-126}");
  EXPECT_EQ(FloatInternalsAsString(-1.777e-38),
            "-1.10000010111111110001000_2 * 2^{-126}");
  EXPECT_EQ(FloatInternalsAsString(1.1),
            "+1.00011001100110011001101_2 * 2^{0}");
  EXPECT_EQ(FloatInternalsAsString(1.19209e-07),
            "+1.11111111111111111010111_2 * 2^{-24}");
  EXPECT_EQ(FloatInternalsAsString(std::numeric_limits<float>::epsilon()),
            "+1.00000000000000000000000_2 * 2^{-23}");
  EXPECT_EQ(FloatInternalsAsString(1.40129846432e-45),
            "+0.00000000000000000000001_2 * 2^{-126}");
  EXPECT_EQ(FloatInternalsAsString(7.17464813734e-43),
            "+0.00000000000001000000000_2 * 2^{-126}");
}