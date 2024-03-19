#include <iostream>

#include "gtest/gtest.h"
#include "s21_smartcalc.h"

/*
SmartCalc Tests
*/

TEST(SmartcalcTest, simple_test1) {
  s21::Model model;
  model.SetReceived("123");
  double result = model.CalculatingResult();
  ASSERT_DOUBLE_EQ(result, 123.);
}

TEST(SmartcalcTest, simple_test2) {
  s21::Model model;
  model.SetReceived("123+14.67");
  double result = model.CalculatingResult();
  ASSERT_DOUBLE_EQ(result, 137.67);
}

TEST(SmartcalcTest, simple_test3) {
  s21::Model model;
  model.SetReceived("123-14.67");
  double result = model.CalculatingResult();
  ASSERT_DOUBLE_EQ(result, 108.33);
}

TEST(SmartcalcTest, simple_test4) {
  s21::Model model;
  model.SetReceived("123*14.67");
  double result = model.CalculatingResult();
  ASSERT_DOUBLE_EQ(result, 1804.41);
}

TEST(SmartcalcTest, simple_test5) {
  s21::Model model;
  model.SetReceived("sin(21)+cos(21)");
  double result = model.CalculatingResult();
  ASSERT_NEAR(result, 0.28892637831, 1e-7);
}

TEST(SmartcalcTest, simple_test6) {
  s21::Model model;
  model.SetReceived("asin(0.21)+acos(0.21)");
  double result = model.CalculatingResult();
  ASSERT_NEAR(result, 1.5707963, 1e-7);
}

TEST(SmartcalcTest, simple_test7) {
  s21::Model model;
  model.SetReceived("atan(0.21)");
  double result = model.CalculatingResult();
  ASSERT_NEAR(result, 0.2069921, 1e-7);
}

TEST(SmartcalcTest, simple_test8) {
  s21::Model model;
  model.SetReceived("-sin(-0.3)-cos(-0.3)");
  double result_real = -sin(-0.3) - cos(-0.3);
  double result = model.CalculatingResult();
  ASSERT_NEAR(result, result_real, 1e-7);
}

TEST(SmartcalcTest, simple_test9) {
  s21::Model model;
  model.SetReceived("-tan(0.8)/(-15+12)");
  double result_real = -tan(0.8) / (-15 + 12);
  double result = model.CalculatingResult();
  ASSERT_NEAR(result, result_real, 1e-7);
}

TEST(SmartcalcTest, simple_test10) {
  s21::Model model;
  model.SetReceived("sin(1)^2+cos(1)^2");
  double result_real = 1;
  double result = model.CalculatingResult();
  ASSERT_NEAR(result, result_real, 1e-7);
}

TEST(SmartcalcTest, simple_test11) {
  s21::Model model;
  model.SetReceived("2^2^3");
  double result_real = 256;
  double result = model.CalculatingResult();
  ASSERT_NEAR(result, result_real, 1e-7);
}

TEST(SmartcalcTest, simple_test12) {
  s21::Model model;
  model.SetReceived("2+2-18mod      9     ");
  double result_real = 2 + 2 - 18 % 9;
  double result = model.CalculatingResult();
  ASSERT_NEAR(result, result_real, 1e-7);
}

TEST(SmartcalcTest, simple_test13) {
  s21::Model model;
  model.SetReceived("44.34-22.34");
  double result_real = 22;
  double result = model.CalculatingResult();
  ASSERT_NEAR(result, result_real, 1e-7);
}

TEST(SmartcalcTest, simple_test14) {
  s21::Model model;
  model.SetReceived("3333/2");
  double result_real = 1666.5;
  double result = model.CalculatingResult();
  ASSERT_NEAR(result, result_real, 1e-7);
}

TEST(SmartcalcTest, simple_test15) {
  s21::Model model;
  model.SetReceived("ln(10)+log(5)");
  double result_real = log10(10) + log(5);
  double result = model.CalculatingResult();
  ASSERT_NEAR(result, result_real, 1e-7);
}

TEST(SmartcalcTest, simple_test16) {
  s21::Model model;
  model.SetReceived("ln(10)+acos(0.32)+asin(0.55)");
  double result_real = log10(10) + acos(0.32) + asin(0.55);
  double result = model.CalculatingResult();
  ASSERT_NEAR(result, result_real, 1e-7);
}

TEST(SmartcalcTest, simple_test17) {
  s21::Model model;
  model.SetReceived("sqrt(15)");
  double result_real = sqrt(15);
  double result = model.CalculatingResult();
  ASSERT_NEAR(result, result_real, 1e-7);
}

TEST(SmartcalcTest, simple_test18) {
  s21::Model model;
  model.SetReceived("(12)(12)");
  double result_real = 12 * 12;
  double result = model.CalculatingResult();
  ASSERT_NEAR(result, result_real, 1e-7);
}

TEST(SmartcalcTest, simple_test19) {
  s21::Model model;
  model.SetReceived("(+123)+(-55.6543322)");
  double result_real = (+123) + (-55.6543322);
  double result = model.CalculatingResult();
  ASSERT_NEAR(result, result_real, 1e-7);
}

TEST(SmartcalcTest, simple_test20) {
  s21::Model model;
  model.SetReceived("(-2)*x");
  model.SetValueX(15);
  double result_real = (-2) * 15;
  double result = model.CalculatingResult();
  ASSERT_NEAR(result, result_real, 1e-7);
}

TEST(SmartcalcTest, middle_test1) {
  s21::Model model;
  model.SetReceived("-(-(-(-(1))))");
  double result_real = -(-(-(-(1))));
  double result = model.CalculatingResult();
  ASSERT_NEAR(result, result_real, 1e-7);
}

TEST(SmartcalcTest, middle_test2) {
  s21::Model model;
  model.SetReceived("-(-1+343)/2+67/(-56)+7/2*23");
  double result_real = -91.6964285;
  double result = model.CalculatingResult();
  ASSERT_NEAR(result, result_real, 1e-7);
}

TEST(SmartcalcTest, middle_test3) {
  s21::Model model;
  model.SetReceived("1^2^3^4");
  double result_real = 1;
  double result = model.CalculatingResult();
  ASSERT_NEAR(result, result_real, 1e-7);
}

TEST(SmartcalcTest, middle_test4) {
  s21::Model model;
  model.SetReceived("1e-3+56/2+4/1");
  double result_real = 0.001 + 56 / 2 + 4 / 1;
  double result = model.CalculatingResult();
  ASSERT_NEAR(result, result_real, 1e-7);
}

TEST(SmartcalcTest, except_test1) {
  s21::Model model;
  model.SetReceived("");
  EXPECT_ANY_THROW(model.CalculatingResult());
}

TEST(SmartcalcTest, except_test2) {
  s21::Model model;
  model.SetReceived("Hehe, boii");
  EXPECT_ANY_THROW(model.CalculatingResult());
}

TEST(SmartcalcTest, except_test3) {
  s21::Model model;
  model.SetReceived("s in(1)");
  EXPECT_ANY_THROW(model.CalculatingResult());
}

TEST(SmartcalcTest, except_test4) {
  s21::Model model;
  model.SetReceived("1.2.2");
  EXPECT_ANY_THROW(model.CalculatingResult());
}

TEST(SmartcalcTest, except_test5) {
  s21::Model model;
  model.SetReceived("1.22,");
  EXPECT_ANY_THROW(model.CalculatingResult());
}

TEST(SmartcalcTest, except_test6) {
  s21::Model model;
  model.SetReceived("()");
  EXPECT_ANY_THROW(model.CalculatingResult());
}

TEST(SmartcalcTest, except_test7) {
  s21::Model model;
  model.SetReceived(")");
  EXPECT_ANY_THROW(model.CalculatingResult());
}

TEST(SmartcalcTest, except_test8) {
  s21::Model model;
  model.SetReceived("(");
  EXPECT_ANY_THROW(model.CalculatingResult());
}

TEST(SmartcalcTest, except_test9) {
  s21::Model model;
  model.SetReceived(")(");
  EXPECT_ANY_THROW(model.CalculatingResult());
}

TEST(SmartcalcTest, except_test10) {
  s21::Model model;
  model.SetReceived("12)(12");
  EXPECT_ANY_THROW(model.CalculatingResult());
}

TEST(SmartcalcTest, except_test11) {
  s21::Model model;
  model.SetReceived("1ee");
  EXPECT_ANY_THROW(model.CalculatingResult());
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
