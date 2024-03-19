#include "deposit_date.h"

namespace s21 {
Date::Date(short day, short month, short year)
    : day_(day), month_(month), year_(year) {}

Date::Date(const Date &other) {
  day_ = other.day_;
  month_ = other.month_;
  year_ = other.year_;
}
Date &Date::operator=(const s21::Date &other) {
  day_ = other.day_;
  month_ = other.month_;
  year_ = other.year_;
  return *this;
}

int Date::GetDaysInFeb(const int &year) {
  if ((!(year % 4) && (year % 100)) || !(year % 400)) {
    return 29;
  }
  return 28;
}

int Date::GetDaysInMonth(const int &month, const int &year) {
  if (month == 2)
    return GetDaysInFeb(year);
  else if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 ||
           month == 10 || month == 12)
    return 31;
  else
    return 30;
}

bool Date::operator==(const s21::Date &other) {
  return day_ == other.day_ && month_ == other.month_ && year_ == other.year_;
}

bool Date::operator!=(const s21::Date &other) { return !operator==(other); }

bool Date::operator<=(const s21::Date &other) {
  if (year_ < other.year_) return true;
  if (month_ < other.month_) return true;
  if (day_ <= other.day_) return true;
  return false;
}

// Get
int Date::GetDay() { return day_; }

int Date::GetMonth() { return month_; }

int Date::GetYear() { return year_; }

// Set
void Date::SetMonth(const int &index) {  // Нашли конец
  month_ += index;
  while (month_ > 12) {
    month_ -= 12;
    year_ += 1;
  }
  int days_in_month = GetDaysInMonth(month_, year_);
  if (days_in_month < day_) {
    day_ = days_in_month;
  }
}

s21::Date &s21::Date::operator++() {
  int days_in_month_ = GetDaysInMonth(month_, year_);
  ++day_;
  if (day_ > days_in_month_) {
    day_ = 1;
    ++month_;
    if (month_ > 12) {
      month_ = 1;
      ++year_;
    }
  }
  return *this;
}
}  // namespace s21
