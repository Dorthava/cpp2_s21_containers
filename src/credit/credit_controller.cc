#include "credit_controller.h"

namespace s21 {
// CreditController::CreditController() : model_(nullptr) {}

CreditController::CreditController(CreditModel *model) : model_(model) {}

// Сеттеры
void CreditController::SetInput(const double &total_amount, const int &term,
                                const double &interest_rate,
                                const bool &type_annuity) {
  model_->SetTotalAmount(total_amount);
  model_->SetTerm(term);
  model_->SetInterestRate(interest_rate);
  model_->SetTypeAnnuity(type_annuity);
}

void s21::CreditController::CalculateResult() { model_->CalculationResults(); }

// Геттеры

std::pair<double, double> CreditController::GetMonthlyPayment() const noexcept {
  return model_->GetMonthlyPayment();
}

double CreditController::GetOverpaymentOnCredit() const noexcept {
  return model_->GetOverpaymentOnCredit();
}

double CreditController::GetTotalPayment() const noexcept {
  return model_->GetTotalPayment();
}
}  // namespace s21