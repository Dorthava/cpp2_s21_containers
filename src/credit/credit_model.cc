#include "credit_model.h"

namespace s21 {

void CreditModel::ResetOutput() noexcept {
  monthly_payment_.first = 0.;
  monthly_payment_.second = 0.;
  overpayment_on_credit_ = 0.;
  total_payment_ = 0.;
}

void CreditModel::CalculationAnnuity() {
  double interest_rate = CalculationInterestRate();
  monthly_payment_.first =
      total_amount_ *
      (interest_rate + (interest_rate / ((pow(1 + interest_rate, term_)) - 1)));
  total_payment_ = monthly_payment_.first * term_;
  overpayment_on_credit_ = total_payment_ - total_amount_;
}

void CreditModel::CalculationDifferentiated() {
  double interest_rate = CalculationInterestRate();
  double loan_balance = total_amount_;
  double debt_portion = total_amount_ / term_;

  std::vector<double> total_payment;
  for (int i{}; i < term_; ++i) {
    double percents = loan_balance * interest_rate;
    loan_balance -= debt_portion;
    total_payment.push_back(percents + debt_portion);
  }
  monthly_payment_ = {total_payment.front(), total_payment.back()};
  for (auto payment : total_payment) {
    total_payment_ += payment;
  }
  overpayment_on_credit_ = total_payment_ - total_amount_;
}

void s21::CreditModel::CheckError() {
  if (total_amount_ > 1000000000000. || total_amount_ < 1.)
    throw std::string("The total loan amount is incorrect");
  if (term_ > 600 || term_ < 1) throw std::string("Term field is incorrect");
  if (interest_rate_ < 0.01 || interest_rate_ > 999)
    throw std::string("Wrong interest rate");
}

void CreditModel::CalculationResults() {
  CheckError();
  ResetOutput();
  if (type_annuity_) {
    CalculationAnnuity();
  } else {
    CalculationDifferentiated();
  }
}

double CreditModel::CalculationInterestRate() {
  return interest_rate_ / 100 / 12;
}
// Сеттеры
void CreditModel::SetTotalAmount(const double &other) noexcept {
  total_amount_ = other;
}

void s21::CreditModel::SetTerm(const int &other) noexcept { term_ = other; }

void s21::CreditModel::SetInterestRate(const double &other) noexcept {
  interest_rate_ = other;
}

void s21::CreditModel::SetTypeAnnuity(const bool &other) noexcept {
  type_annuity_ = other;
}

// Геттеры
std::pair<double, double> CreditModel::GetMonthlyPayment() const noexcept {
  return monthly_payment_;
}

double CreditModel::GetOverpaymentOnCredit() const noexcept {
  return overpayment_on_credit_;
}

double CreditModel::GetTotalPayment() const noexcept { return total_payment_; }

}  // namespace s21