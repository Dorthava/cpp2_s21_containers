#ifndef CPP3_S21_SMARTCALC_V20_CREDIT_CREDIT_CONTROLLER_H
#define CPP3_S21_SMARTCALC_V20_CREDIT_CREDIT_CONTROLLER_H

#include "credit_model.h"
namespace s21 {
class CreditController {
 public:
  CreditController() = delete;
  CreditController(CreditModel* model);
  CreditController(const CreditController& other) = delete;
  CreditController(CreditController&& other) = delete;
  CreditController& operator=(const CreditController& other) = delete;
  CreditController& operator=(CreditController&& other) = delete;
  ~CreditController() = default;

  // Сеттеры
  void SetInput(const double& total_amount, const int& term,
                const double& interest_rate, const bool& type_annuity);
  void CalculateResult();

  // Геттеры
  std::pair<double, double> GetMonthlyPayment() const noexcept;
  double GetOverpaymentOnCredit() const noexcept;
  double GetTotalPayment() const noexcept;

 private:
  CreditModel* model_;
};
}  // namespace s21

#endif  // CPP3_S21_SMARTCALC_V20_CREDIT_CREDIT_CONTROLLER_H
