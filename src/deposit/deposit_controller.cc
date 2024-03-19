#include "deposit_controller.h"

namespace s21 {
DepositController::DepositController(DepositModel *model) : model_(model) {}

// Add Replenishment
void s21::DepositController::AddReplenishment(
    const std::pair<s21::Date, double> &other) {
  model_->SetReplenishment(other);
}

// Result:
void DepositController::CalculateResult() { model_->CalculationResult(); }

// Сеттеры
void DepositController::SetDepositAmount(const double &other) {
  model_->SetDepositAmount(other);
}

void DepositController::SetDepositTerm(const int &other) {
  model_->SetDepositTerm(other);
}

void DepositController::SetInterestRate(const double &other) {
  model_->SetInterestRate(other);
}

void DepositController::SetTaxRate(const double &other) {
  model_->SetTaxRate(other);
}

void DepositController::SetPeriodicity(const short &other) {
  model_->SetPeriodicity(other);
}

void DepositController::SetCapitalization(const bool &other) {
  model_->SetCapitalization(other);
}

void DepositController::SetDate(const Date &date) { model_->SetDate(date); }

void s21::DepositController::SetReset() { model_->SetReset(); }

// Геттеры
double s21::DepositController::GetAccruedInterest() {
  return model_->GetAccruedInterest();
}

double s21::DepositController::GetTaxAmount() { return model_->GetTaxAmount(); }

double s21::DepositController::GetDepositEnd() {
  return model_->GetDepositEnd();
}
}  // namespace s21