#ifndef CPP3_S21_SMARTCALC_V20_DEPOSIT_DEPOSIT_DATE_H
#define CPP3_S21_SMARTCALC_V20_DEPOSIT_DEPOSIT_DATE_H

namespace s21 {
class Date final {
 public:
  Date() = delete;
  Date(short day, short month, short year);
  Date(const Date& other);
  Date(Date&& other) = delete;
  Date& operator=(const Date& other);
  Date& operator=(Date&& other) = delete;
  ~Date() = default;

  // Перегрузка операций
  bool operator==(const Date& other);
  bool operator!=(const Date& other);
  bool operator<=(const Date& other);
  Date& operator++();

  void SetMonth(const int& index);

  int GetDay();
  int GetMonth();
  int GetYear();
  int GetDaysInFeb(const int& year);

 private:
  int GetDaysInMonth(const int& month,
                     const int& year);  // внутренний метод получения месяца
  short day_;
  short month_;
  short year_;
};
}  // namespace s21
// #include "deposit_date.cc"
#endif  // CPP3_S21_SMARTCALC_V20_DEPOSIT_DEPOSIT_DATE_H