#ifndef CPP3_S21_SMARTCALC_V20_SMARTCALC_CREDIT_CREDIT_MODEL_H
#define CPP3_S21_SMARTCALC_V20_SMARTCALC_CREDIT_CREDIT_MODEL_H

#include <math.h>

#include <string>
#include <vector>
namespace s21 {
class CreditModel {
 public:
  // Constructor
  CreditModel() = default;
  CreditModel(const CreditModel& other) = delete;
  CreditModel(CreditModel&& other) = delete;
  CreditModel& operator=(const CreditModel& other) = delete;
  CreditModel& operator=(CreditModel&& other) = delete;
  ~CreditModel() = default;

  void CheckError();
  void ResetOutput() noexcept;
  void CalculationResults();
  double CalculationInterestRate();

  // Сеттеры
  void SetTotalAmount(const double& other) noexcept;
  void SetTerm(const int& other) noexcept;
  void SetInterestRate(const double& other) noexcept;
  void SetTypeAnnuity(const bool& other) noexcept;

  // Геттеры
  std::pair<double, double> GetMonthlyPayment() const noexcept;
  double GetOverpaymentOnCredit() const noexcept;
  double GetTotalPayment() const noexcept;

 private:
  // Внутренние методы:
  void CalculationAnnuity();
  void CalculationDifferentiated();

  // Входные данные
  double total_amount_;
  int term_;
  double interest_rate_;
  bool type_annuity_;

  // Выходные данные
  std::pair<double, double>
      monthly_payment_;  // ежемесячный платеж {для депозитарного отличается}
  double overpayment_on_credit_;  // Общая переплата
  double total_payment_;          // общая сумма платежа
};
}  // namespace s21

// #include "credit_model.cc"
#endif  // CPP3_S21_SMARTCALC_V20_SMARTCALC_CREDIT_CREDIT_MODEL_H
