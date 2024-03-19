#include "deposit_model.h"
namespace s21 {
DepositModel::DepositModel()
    : date_(0, 0, 0),
      deposit_amount_(0.),
      deposit_term_(0),
      interest_rate_(0.),
      tax_rate_(0.),
      periodicity_of_payments_(0),
      capitalization_of_interest(false),
      replenishments_list_() {}

// Сеттеры
void DepositModel::SetDepositAmount(const double &other) {
  deposit_amount_ = other;
}

void DepositModel::SetDepositTerm(const int &other) { deposit_term_ = other; }

void DepositModel::SetInterestRate(const double &other) {
  interest_rate_ = other;
}

void DepositModel::SetTaxRate(const double &other) { tax_rate_ = other; }

void DepositModel::SetPeriodicity(const short &other) {
  periodicity_of_payments_ = other;
}

void DepositModel::SetCapitalization(const bool &other) {
  capitalization_of_interest = other;
}

void DepositModel::SetDate(const Date &date) { date_ = date; }

void DepositModel::SetReset() {
  deposit_amount_ = 0.;
  deposit_term_ = 0;
  interest_rate_ = 0.;
  tax_rate_ = 0.;
  periodicity_of_payments_ = 0;
  capitalization_of_interest = false;
  replenishments_list_.clear();
  accrued_interest_ = 0.;
}

// Геттеры
double DepositModel::GetAccruedInterest() { return accrued_interest_; }

double DepositModel::GetTaxAmount() { return tax_amount_; }

double DepositModel::GetDepositEnd() { return end_amount_; }

void DepositModel::SetReplenishment(const std::pair<Date, double> &other) {
  replenishments_list_.push_back(other);
}

void DepositModel::UpdateTotal(const Date &date, double &total) {
  for (auto i : replenishments_list_) {
    if (i.second > 1000000000000. || i.second < -1000000000000.)
      throw std::string("The replenishment or withdraval is incorrect");
    if (i.first == date) total += i.second;
  }
}

void DepositModel::CheckError() const {
  if (deposit_amount_ > 1000000000000. || deposit_amount_ < 1.)
    throw std::string("The total loan amount is incorrect");
  if (deposit_term_ > 365 || deposit_term_ < 1)
    throw std::string("Term field is incorrect");
  if (interest_rate_ < 0.01 || interest_rate_ > 999)
    throw std::string("Wrong interest rate");
  if (tax_rate_ < 0.01 || tax_rate_ > 999)
    throw std::string("Wrong interest rate");
}

void DepositModel::CalculationResult() {
  CheckError();
  double accrued_base = interest_rate_ / (100 * 365);
  double accrued_adv = interest_rate_ / (100 * 366);
  Date date_end = date_;

  date_end.SetMonth(deposit_term_);
  Date last_date = date_;
  double add_value{};
  double total_value(deposit_amount_);
  while (date_ != date_end) {
    if (!replenishments_list_.empty()) UpdateTotal(date_, total_value);
    if (total_value < 1.)
      throw std::string(
          "You've run out of money. The deposit is automatically closed. You "
          "will not receive any interest!:)");
    if (date_.GetDaysInFeb(date_.GetYear()) == 29)
      add_value += total_value * accrued_adv;
    else
      add_value += total_value * accrued_base;
    if (periodicity_of_payments_ == 0) {
      accrued_interest_ += add_value;
      if (capitalization_of_interest) {
        total_value += add_value;
      }
      add_value = 0.;
    }
    if (last_date.GetMonth() != (++date_).GetMonth()) {
      last_date = date_;
      if (periodicity_of_payments_ == 1) {
        accrued_interest_ += add_value;
        if (capitalization_of_interest) {
          total_value += add_value;
        }
        add_value = 0.;
      }
    }
  }
  if (periodicity_of_payments_ == 2 || periodicity_of_payments_ == 1) {
    accrued_interest_ += add_value;
    if (capitalization_of_interest) {
      total_value += add_value;
    }
  }
  tax_amount_ = tax_rate_ * 0.01 * accrued_interest_;
  end_amount_ = total_value;
}
}  // namespace s21
