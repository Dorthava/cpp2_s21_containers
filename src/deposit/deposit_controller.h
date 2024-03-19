#ifndef CPP3_S21_SMARTCALC_V20_DEPOSIT_DEPOSIT_CONTROLLER_H
#define CPP3_S21_SMARTCALC_V20_DEPOSIT_DEPOSIT_CONTROLLER_H
#include "deposit_model.h"

namespace s21 {
class DepositController {
 public:
  DepositController() = delete;
  DepositController(DepositModel* model);
  DepositController(const DepositController& other) = delete;
  DepositController(DepositController&& other) = delete;
  DepositController& operator=(const DepositController& other) = delete;
  DepositController& operator=(DepositController&& other) = delete;
  ~DepositController() = default;

  void AddReplenishment(const std::pair<Date, double>& other);
  void CalculateResult();

  void SetDepositAmount(const double& other);
  void SetDepositTerm(const int& other);
  void SetInterestRate(const double& other);
  void SetTaxRate(const double& other);
  void SetPeriodicity(const short& other);
  void SetCapitalization(const bool& other);
  void SetDate(const s21::Date& date);

  void SetReset();
  // Геттеры
  double GetAccruedInterest();
  double GetTaxAmount();
  double GetDepositEnd();

 private:
  DepositModel* model_;
};
}  // namespace s21
#endif  // CPP3_S21_SMARTCALC_V20_DEPOSIT_DEPOSIT_CONTROLLER_H