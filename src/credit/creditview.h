#ifndef CPP3_S21_SMARTCALC_V20_SMARTCALC_CREDIT_CREDIT_VIEW_H
#define CPP3_S21_SMARTCALC_V20_SMARTCALC_CREDIT_CREDIT_VIEW_H

#include <QValidator>
#include <QWidget>

#include "credit_controller.h"
namespace Ui {
class CreditView;
}

namespace s21 {
class CreditView : public QWidget {
  Q_OBJECT

 public:
  explicit CreditView(QWidget* parent = nullptr);
  CreditView(const CreditView& other) = delete;
  CreditView(CreditView&& other) = delete;
  CreditView& operator=(const CreditView& other) = delete;
  CreditView& operator=(CreditView&& other) = delete;
  ~CreditView();

 private slots:
  void on_pushButton_2_clicked();
  void on_pushButton_clicked();

 private:
  void SetValidators();

  Ui::CreditView* ui;
  s21::CreditModel* model_;
  s21::CreditController* controller_;

  QDoubleValidator* validator_double_;
  QIntValidator* validator_int_;
};
}  // namespace s21
#endif  // CPP3_S21_SMARTCALC_V20_SMARTCALC_CREDIT_CREDIT_VIEW_H
