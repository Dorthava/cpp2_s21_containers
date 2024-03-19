#ifndef CPP3_S21_SMARTCALC_V20_DEPOSIT_DEPOSIT_MODEL_H
#define CPP3_S21_SMARTCALC_V20_DEPOSIT_DEPOSIT_MODEL_H

#include <string>
#include <vector>

#include "deposit_date.h"

namespace s21 {
class DepositModel {
 public:
  DepositModel();
  DepositModel(const DepositModel& other) = delete;
  DepositModel(DepositModel&& other) = delete;
  DepositModel& operator=(const DepositModel& other) = delete;
  DepositModel& operator=(DepositModel&& other) = delete;
  ~DepositModel() = default;

  // Сеттеры
  void SetDepositAmount(const double& other);
  void SetDepositTerm(const int& other);
  void SetInterestRate(const double& other);
  void SetTaxRate(const double& other);
  void SetPeriodicity(const short& other);
  void SetCapitalization(const bool& other);
  void SetReplenishment(const std::pair<Date, double>& other);
  void SetDate(const Date& date);

  void SetReset();
  // Геттеры
  double GetAccruedInterest();
  double GetTaxAmount();
  double GetDepositEnd();

  // Functions
  void CheckError() const;
  void CalculationResult();
  void UpdateTotal(const Date& date, double& total);

 private:
  // Входные данные
  Date date_;
  double deposit_amount_;  // Сумма вклада
  int deposit_term_;       // Срок размещения - в месяцах
  double interest_rate_;   // Процентная ставка
  double tax_rate_;        // Налоговая ставка
  short periodicity_of_payments_;  // Периодичность выплат(0 - 2)
  bool capitalization_of_interest;  // Капитализация процентов
  std::vector<std::pair<Date, double>>
      replenishments_list_;  // Cписок пополнений - std::pair<int, double>

  // Выходные данные
  double accrued_interest_;  // Начисленные проценты
  double tax_amount_;        // Сумма налога
  double end_amount_;  // Cумма на вкладе к концу срока
};
}  // namespace s21

// #include "deposit_model.cc"
#endif  // CPP3_S21_SMARTCALC_V20_DEPOSIT_DEPOSIT_MODEL_H
